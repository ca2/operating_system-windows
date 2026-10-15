#pragma once
#include <shlobj.h>
#include <wchar.h>

inline HRESULT ca2_get_known_folder_path(REFKNOWNFOLDERID id, DWORD flags, HANDLE token, PWSTR *path)
{
#ifdef __REACTOS__
   if (!path)
      return E_POINTER;
   *path = nullptr;
   if (flags)
      return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
   struct mapping { const GUID *id; int csidl; };
   const mapping folders[] = {
      {&FOLDERID_Recent, CSIDL_RECENT}, {&FOLDERID_Profile, CSIDL_PROFILE},
      {&FOLDERID_RoamingAppData, CSIDL_APPDATA}, {&FOLDERID_ProgramData, CSIDL_COMMON_APPDATA},
      {&FOLDERID_Windows, CSIDL_WINDOWS}
   };
   for (const auto &folder : folders)
   {
      if (!IsEqualGUID(id, *folder.id))
         continue;
      wchar_t buffer[MAX_PATH]{};
      HRESULT result = SHGetFolderPathW(nullptr, folder.csidl, token, SHGFP_TYPE_CURRENT, buffer);
      if (FAILED(result))
         return result;
      size_t bytes = (wcslen(buffer) + 1) * sizeof(wchar_t);
      *path = static_cast<PWSTR>(CoTaskMemAlloc(bytes));
      if (!*path)
         return E_OUTOFMEMORY;
      memcpy(*path, buffer, bytes);
      return S_OK;
   }
   return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
#else
   return SHGetKnownFolderPath(id, flags, token, path);
#endif
}
