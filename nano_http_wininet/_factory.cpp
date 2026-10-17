#include "platform.h"
#include "http.h"
__FACTORY_EXPORT void nano_http_wininet_factory(::factory::factory* factory)
{
   factory->add_factory_item<::windows::nano::http_native::http, ::nano::http::http>();
}
