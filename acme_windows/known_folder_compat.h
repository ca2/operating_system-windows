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
   // Compatibility binaries also run on recent Windows. Preserve redirected
   // known folders there without importing a Vista-only API on ReactOS/XP.
   using get_known_folder_path = HRESULT (WINAPI *)(REFKNOWNFOLDERID, DWORD, HANDLE, PWSTR *);
   const auto shell = GetModuleHandleW(L"shell32.dll");
   const auto getKnownFolderPath = shell ? reinterpret_cast<get_known_folder_path>(
      GetProcAddress(shell, "SHGetKnownFolderPath")) : nullptr;
   if (getKnownFolderPath)
   {
      const HRESULT result = getKnownFolderPath(id, flags, token, path);
      if (SUCCEEDED(result))
         return result;
      if (*path)
      {
         CoTaskMemFree(*path);
         *path = nullptr;
      }
      if (result != E_NOTIMPL && result != HRESULT_FROM_WIN32(ERROR_CALL_NOT_IMPLEMENTED)
         && result != HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED))
         return result;
   }

   struct mapping { const GUID *id; int csidl; const wchar_t *suffix; };
   const mapping folders[] = {
      {&FOLDERID_Recent, CSIDL_RECENT, L""}, {&FOLDERID_Profile, CSIDL_PROFILE, L""},
      {&FOLDERID_RoamingAppData, CSIDL_APPDATA, L""}, {&FOLDERID_ProgramData, CSIDL_COMMON_APPDATA, L""},
      {&FOLDERID_Windows, CSIDL_WINDOWS, L""},
      {&FOLDERID_Desktop, CSIDL_DESKTOPDIRECTORY, L""}, {&FOLDERID_Documents, CSIDL_PERSONAL, L""},
      {&FOLDERID_Music, CSIDL_MYMUSIC, L""}, {&FOLDERID_Pictures, CSIDL_MYPICTURES, L""},
      {&FOLDERID_Videos, CSIDL_MYVIDEO, L""},
      // XP has no Downloads CSIDL. Use the profile's Downloads subfolder.
      {&FOLDERID_Downloads, CSIDL_PROFILE, L"\\Downloads"}
   };
   for (const auto &folder : folders)
   {
      if (!IsEqualGUID(id, *folder.id))
         continue;
      wchar_t buffer[MAX_PATH]{};
      HRESULT result = SHGetFolderPathW(nullptr, folder.csidl, token, SHGFP_TYPE_CURRENT, buffer);
      if (FAILED(result))
         return result;
      const size_t length = wcslen(buffer);
      const size_t suffixLength = wcslen(folder.suffix);
      size_t bytes = (length + suffixLength + 1) * sizeof(wchar_t);
      *path = static_cast<PWSTR>(CoTaskMemAlloc(bytes));
      if (!*path)
         return E_OUTOFMEMORY;
      memcpy(*path, buffer, length * sizeof(wchar_t));
      memcpy(*path + length, folder.suffix, (suffixLength + 1) * sizeof(wchar_t));
      return S_OK;
   }
   return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
#else
   return SHGetKnownFolderPath(id, flags, token, path);
#endif
}
