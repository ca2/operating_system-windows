#include "platform.h"
#include "http.h"
#include "transport.h"
#include "acme/nano/http/get.h"
#include "acme/prototype/prototype/url.h"
namespace windows { namespace nano { namespace http_mbedtls {
void http::perform(::nano::http::get* request) {
    information() << "HTTPS backend: Mbed TLS 4.1.1 with Winsock (independent of Schannel).";
    try {
        transfer_progress_function progress;
        progress = request->payload("transfer_progress_function");
        ::function<void(const ::scoped_string&)> status;
        status = request->payload("http_status_function");
        bool retryStatusVisible = false;
        auto response = ca2_tls::get_with_retry(request->m_url.as_string().c_str(), request->m_strUserAgent.c_str(),
            request->payload("only_headers").as_bool(),
            [request, progress, status, &retryStatusVisible](const unsigned char* bytes, size_t count, std::uint64_t total) {
                if (retryStatusVisible && status) { status(""); retryStatusVisible = false; }
                request->get_memory_response()->append(bytes, count);
                if (progress) {
                    const auto received = request->get_memory_response()->size();
                    progress(total ? (::f64)received / total : 0., received, total);
                }
            },
            [this](const std::string& text) { information() << text.c_str(); },
            [request, progress]() {
                auto memory = request->get_memory_response();
                if (memory) memory->set_size(0);
                if (progress) progress(0., 0, 0);
            },
            [status, &retryStatusVisible](const std::string& text) {
                retryStatusVisible = true;
                if (status) status(text.c_str());
            });
        if (retryStatusVisible && status) status("");
        request->set_status(response.status);
        request->payload("out_attributes")["http_status_code"] = (::i64)response.status;
        ::string headers(response.headers.c_str());
        request->payload("out_headers").as_property_set().parse_network_headers(headers);
        ::string_array_base lines; lines.add_lines(headers, true);
        request->property_set().parse_network_headers(lines);
    } catch (const std::exception& exception) {
        error() << exception.what();
        throw ::exception(error_failed, exception.what());
    }
}
}}}
