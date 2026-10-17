#pragma once
#include "acme/_.h"
#include "acme/_operating_system.h"
#if defined(_nano_http_wininet_project)
#define CLASS_DECL_NANO_HTTP_WININET CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO_HTTP_WININET CLASS_DECL_IMPORT
#endif
