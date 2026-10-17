"""Test real TLS 1.2 and HTTP framing without running the installer.
Usage: python http_framing.py <probe-build-directory> <cmake-executable>
Requires OpenSSL on PATH. Temporarily replaces the probe build's embedded CA bundle.
"""
import pathlib
import socket
import ssl
import struct
import subprocess
import sys
import tempfile
import threading
import time

build, cmake = pathlib.Path(sys.argv[1]), sys.argv[2]
source = pathlib.Path(__file__).resolve().parent
normal_bundle = source.parent / "ca-bundle.pem"


def configure(bundle):
    subprocess.run([cmake, "-S", str(source), "-B", str(build),
                    "-DCA2_TLS_CA_BUNDLE=" + str(bundle)], check=True, stdout=subprocess.DEVNULL)
    subprocess.run([cmake, "--build", str(build), "--target", "ca2_tls_probe", "-j", "14"],
                   check=True, stdout=subprocess.DEVNULL)


with tempfile.TemporaryDirectory(prefix="ca2-tls-framing-") as directory:
    directory = pathlib.Path(directory)
    certificate, key = directory / "root.pem", directory / "key.pem"
    configuration = directory / "openssl.cnf"
    configuration.write_text("[req]\ndistinguished_name=dn\n[dn]\nCN=localhost\n")
    subprocess.run(["openssl", "req", "-config", str(configuration), "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "1",
                    "-subj", "/CN=localhost", "-addext", "subjectAltName=DNS:localhost",
                    "-keyout", str(key), "-out", str(certificate)],
                   check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    context.minimum_version = context.maximum_version = ssl.TLSVersion.TLSv1_2
    context.load_cert_chain(certificate, key)
    listener = socket.socket()
    listener.bind(("127.0.0.1", 0))
    listener.listen()
    listener.settimeout(0.2)
    port = listener.getsockname()[1]
    stop = threading.Event()
    requests = {}
    replies = {
        "/length": b"HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello",
        "/chunked": b"HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n2\r\nHe\r\n3\r\nllo\r\n0\r\nX-Trailer: yes\r\n\r\n",
        "/truncated": b"HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHe",
        "/duplicate": b"HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Length: 5\r\n\r\nHello",
        "/ambiguous": b"HTTP/1.1 200 OK\r\nContent-Length: 5\r\nTransfer-Encoding: chunked\r\n\r\n",
        "/badchunk": b"HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\nZ\r\n",
        "/redirect": b"HTTP/1.1 302 Found\r\nLocation: /length\r\nContent-Length: 0\r\n\r\n",
        "/downgrade": b"HTTP/1.1 302 Found\r\nLocation: http://localhost/\r\nContent-Length: 0\r\n\r\n",
    }

    def serve():
        while not stop.is_set():
            try:
                connection, _ = listener.accept()
            except socket.timeout:
                continue
            try:
                with context.wrap_socket(connection, server_side=True) as stream:
                    stream.settimeout(5)
                    request = b""
                    while b"\r\n\r\n" not in request:
                        part = stream.recv(4096)
                        if not part:
                            break
                        request += part
                    path = request.split(b" ")[1].decode("ascii")
                    requests[path] = requests.get(path, 0) + 1
                    if path in ("/retry", "/exhausted"):
                        if path == "/exhausted" or requests[path] <= 3:
                            stream.sendall(b"HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHe")
                            # Force a reset after a partial body, like Winsock 10054.
                            time.sleep(0.05)
                            stream.setsockopt(socket.SOL_SOCKET, socket.SO_LINGER, struct.pack("HH", 1, 0))
                            continue
                        path = "/length"
                    stream.sendall(replies[path])
            except (OSError, IndexError, KeyError):
                connection.close()

    thread = threading.Thread(target=serve, daemon=True)
    thread.start()
    try:
        configure(certificate)
        cases = [("length", None), ("chunked", None), ("redirect", None),
                 ("truncated", "Truncated HTTP body"), ("duplicate", "Duplicate HTTP content length"),
                 ("ambiguous", "Ambiguous HTTP body framing"), ("badchunk", "Invalid or excessive HTTP size"),
                 ("downgrade", "Non-HTTPS redirect refused")]
        for path, expected_error in cases:
            arguments = [str(build / "ca2_tls_probe.exe"), f"https://localhost:{port}/{path}"]
            arguments += ["fail", expected_error] if expected_error else ["body"]
            result = subprocess.run(arguments, capture_output=True, text=True, timeout=15)
            assert result.returncode == 0, (path, result.stdout, result.stderr)
            if not expected_error:
                assert "status=200 bytes=5" in result.stdout, (path, result.stdout)
                assert "TLSv1.2" in result.stdout, (path, result.stdout)
            print("PASS", path)
        for path in ("retry", "exhausted", "duplicate", "downgrade"):
            before = requests.get("/" + path, 0)
            started = time.monotonic()
            result = subprocess.run([str(build / "ca2_tls_probe.exe"),
                                     f"https://localhost:{port}/{path}", "retry"],
                                    capture_output=True, text=True, timeout=25)
            count = requests.get("/" + path, 0) - before
            assert count == (4 if path in ("retry", "exhausted") else 1), (path, count, result.stdout)
            if path == "retry":
                assert result.returncode == 0 and "status=200 bytes=5" in result.stdout, result.stdout
                assert "resets=3" in result.stdout, result.stdout
            else:
                assert result.returncode != 0, result.stdout
            if count == 4:
                assert time.monotonic() - started >= 7, result.stdout
                for delay in (1, 2, 4):
                    assert f"in {delay} seconds" in result.stdout, result.stdout
                for retry, seconds in ((1, 1), (2, 2), (3, 4)):
                    lines = [line for line in result.stdout.splitlines()
                             if line.startswith(f"Retry {retry}/3 (attempt")]
                    expected = [f"Retry {retry}/3 (attempt {retry + 1}/4) in {remaining} "
                                + ("second..." if remaining == 1 else "seconds...")
                                for remaining in range(seconds, 0, -1)]
                    assert lines == expected, (lines, expected)
            print("PASS", path, "retry policy")
    finally:
        stop.set()
        thread.join(2)
        listener.close()
        configure(normal_bundle)
