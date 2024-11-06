#include "framework.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/adaptor.h"
#include "acme/prototype/string/international.h"
#include "acme/_operating_system.h"
#include <shellapi.h>
#include <shlobj.h>



CLASS_DECL_ACME_WINDOWS const void * get_resource_pointer(HINSTANCE hinst, DWORD nID, const char * pcszType, memsize & memsize);


HICON extract_icon(HINSTANCE hInst, const ::string& pszExeFileName, unsigned int nIconIndex)
{

   return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);

}


CLASS_DECL_ACME_WINDOWS const void* get_resource_pointer(HINSTANCE hinstance, DWORD nID, const char* pcszType, memsize& memsize)
{

   HRSRC hrsrc;

   if (::is_set(pcszType))
   {
      hrsrc = FindResourceW(hinstance, MAKEINTRESOURCEW(nID), wstring(pcszType));
   }
   else
   {
      hrsrc = FindResourceW(hinstance, MAKEINTRESOURCEW(nID), (const WCHAR*)(pcszType));
   }


   if (!hrsrc)
   {

      if (::is_set(pcszType))
      {
         hrsrc = FindResourceW(nullptr, MAKEINTRESOURCEW(nID), wstring(pcszType));
      }
      else
      {
         hrsrc = FindResourceW(nullptr, MAKEINTRESOURCEW(nID), (const WCHAR*)(pcszType));
      }
      if (!hrsrc)
      {

         if (::is_set(pcszType))
         {
            hrsrc = FindResourceW(::GetModuleHandle(NULL), MAKEINTRESOURCEW(nID), wstring(pcszType));
         }
         else
         {
            hrsrc = FindResourceW(::GetModuleHandle(NULL), MAKEINTRESOURCEW(nID), (const WCHAR*)(pcszType));
         }
      }
   }

   HGLOBAL hglobalResource;
   int_bool bOk;
   DWORD* pResource;

   if (hrsrc == nullptr)
   {

      return nullptr;

   }

   hglobalResource = LoadResource(hinstance, hrsrc);

   if (hglobalResource == nullptr)
   {

      return nullptr;

   }

   memsize = SizeofResource(hinstance, hrsrc);

   if (hglobalResource == nullptr)
   {

      return nullptr;

   }

   bOk = true;

   pResource = (DWORD*)LockResource(hglobalResource);

   return pResource;

}


CLASS_DECL_ACME_WINDOWS bool read_resource_as_memory(memory& memory, HINSTANCE hinstance, DWORD nID, const char* pcszType, character_count iReadAtMostByteCount)
{

   memsize memsize;

   auto pdata = get_resource_pointer(hinstance, nID, pcszType, memsize);

   if (::is_null(pdata))
   {

      return false;

   }

   auto iSize = minimum_non_negative(memsize, iReadAtMostByteCount);

   memory.assign(memory, iSize);

   return true;

}


bool CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(HWND hwnd, ::file::path& str, int csidl, bool fCreate)
{

   return ::SHGetSpecialFolderPathW(hwnd, wstring_adaptor(str, MAX_PATH * 8), csidl, fCreate) != false;

}


::file::path CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(int csidl, bool fCreate, ::windowing::window* pwindow)
{

   ::file::path path;

   if (!shell_get_special_folder_path(nullptr, path, csidl, fCreate))
   {

      return {};

   }

   return path;

}



