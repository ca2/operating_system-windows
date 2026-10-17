#pragma once
#include "acme/nano/http/http.h"
namespace windows { namespace nano { namespace http_native {
class CLASS_DECL_NANO_HTTP_WININET http : virtual public ::nano::http::http
{
public:
   void perform(::nano::http::get* request) override;
};
}}}
