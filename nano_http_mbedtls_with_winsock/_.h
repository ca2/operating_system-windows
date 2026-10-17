#pragma once
#include "acme/_.h"
#if defined(_nano_http_mbedtls_with_winsock_project)
#define CLASS_DECL_NANO_HTTP_MBEDTLS_WITH_WINSOCK CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO_HTTP_MBEDTLS_WITH_WINSOCK CLASS_DECL_IMPORT
#endif
