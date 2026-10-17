#pragma once
#include "acme/nano/http/http.h"
namespace windows { namespace nano { namespace http_mbedtls {
class CLASS_DECL_NANO_HTTP_MBEDTLS_WITH_WINSOCK http : virtual public ::nano::http::http {
public:
    void perform(::nano::http::get* request) override;
};
}}}
