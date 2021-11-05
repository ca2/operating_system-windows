#pragma once


#include "apex/_.h"
#include "acme_windows/_.h"
#include "apex_windows_common/_.h"


#if defined(_APEX_WINDOWS_LIBRARY)
#define CLASS_DECL_APEX_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APEX_WINDOWS  CLASS_DECL_IMPORT
#endif



