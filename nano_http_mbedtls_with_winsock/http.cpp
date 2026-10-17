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
        auto response = ca2_tls::get(request->m_url.as_string().c_str(), request->m_strUserAgent.c_str(),
            request->payload("only_headers").as_bool(),
            [request, progress](const unsigned char* bytes, size_t count, std::uint64_t total) {
                request->get_memory_response()->append(bytes, count);
                if (progress) {
                    const auto received = request->get_memory_response()->size();
                    progress(total ? (::f64)received / total : 0., received, total);
                }
            },
            [this](const std::string& text) { information() << text.c_str(); });
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
