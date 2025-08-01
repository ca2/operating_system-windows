#pragma once


//#include "exception.h"


string get_error_message(unsigned int dwError);


//CLASS_DECL_ACME_WINDOWS bool __initialize();


//#include "system_dir.h"
//#include "system_file.h"
//
//#include "folder_watch.h"
//#include "factory_exchange.h"
//#include "uac_tools.h"
//#include "file.h"
//#include "crypto.h"
//#include "ip_enum.h"


#define NODE_THREAD(pthread) (dynamic_cast < ::windows::thread * > (dynamic_cast < thread * >(pthread)))


//
//#include "command.h"



//void CLASS_DECL_ACME_WINDOWS __cdecl _ca2_purecall();
void CLASS_DECL_ACME_WINDOWS __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);
bool CLASS_DECL_ACME_WINDOWS __windows_init();
//int CLASS_DECL_ACME_WINDOWS __windows_main(::platform::system * psystem, ::create * pmaininitdata);






//#include "file_find.h"
#include "file.h"
//#include "shell.h"
//#include "stdio_file.h"
//#include "registry.h"
//#include "os.h"


// Sanity checks for ATOMs
CLASS_DECL_ACME_WINDOWS bool __is_valid_atom(ATOM nAtom);
//CLASS_DECL_ACME_WINDOWS bool __is_valid_atom(const ::string & psz);
CLASS_DECL_ACME_WINDOWS bool __is_valid_atom(const wchar_t * psz);


/////////////////////////////////////////////////////////////////////////////
// locale-invariant comparison helpers till CRT gets that support
inline int __invariant_stricmp(const ::string &pszLeft, const ::string &pszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringA(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pszLeft,
                           -1,
                           pszRight,
                           -1) - CSTR_EQUAL;
#else
   return ansi_compare_ci(pszLeft,pszRight);
#endif
}

inline int __invariant_stricmp(const unichar *pwszLeft,const unichar *pwszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringW(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pwszLeft,
                           -1,
                           pwszRight,
                           -1) - CSTR_EQUAL;
#else
   return wide_compare_case_insensitive(pwszLeft,pwszRight);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//// Portability abstractions
//
//#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
//#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
//#define __get_dialog_control_id(oswindow)         ((unsigned int)(unsigned short)::GetDlgCtrlID(oswindow))
//#define __get_dialog_control_id_(oswindow)         ((unsigned int)(unsigned short)oswindow->GetDlgCtrlId())


//#include "pipe.h"
//#include "process.h"













CLASS_DECL_ACME_WINDOWS int delete_registry_tree_helper(HKEY hParentKey, const ::scoped_string & scopedstrKeyName);


//CLASS_DECL_ACME_WINDOWS ::pointer<::platform::application>__get_app();
CLASS_DECL_ACME_WINDOWS HINSTANCE __get_resource_handle();
CLASS_DECL_ACME_WINDOWS void __set_resource_handle(HINSTANCE hInstResource);

CLASS_DECL_ACME_WINDOWS HINSTANCE __get_resource_handle();
CLASS_DECL_ACME_WINDOWS HINSTANCE __find_string_resource_handle(unsigned int nID);



//CLASS_DECL_ACME_WINDOWS int app_main(::platform::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, char * pCmdLine, ::e_display edisplay);




//#include "tts_speaker.h"




