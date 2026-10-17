# nano_http_mbedtls_with_winsock

Verified HTTPS using Mbed TLS 4.1.1 and Winsock, independent of Schannel.
TLS 1.2/1.3 defaults, SNI and hostname checking, bundled CA roots, bounded redirects
(HTTPS only), HTTP Content-Length and chunked decoding, progress reporting,
30-second socket I/O/connect timeouts and a 1 GiB response limit.
Requests are serialized to protect the default PSA implementation.
The ca2 HTTP adapter retries transient connection failures and interrupted bodies
up to four attempts, with 1, 2 and 4 second delays outside the transport lock.
Partial response data and progress are reset before retrying. Certificate failures,
malformed HTTP and HTTP error status codes are not retried. The optional
`http_status_function` payload callback receives the retry index and a countdown
updated each second; the installer displays it in the detail status line.
Retries restart the complete GET; they do not resume a partial archive.
Synchronous OS DNS resolution can take longer than socket timeouts.
Initial scope: DNS hostnames (no IPv6 literals), direct connections (no HTTP proxies).

`ca-bundle.pem` is the Mozilla CA export from https://curl.se/ca/cacert.pem,
retrieved 2026-10-17; SHA256 a41b5d356aea97a529fe27e0f7316d2f9d946d75927476cf9cf1b90637d00505.
Source and update instructions: https://curl.se/docs/caextract.html .
The certificate data is under MPL-2.0; preserve its source/license notices.
Refresh the bundle deliberately with security updates; never disable certificate checks.

The `transport` library has no ca2 runtime dependency and can be probed without launching
an installer. Negative tests must reject expired, untrusted and wrong-host certificates.

Certificate validation checks chain, hostname and dates using the embedded bundle.
Online OCSP/revocation fetching is not implemented. This is an initial backend, not a claim
of a complete browser HTTP/TLS implementation. The current client closes each connection.
Override the trust bundle explicitly with `CA2_TLS_CA_BUNDLE` when using private CAs.
