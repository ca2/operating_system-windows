#pragma once


#include "acme/_.h"
#include "acme_windows_common/_.h"


#if defined(_acme_windows_project)
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_IMPORT
#endif


namespace acme_windows
{


   class directory_context;
   class directory_system;

   class file_context;
   class file_system;


} // namespace acme_windows



