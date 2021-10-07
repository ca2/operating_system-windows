#pragma once


#include "acme_windows_common/_acme_windows_common.h"
#include "acme/operating_system.h"
#include <Shlobj.h>
#include <shellapi.h>
#include "acme_windows_common/comptr.h"



CLASS_DECL_ACME_WINDOWS HANDLE hfile_create(
   const char * pFileName,

   ::u32                   dwDesiredAccess,
   ::u32                   dwShareMode,
   void * pSecurityAttributes,
   ::u32                   dwCreationDisposition,
   ::u32                   dwFlagsAndAttributes,
   HANDLE                  hTemplateFile
);


CLASS_DECL_ACME_WINDOWS bool ensure_file_size_handle(HANDLE h, u64 iSize);


// namespace str
// {

//    string CLASS_DECL_ACME get_window_text_timeout(oswindow oswindow, ::duration tickTimeout = 1000);

// } // namespace str


CLASS_DECL_ACME void TRACELASTERROR();



//#include "acme_windows_common/comptr.h"
bool windows_find_is_dots(WIN32_FIND_DATAW & data);


CLASS_DECL_ACME inline i32 muldiv32(i32 a, i32 b, i32 ca)
{

   return (i32) ::MulDiv((i32)a, (i32)b, (i32)ca);

}

CLASS_DECL_ACME int_bool HFILE_set_size(HANDLE h, u64 iSize);

#ifdef WINDOWS
CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);

#endif


CLASS_DECL_ACME TCHAR *** process_get_pargv();
CLASS_DECL_ACME TCHAR ** process_get_argv();
#include <fcntl.h>
#include <VersionHelpers.h>
#include <ddeml.h>
#include <share.h>
#include <io.h>
//#include <process.h>
#include <Winsvc.h>




namespace str
{

#ifdef WINDOWS

   inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

   inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);

   inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

   inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);

#endif


// #ifdef WINDOWS
//    // wd16
//    CLASS_DECL_ACME  BSTR               AllocSysString(const ansichar * pchData, strsize nDataLength) noexcept;
//    CLASS_DECL_ACME  bool               ReAllocSysString(BSTR * pbstr, const ansichar * pchData, strsize nDataLength) noexcept;

// #endif

// #ifdef WINDOWS
//    // wd32
//    inline  BSTR               AllocSysString(const wd32char * pchData, strsize nDataLength) noexcept;
//    inline  bool               ReAllocSysString(BSTR * pbstr, const wd32char * pchData, strsize nDataLength) noexcept;

// #endif


} //namespace str

CLASS_DECL_ACME string get_command_line(HANDLE handleProcess);



#ifdef WINDOWS


CLASS_DECL_ACME FILETIME __FILETIME(const ::datetime::time & time);


#endif



void __copy(payload * ppayload, const FILETIME * ptime);
void __copy(payload * ppayload, const SYSTEMTIME * ptime);





inline void __copy(payload * ppayload, const LPDWORD * lppdw)
{

   ppayload->operator = ((::u32 *)*lppdw);

}

inline void __copy(payload * ppayload, const long * plong)
{

   ppayload->operator = ((::i32)*plong);

}


inline void __copy(payload * ppayload, const DWORD * pdw)
{

   ppayload->operator = ((::u32)*pdw);

}


//inline void __copy(LPDWORD * ppdw, const payload * ppayload)
//{
//
//   *ppdw = (LPDWORD) (u32*) *ppayload;
//
//}

inline void __copy(long * plong, const payload * ppayload)
{

   *plong = (long)ppayload->i64();

}


inline void __copy(DWORD * pdw, const payload * ppayload)
{

   *pdw = ppayload->u32();

}


CLASS_DECL_ACME_WINDOWS ::file::path get_module_path(HMODULE hmodule = nullptr);
//CLASS_DECL_ACME_WINDOWS ::file::path module(HMODULE pmoduleosdata = nullptr);
CLASS_DECL_ACME_WINDOWS string read_resource_as_string(hinstance hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME_WINDOWS bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);



#include "file.h"


#include "simple_hold_handle.h"
#include "process.h"
//#include "acme/os/windows/registry.h"




inline comptr < IStream > create_istream(const memory_base & memory)
{

   return ::SHCreateMemStream(memory.get_data(), (::u32)memory.get_size());

}






CLASS_DECL_ACME bool is_valid_FILETIME(const FILETIME & ft) noexcept;


//CLASS_DECL_ACME BSTR AllocSysString(const ::string & str);





CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);


//#include "exception/engine.h"


#include "dir.h"


//#include "acme/os/windows/itemidlist.h"


//#include "top_level_enum.h"


//#include "acme/os/windows/extract_icon.h"


//#include "file_memory_map.h"


//#include "process_env_reader.h"





//#include "api.h"



namespace windows
{


   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid);


} // namespace windows


// namespace path
// {


//    CLASS_DECL_ACME::file::path module(HMODULE hmodule);


// } // namespace path


#include "acme_windows_common/_acme_windows_common.h"
#include "acme/node/operating_system/_const_console.h"
#include "acme/node/operating_system/console.h"


#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"


#include "acme_dir.h"
#include "acme_file.h"
#include "acme_path.h"


#include "file_find.h"
#include "registry.h"


#include "itemidlist.h"


#include "console.h"
#include "pipe.h"


#include "callstack.h"
//#include "exception_engine.h"


#include "shared_memory.h"


#include "file_exception.h"


#include "uac_tools.h"


#include "node.h"



