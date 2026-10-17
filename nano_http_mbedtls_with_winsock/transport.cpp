#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "transport.h"
#include "ca_bundle.h"
#include <mbedtls/ssl.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/error.h>
#include <mbedtls/net_sockets.h>
#include <psa/crypto.h>
#include <algorithm>
#include <climits>
#include <cstring>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ca2_tls {
namespace {
constexpr std::size_t max_headers = 65536;
constexpr std::uint64_t max_body = 1024ULL * 1024 * 1024;
// Serialize use of the default PSA implementation until a threading adapter is configured.
std::mutex tls_mutex;
std::string lower(std::string s) {
    for (char& c : s) if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
    return s;
}
std::string trim(std::string s) {
    auto first = s.find_first_not_of(" \t");
    return first == std::string::npos ? "" : s.substr(first, s.find_last_not_of(" \t") - first + 1);
}
void safe_text(const std::string& s) {
    for (unsigned char c : s) if (c < 32 || c == 127) throw std::runtime_error("Control character in HTTPS URL or request header.");
}
struct url_parts { std::string host, authority, path; unsigned short port = 443; };
url_parts parse_url(const std::string& url) {
    safe_text(url);
    if (url.compare(0, 8, "https://") != 0) throw std::runtime_error("Only verified HTTPS URLs are supported.");
    auto slash = url.find_first_of("/?#", 8);
    url_parts result;
    result.authority = url.substr(8, slash == std::string::npos ? slash : slash - 8);
    result.host = result.authority;
    if (result.host.empty() || result.host.find_first_of("@\\ ") != std::string::npos)
        throw std::runtime_error("Invalid HTTPS host.");
    auto colon = result.host.find(':');
    if (colon != std::string::npos) {
        auto port = result.host.substr(colon + 1);
        if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos) throw std::runtime_error("Invalid HTTPS port.");
        auto n = std::stoul(port);
        if (n == 0 || n > 65535) throw std::runtime_error("Invalid HTTPS port.");
        result.port = static_cast<unsigned short>(n);
        result.host.resize(colon);
    }
    if (result.host.empty()) throw std::runtime_error("Empty HTTPS hostname.");
    result.path = slash == std::string::npos ? "/" : url.substr(slash);
    if (result.path[0] != '/') result.path.insert(0, "/");
    auto fragment = result.path.find('#');
    if (fragment != std::string::npos) result.path.resize(fragment);
    if (result.path.empty()) result.path = "/";
    return result;
}
struct socket_handle {
    SOCKET value = INVALID_SOCKET;
    int last_error = 0;
    socket_handle() = default;
    socket_handle(const socket_handle&) = delete;
    ~socket_handle() { if (value != INVALID_SOCKET) closesocket(value); }
};
int send_tls(void* context, const unsigned char* bytes, size_t size) {
    auto& socket = *static_cast<socket_handle*>(context);
    int n = send(socket.value, reinterpret_cast<const char*>(bytes), static_cast<int>((std::min)(size, size_t(INT_MAX))), 0);
    if (n == SOCKET_ERROR) { socket.last_error = WSAGetLastError(); return MBEDTLS_ERR_NET_SEND_FAILED; }
    return n;
}
int receive_tls(void* context, unsigned char* bytes, size_t size) {
    auto& socket = *static_cast<socket_handle*>(context);
    int n = recv(socket.value, reinterpret_cast<char*>(bytes), static_cast<int>((std::min)(size, size_t(INT_MAX))), 0);
    if (n == SOCKET_ERROR) { socket.last_error = WSAGetLastError(); return MBEDTLS_ERR_NET_RECV_FAILED; }
    return n;
}
void connect_socket(socket_handle& socket, const url_parts& url) {
    addrinfo hints{}; hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM; hints.ai_protocol = IPPROTO_TCP;
    addrinfo* addresses = nullptr;
    const auto service = std::to_string(url.port);
    const int resolved = getaddrinfo(url.host.c_str(), service.c_str(), &hints, &addresses);
    if (resolved) throw std::runtime_error("Winsock DNS failed: " + std::to_string(resolved));
    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> guard(addresses, freeaddrinfo);
    int last_error = 0;
    for (auto address = addresses; address; address = address->ai_next) {
        SOCKET candidate = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);
        if (candidate == INVALID_SOCKET) { last_error = WSAGetLastError(); continue; }
        u_long nonblocking = 1;
        bool connected = false;
        if (ioctlsocket(candidate, FIONBIO, &nonblocking) == 0) {
            int code = connect(candidate, address->ai_addr, static_cast<int>(address->ai_addrlen));
            last_error = code == 0 ? 0 : WSAGetLastError();
            if (!last_error) connected = true;
            else if (last_error == WSAEWOULDBLOCK || last_error == WSAEINPROGRESS) {
                fd_set write_set, error_set;
                FD_ZERO(&write_set); FD_ZERO(&error_set); FD_SET(candidate, &write_set); FD_SET(candidate, &error_set);
                timeval timeout{30, 0};
                code = select(0, nullptr, &write_set, &error_set, &timeout);
                int error_size = sizeof(last_error);
                if (code > 0 && getsockopt(candidate, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&last_error), &error_size) == 0)
                    connected = last_error == 0 && FD_ISSET(candidate, &write_set);
                else last_error = code == 0 ? WSAETIMEDOUT : WSAGetLastError();
            }
        } else last_error = WSAGetLastError();
        nonblocking = 0;
        if (connected && ioctlsocket(candidate, FIONBIO, &nonblocking) == 0) {
            DWORD timeout = 30000;
            if (setsockopt(candidate, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout)) == 0
                && setsockopt(candidate, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout)) == 0) {
                socket.value = candidate; return;
            }
            last_error = WSAGetLastError();
        }
        closesocket(candidate);
    }
    throw std::runtime_error("Winsock connect failed: " + std::to_string(last_error));
}
struct tls_connection {
    socket_handle socket;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config config;
    mbedtls_x509_crt roots;
    tls_connection() { mbedtls_ssl_init(&ssl); mbedtls_ssl_config_init(&config); mbedtls_x509_crt_init(&roots); }
    ~tls_connection() { mbedtls_ssl_free(&ssl); mbedtls_ssl_config_free(&config); mbedtls_x509_crt_free(&roots); }
    void check(int code, const char* operation) {
        if (code >= 0) return;
        char description[512]{}; mbedtls_strerror(code, description, sizeof(description));
        std::string message = std::string(operation) + ": " + description + " (" + std::to_string(code) + ").";
        const auto flags = mbedtls_ssl_get_verify_result(&ssl);
        if (flags) {
            char verification[2048]{};
            mbedtls_x509_crt_verify_info(verification, sizeof(verification), "", flags);
            message += " Certificate verification: " + std::string(verification);
        }
        if (socket.last_error) message += " Winsock error " + std::to_string(socket.last_error) + ".";
        throw std::runtime_error(message);
    }
    void open(const url_parts& url, const logger& log) {
        int parsed = mbedtls_x509_crt_parse(&roots, ca_bundle, sizeof(ca_bundle));
        // Partial parse failures also fail closed: don't silently use an incomplete root bundle.
        if (parsed != 0) { if (parsed < 0) check(parsed, "Loading CA roots"); throw std::runtime_error("Unable to parse every bundled CA root."); }
        check(mbedtls_ssl_config_defaults(&config, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT), "TLS defaults");
        mbedtls_ssl_conf_authmode(&config, MBEDTLS_SSL_VERIFY_REQUIRED);
        mbedtls_ssl_conf_ca_chain(&config, &roots, nullptr);
        check(mbedtls_ssl_setup(&ssl, &config), "TLS setup");
        check(mbedtls_ssl_set_hostname(&ssl, url.host.c_str()), "TLS hostname/SNI");
        if (log) log("Resolving and connecting to " + url.host + ":" + std::to_string(url.port));
        connect_socket(socket, url);
        mbedtls_ssl_set_bio(&ssl, &socket, send_tls, receive_tls, nullptr);
        int handshake;
        const DWORD started = GetTickCount();
        do {
            handshake = mbedtls_ssl_handshake(&ssl);
            if (GetTickCount() - started > 60000) throw std::runtime_error("TLS handshake timed out.");
        } while (handshake == MBEDTLS_ERR_SSL_WANT_READ || handshake == MBEDTLS_ERR_SSL_WANT_WRITE);
        check(handshake, "TLS handshake");
        if (mbedtls_ssl_get_verify_result(&ssl)) throw std::runtime_error("Certificate verification did not succeed.");
        if (log) log(std::string("Verified TLS connection: ") + mbedtls_ssl_get_version(&ssl) + " / " + mbedtls_ssl_get_ciphersuite(&ssl));
    }
    void write(const std::string& data) {
        size_t position = 0;
        while (position < data.size()) {
            int n = mbedtls_ssl_write(&ssl, reinterpret_cast<const unsigned char*>(data.data() + position), data.size() - position);
            if (n == MBEDTLS_ERR_SSL_WANT_READ || n == MBEDTLS_ERR_SSL_WANT_WRITE
                || n == MBEDTLS_ERR_SSL_RECEIVED_NEW_SESSION_TICKET) continue;
            check(n, "TLS write");
            if (!n) throw std::runtime_error("TLS write made no progress.");
            position += static_cast<size_t>(n);
        }
    }
};
struct reader {
    tls_connection& tls;
    std::string pending;
    bool clean_close = false;
    bool fill() {
        unsigned char bytes[32768];
        int n;
        const DWORD started = GetTickCount();
        do {
            n = mbedtls_ssl_read(&tls.ssl, bytes, sizeof(bytes));
            if (GetTickCount() - started > 60000) throw std::runtime_error("TLS read timed out.");
        } while (n == MBEDTLS_ERR_SSL_WANT_READ || n == MBEDTLS_ERR_SSL_WANT_WRITE
                || n == MBEDTLS_ERR_SSL_RECEIVED_NEW_SESSION_TICKET);
        if (n == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) { clean_close = true; return false; }
        if (!n) return false;
        tls.check(n, "TLS read");
        pending.append(reinterpret_cast<char*>(bytes), static_cast<size_t>(n)); return true;
    }
    std::string line() {
        for (;;) {
            auto end = pending.find("\r\n");
            if (end != std::string::npos) {
                if (end > max_headers) throw std::runtime_error("HTTP line too long.");
                auto result = pending.substr(0, end); pending.erase(0, end + 2); return result;
            }
            if (pending.size() > max_headers) throw std::runtime_error("HTTP line too long.");
            if (!fill()) throw std::runtime_error("Truncated HTTP headers or chunk metadata.");
        }
    }
    void exact(std::uint64_t length, const std::function<void(const char*, size_t)>& sink) {
        while (length) {
            if (pending.empty() && !fill()) throw std::runtime_error("Truncated HTTP body.");
            const auto count = static_cast<size_t>((std::min)(length, std::uint64_t(pending.size())));
            sink(pending.data(), count); pending.erase(0, count); length -= count;
        }
    }
};
std::uint64_t number(const std::string& text, unsigned base) {
    if (text.empty()) throw std::runtime_error("Empty HTTP size.");
    std::uint64_t value = 0;
    for (unsigned char c : text) {
        unsigned digit = c >= '0' && c <= '9' ? c - '0' : c >= 'a' && c <= 'f' ? c - 'a' + 10 : c >= 'A' && c <= 'F' ? c - 'A' + 10 : 255;
        if (digit >= base || value > (max_body - digit) / base) throw std::runtime_error("Invalid or excessive HTTP size.");
        value = value * base + digit;
    }
    return value;
}
std::string redirect_url(const url_parts& old, std::string location) {
    safe_text(location);
    if (location.empty()) throw std::runtime_error("Empty HTTPS redirect.");
    if (location.compare(0, 8, "https://") == 0) return location;
    if (location.compare(0, 2, "//") == 0) return "https:" + location;
    if (location.find(':') != std::string::npos) throw std::runtime_error("Non-HTTPS redirect refused.");
    if (location[0] == '/') return "https://" + old.authority + location;
    const auto path = old.path.substr(0, old.path.find('?'));
    if (location[0] == '?') return "https://" + old.authority + path + location;
    return "https://" + old.authority + path.substr(0, path.rfind('/') + 1) + location;
}
}

response get(const std::string& initial_url, const std::string& user_agent, bool headers_only,
    const receiver& receive, const logger& log) {
    std::lock_guard<std::mutex> lock(tls_mutex);
    static bool initialized = false;
    if (!initialized) {
        auto status = psa_crypto_init();
        if (status != PSA_SUCCESS) throw std::runtime_error("PSA crypto initialization failed: " + std::to_string(status));
        initialized = true;
    }
    struct winsock_session {
        winsock_session() { WSADATA data{}; int code = WSAStartup(MAKEWORD(2, 2), &data); if (code) throw std::runtime_error("WSAStartup failed: " + std::to_string(code)); }
        ~winsock_session() { WSACleanup(); }
    } winsock;
    safe_text(user_agent);
    std::string current_url = initial_url;
    for (int redirects = 0; redirects <= 5; ++redirects) {
        const auto url = parse_url(current_url);
        tls_connection tls; tls.open(url, log);
        tls.write("GET " + url.path + " HTTP/1.1\r\nHost: " + url.authority + "\r\nUser-Agent: "
            + (user_agent.empty() ? "ca2-mbedtls" : user_agent) + "\r\nAccept: */*\r\nAccept-Encoding: identity\r\nConnection: close\r\n\r\n");
        reader input{tls, {}, false};
        response result;
        bool have_length = false, chunked = false;
        std::string location;
        size_t header_bytes = 0;
        for (;;) {
            auto status = input.line();
            header_bytes += status.size() + 2;
            if ((status.compare(0, 9, "HTTP/1.1 ") && status.compare(0, 9, "HTTP/1.0 "))
                || status.size() < 12 || status[9] < '1' || status[9] > '5'
                || status[10] < '0' || status[10] > '9' || status[11] < '0' || status[11] > '9') throw std::runtime_error("Invalid HTTP status line.");
            result.status = (status[9] - '0') * 100 + (status[10] - '0') * 10 + status[11] - '0';
            result.headers = status + "\r\n";
            for (;;) {
                auto line = input.line(); header_bytes += line.size() + 2;
                if (header_bytes > max_headers) throw std::runtime_error("HTTP headers exceed 64 KiB.");
                result.headers += line + "\r\n";
                if (line.empty()) break;
                auto colon = line.find(':');
                if (!colon || colon == std::string::npos || line[0] == ' ' || line[0] == '\t') throw std::runtime_error("Malformed HTTP header.");
                const auto name = lower(line.substr(0, colon));
                const auto value = trim(line.substr(colon + 1));
                if (name == "content-length") {
                    if (have_length) throw std::runtime_error("Duplicate HTTP content length.");
                    have_length = true; result.content_length = number(value, 10);
                } else if (name == "transfer-encoding") {
                    if (chunked || lower(value) != "chunked") throw std::runtime_error("Unsupported HTTP transfer encoding.");
                    chunked = true;
                } else if (name == "content-encoding" && lower(value) != "identity") throw std::runtime_error("Unsupported HTTP content encoding.");
                else if (name == "location") location = value;
            }
            if (result.status >= 200) break;
            if (result.status == 101) throw std::runtime_error("HTTP upgrade is unsupported.");
            have_length = chunked = false; result.content_length = 0; location.clear();
        }
        if (have_length && chunked) throw std::runtime_error("Ambiguous HTTP body framing.");
        if (result.status == 301 || result.status == 302 || result.status == 303 || result.status == 307 || result.status == 308) {
            if (redirects == 5) throw std::runtime_error("Too many HTTPS redirects.");
            current_url = redirect_url(url, location);
            if (log) log("Following verified HTTPS redirect: " + current_url);
            continue;
        }
        if (log) log("HTTP status " + std::to_string(result.status));
        if (headers_only || result.status == 204 || result.status == 304) return result;
        std::uint64_t total = 0;
        auto emit = [&](const char* bytes, size_t count) {
            if (count > max_body - total) throw std::runtime_error("HTTP body exceeds 1 GiB.");
            total += count;
            if (receive) receive(reinterpret_cast<const unsigned char*>(bytes), count, result.content_length);
        };
        if (chunked) {
            for (;;) {
                auto line = input.line();
                auto count = number(line.substr(0, line.find(';')), 16);
                if (!count) {
                    size_t trailer_bytes = 0;
                    for (;;) {
                        auto trailer = input.line(); trailer_bytes += trailer.size() + 2;
                        if (trailer_bytes > max_headers) throw std::runtime_error("HTTP trailers exceed 64 KiB.");
                        if (trailer.empty()) break;
                    }
                    break;
                }
                input.exact(count, emit);
                if (!input.line().empty()) throw std::runtime_error("Invalid HTTP chunk terminator.");
            }
        } else if (have_length) input.exact(result.content_length, emit);
        else {
            do { emit(input.pending.data(), input.pending.size()); input.pending.clear(); } while (input.fill());
            if (!input.clean_close) throw std::runtime_error("TLS closed without authenticated end-of-body.");
        }
        return result;
    }
    throw std::runtime_error("Too many HTTPS redirects.");
}
}
