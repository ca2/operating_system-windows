"""Test real TLS 1.2 and HTTP framing without running the installer.
Usage: python http_framing.py <probe-build-directory> <cmake-executable>
Requires OpenSSL on PATH. Temporarily replaces the probe build's embedded CA bundle.
"""
import pathlib
import socket
import ssl
import subprocess
import sys
import tempfile
import threading

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
    finally:
        stop.set()
        thread.join(2)
        listener.close()
        configure(normal_bundle)
