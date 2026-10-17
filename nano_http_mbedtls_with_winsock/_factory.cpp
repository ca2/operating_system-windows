#include "platform.h"
#include "http.h"
__FACTORY_EXPORT void nano_http_mbedtls_with_winsock_factory(::factory::factory* factory) {
    factory->add_factory_item<::windows::nano::http_mbedtls::http, ::nano::http::http>();
}
