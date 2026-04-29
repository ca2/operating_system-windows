#pragma once


#include "acme/_.h"
#include "acme_windows_common/_.h"


#if defined(_accessibility_windows_project)
#define CLASS_DECL_ACCESSIBILITY_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACCESSIBILITY_WINDOWS  CLASS_DECL_IMPORT
#endif


namespace accessibility_windows
{


   class application;

   class main_window;


} // namespace acme_windows



