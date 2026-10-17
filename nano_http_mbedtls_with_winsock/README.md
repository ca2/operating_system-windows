# nano_http_mbedtls_with_winsock

Verified HTTPS using Mbed TLS 4.1.1 and Winsock, independent of Schannel.
TLS 1.2/1.3 defaults, SNI and hostname checking, bundled CA roots, bounded redirects
(HTTPS only), HTTP Content-Length and chunked decoding, progress reporting,
30-second socket I/O/connect timeouts and a 1 GiB response limit.
Requests are serialized to protect the default PSA implementation.
Synchronous OS DNS resolution can take longer than socket timeouts.
Initial scope: DNS hostnames (no IPv6 literals), direct connections (no HTTP proxies).

`ca-bundle.pem` is the Mozilla CA export from https://curl.se/ca/cacert.pem,
retrieved 2026-10-17; SHA256 a41b5d356aea97a529fe27e0f7316d2f9d946d75927476cf9cf1b90637d00505.
Source and update instructions: https://curl.se/docs/caextract.html .
The certificate data is under MPL-2.0; preserve its source/license notices.
Refresh the bundle deliberately with security updates; never disable certificate checks.

The `transport` library has no ca2 runtime dependency and can be probed without launching
an installer. Negative tests must reject expired, untrusted and wrong-host certificates.
