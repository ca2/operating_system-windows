#pragma once


#include "acme/_.h"
#include "acme_windows_common/_.h"


#if defined(_ACME_WINDOWS_LIBRARY)
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_IMPORT
#endif


//CLASS_DECL_ACME_WINDOWS void command_system(const char* psz);