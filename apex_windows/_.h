#pragma once


#include "apex/_.h"
#include "acme_windows/_.h"
#include "apex_windows_common/_.h"


#if defined(_APEX_WINDOWS_LIBRARY)
#define CLASS_DECL_APEX_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APEX_WINDOWS  CLASS_DECL_IMPORT
#endif


namespace apex_windows
{


   class dir_context;
   class dir_system;


} // namespace apex_windows


//CLASS_DECL_APEX_WINDOWS HRESULT win_create_link(const widechar * pszPathObj, const widechar * pszPathLink, const widechar * pszDesc, const widechar * pszIconPath, ::i32 iIcon);



