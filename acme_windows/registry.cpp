#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/string/international.h"
#include "registry.h"


namespace acme_windows
{


   registry::registry()
   {

   }


   registry::~registry()
   {

   }

   
   ::payload registry::key::get(const ::scoped_string & scopedstrValueName)
   {

      ::u32 dwType;

      ::u32 cbValue;

      /* auto estatus = */ _value_type_and_size(scopedstrValueName, dwType, cbValue);

      //if (::failed(estatus))
      //{

      //   return estatus;

      //}

      if (dwType == REG_DWORD)
      {

         ::u32 uValue;

         auto estatus = _value(&uValue, scopedstrValueName, dwType, cbValue);

         if(!estatus)
         {

            return estatus;

         }

         return uValue;

      }
      else if (dwType == REG_SZ)
      {

         wstring wstrValue;
       
         auto pwszValue = wstrValue.get_string_buffer(cbValue);

         auto estatus = _value(pwszValue, scopedstrValueName, dwType, cbValue);

         if(!estatus)
         {

            return estatus;

         }
         
         wstrValue.release_string_buffer();

         return string(wstrValue);

      }
      else if (dwType == REG_BINARY)
      {

         ::memory memory;

         memory.set_size(cbValue);

         auto estatus = _value(memory.data(), scopedstrValueName, dwType, cbValue);
         
         if (!estatus)
         {

            return estatus;

         }

         return memory.get_string();

      }

      return ::error_wrong_type;

   }


   registry::key::key()
   {

      m_hkey = nullptr;

   }


   registry::key::~key()
   {

      if(m_hkey != nullptr)
      {

         close();

      }

   }


   bool registry::key::open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate)
   { 
      
      return _open(hkey, scopedstrSubKey, bCreate);
   
   }


   bool registry::key::_open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate)
   {

      LSTATUS lstatus;

      if(bCreate)
      {

         lstatus = ::RegCreateKeyW(hkey, wstring(scopedstrSubKey), &m_hkey);

         if (lstatus != ERROR_SUCCESS)
         {

            return false;

         }

      }
      else
      {

         lstatus = ::RegOpenKeyW(hkey, wstring(scopedstrSubKey), &m_hkey);
         
         if (lstatus != ERROR_SUCCESS)
         {

            return false;

         }

      }

      return true;

   }


   bool registry::key::value(void * pvalue, const ::scoped_string & scopedstrValueName, ::u32 & dwType, ::u32 & cbValue)
   { 
      
      return _value(pvalue, scopedstrValueName, dwType, cbValue);

   }


   bool registry::key::defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey) 
   { 
      
      return _defer_create(hkey, scopedstrSubKey);
   
   }

   
   void registry::key::close()
   {

      if(m_hkey != nullptr)
      {

         if(ERROR_SUCCESS == ::RegCloseKey(m_hkey))
         {

            m_hkey = nullptr;

         }

      }

   }


   bool registry::key::_value(void* pvalue, const ::scoped_string & scopedstrValueName, ::u32& dwType, ::u32& cbValue)
   {

      if (ERROR_SUCCESS != ::RegQueryValueExW(m_hkey, wstring(scopedstrValueName), nullptr, (LPDWORD) &dwType, (byte*)pvalue, (LPDWORD) &cbValue))
      {

         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrValueName, ::u32 & dwValue)
   {
      
      ::u32 dwType;

      ::u32 cbValue;
      
      auto bOk = _value_type_and_size(scopedstrValueName, dwType, cbValue);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_DWORD)
      {

         return false;

      }

      cbValue = sizeof(dwValue);

      bOk = _value(&dwValue, scopedstrValueName, dwType, cbValue);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrValueName, string &str)
   {

      ::u32 dwType;

      ::u32 cbValue;

      bool bOk = _value_type_and_size(scopedstrValueName, dwType, cbValue);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
      {

         return false;

      }

      wstring wstr;

      auto pwsz = wstr.get_string_buffer(cbValue);

      bOk = _value(pwsz, scopedstrValueName, dwType, cbValue);

      wstr.release_string_buffer();

      str = wstr;

      if(!bOk)
      {
         
         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrValueName, memory & mem)
   {

      ::u32 dwType;

      ::u32 cbValue;

      auto bOk = _value_type_and_size(scopedstrValueName, dwType, cbValue);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_BINARY)
      {

         return false;

      }

      mem.set_size(cbValue);

      bOk = _value(mem.data(), scopedstrValueName, dwType, cbValue);

      if (!bOk)
      {

         mem.truncate(0);

         return false;

      }      
      
      return true;

   }

   
   void registry::key::_set_value(const void* pvalue, const ::scoped_string & scopedstrValueName, ::u32 dwType, ::u32 cbValue)
   {

      auto lstatus = RegSetValueExW(m_hkey, scopedstrValueName.is_empty() ? nullptr : wstring(scopedstrValueName), 0, dwType, (const byte *) pvalue, cbValue);

      if (lstatus != ERROR_SUCCESS)
      {

         auto estatus = ::windows::last_error_status(lstatus);

         throw ::exception(estatus);

      }

      //return ::success;

   }


   bool registry::key::value_type_and_size(const ::scoped_string & scopedstrValueName, ::u32 & dwType, ::u32 & cbValue)
   {

      return _value_type_and_size(scopedstrValueName, dwType, cbValue);

   }


   //void registry::key::_set(const ::string & strValueName, const scoped_string & scopedstrValue)
   //{

   //   return this->_set(strValueName, (const ::string &)scopedstrValue);

   //}


   void registry::key::_set(const ::scoped_string & scopedstrValueName, const ::scoped_string & scopedstrValue, int iType)
   {

      wstring wstr(scopedstrValue);

      return _set_value(wstr.c_str(), scopedstrValueName, iType, (::u32) wstr.character_count_in_bytes());

   }


   //void registry::key::_set(const ::scoped_string & scopedstrValueName, const ::string & pszValue)
   //{

   //   return _set(pcszValueName, string(pszValue));

   //}


   void registry::key::_set_binary(const ::scoped_string & scopedstrValueName, const memory & memValue)
   {

      return _set_value(memValue.data(), scopedstrValueName, REG_BINARY, (::u32) memValue.size());

   }


   void registry::key::_set(const ::scoped_string & scopedstrValueName, ::u32 dwValue)
   {

      return _set_value(&dwValue, scopedstrValueName, REG_DWORD, sizeof(dwValue));

   }


   bool registry::key::get(const ::scoped_string & scopedstrValueName, ::u32 & dwValue)
   { 
      
      return _get(scopedstrValueName, dwValue);

      //__defer_throw_estatus(estatus);
   
   }


   bool registry::key::get(const ::scoped_string & scopedstrValueName, string & strValue)
   { 
      
      return _get(scopedstrValueName, strValue);

      //__defer_throw_estatus(estatus);
   
   }


   bool registry::key::get(const ::scoped_string & scopedstrValueName, memory & mem)
   { 
      
      return _get(scopedstrValueName, mem);
//
  ///    __defer_throw_estatus(estatus);
   
   }


   void registry::key::set(const ::scoped_string & scopedstrValueName, ::u32 dwValue)
   {
      
       _set(scopedstrValueName, dwValue);

      //__defer_throw_estatus(estatus);

   
   }

   //void registry::key::set(const ::string & strValueName, const scoped_string & strValue)
   //{

   //   this->set(strValueName, (const string &)strValue);

   //}

   void registry::key::set(const ::scoped_string & scopedstrValueName, const scoped_string & scopedstrValue, int iType)
   { 

      /*auto estatus = */ _set(scopedstrValueName, scopedstrValue, iType);
      
      //__defer_throw_estatus(estatus);
   
   }


   //void registry::key::set(const ::string & strValueName, const ::string & strValue)
   //{

   //   auto estatus = _set(strValueName, strValue);

   //   __defer_throw_estatus(estatus);

   //}


   void registry::key::set_binary(const ::scoped_string & scopedstrValueName, const memory & mem)
   { 

      /*auto estatus =*/ _set_binary(scopedstrValueName, mem);
      
      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::delete_value(const ::scoped_string & scopedstrValueName)
   { 
      
      /*auto estatus = */ _delete_value(scopedstrValueName);

      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::delete_key()
   { 

      /*auto estatus = */ _delete_key();
      
      // __defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_key(string_array & stra)
   { 

      /*auto estatus = */ _ls_key(stra);
      
      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_value(string_array & stra)
   {

      /*auto estatus = */ _ls_value(stra);

      //__defer_throw_estatus(estatus);

   }


   void registry::key::_delete_value(const ::scoped_string & scopedstrValueName)
   {

      wstring wstr(scopedstrValueName);

      if (ERROR_SUCCESS != ::RegDeleteValueW(m_hkey, (WCHAR *) wstr.c_str()))
      {

         throw ::exception(error_failed);

      }

      //return success;

   }


   void registry::key::_delete_key()
   {

      ASSERT(false);
      // please verify if
      // using nullptr for the value parameter
      // deletes the key.
      if (ERROR_SUCCESS != ::RegDeleteKey(m_hkey, nullptr))
      {

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   void registry::key::_ls_key(string_array & stra)
   {

      DWORD dwMaxSubKeyLen;

      RegQueryInfoKey(
      m_hkey,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &dwMaxSubKeyLen,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      nullptr);
      i32 iSize = maximum(dwMaxSubKeyLen, 1024u);
      wchar_t *buf = (wchar_t *) malloc(iSize * 2);
      i32 iKey = 0;
      while(::RegEnumKeyW(m_hkey, iKey, buf, iSize) == ERROR_SUCCESS)
      {
         stra.add(string(buf));
         iKey++;
      }
      free(buf);
      //return iKey;
   }


   registry::key::operator HKEY()
   {
      return m_hkey;
   }

   void registry::key::_ls_value(string_array & stra)
   {
      
      ::u32 dwMaxValueNameLen = 16384;

      wstring hwstr;
      
      auto pwsz=hwstr.get_string_buffer(dwMaxValueNameLen * 2);

      ::i32 l;

      DWORD dwIndex = 0;

      DWORD dwLen = dwMaxValueNameLen;

      while(ERROR_SUCCESS == (l = RegEnumValueW(
                                  m_hkey,
                                  dwIndex,
         pwsz,
                                  &dwLen,
                                  nullptr,
                                  nullptr,
                                  nullptr,
                                  nullptr)))
      {
         
         stra.add(string(pwsz, dwLen));

         dwIndex++;

         dwLen = dwMaxValueNameLen;

      }
      
      //return ::success;

   }


   ::i32 reg_query_value(HKEY hkey, const ::string & pszSubKey, string & str)
   {

      DWORD dwType = 0;
      DWORD dwSize = 0;
      ::i32 lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

      if (lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {

         wstring wstr;
         
         auto pwsz = wstr.get_string_buffer(dwSize/sizeof(::wide_character));

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (byte *)(unichar *)pwsz, &dwSize);

         wstr.release_string_buffer(dwSize / sizeof(::wide_character));

         str = wstr;

         //str.release_string_buffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }



} // namespace acme_windows






typedef
LSTATUS
(APIENTRY * LPFN_RegGetValueW) (
   HKEY hkey,
   const ::wide_character * pSubKey,

   const ::wide_character * pValue,

   u32 dwFlags,
   LPDWORD pdwType,
   PVOID pvData,
   LPDWORD pcbData
   );


LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;


int WinRegGetValueW(HKEY hkey, const ::wide_character * pSubKey, const ::wide_character * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{

   if (g_pfnRegGetValueW != nullptr)
   {

      return g_pfnRegGetValueW(hkey, pSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);

   }
   else
   {

      LSTATUS lstatus = RegQueryValueExW(hkey, pSubKey, nullptr, pdwType, (byte *)pvData, pcbData);

      if (lstatus == ERROR_SUCCESS)
      {

         if (pvData != nullptr && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
         {

            ((WCHAR *)pvData)[*pcbData] = L'\0';

         }

      }

      return lstatus;

   }

}


CLASS_DECL_ACME_WINDOWS void reg_delete_tree_dup(HKEY hkey, const char * name)
{

   HKEY hkeySub = nullptr;

   if (ERROR_SUCCESS == ::RegOpenKeyW(hkey, wstring(name), &hkeySub))
   {

      u32 dwAlloc = 1026 * 64;

      wchar_t * szKey = (wchar_t *)memory_allocate(dwAlloc * 2);

      u32 dwIndex = 0;

      while (ERROR_SUCCESS == ::RegEnumKeyW(hkeySub, dwIndex, szKey, dwAlloc))
      {

         reg_delete_tree_dup(hkeySub, string(szKey));

         dwIndex++;

      }

      memory_free_debug(szKey, 0);

      ::RegCloseKey(hkeySub);

   }

   ::RegDeleteKeyW(hkey, wstring(name));

}


CLASS_DECL_ACME_WINDOWS void windows_registry_initialize()
{

   HMODULE hmoduleAdvApi32 = ::LoadLibraryW(L"AdvApi32");

   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");

}










string file_get_mozilla_firefox_plugin_container_path()
{

   string strPath;
   HKEY hkeyMozillaFirefox;

   if (::RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Mozilla\\Mozilla Firefox", &hkeyMozillaFirefox) != ERROR_SUCCESS)
      return "";
   {

      DWORD dwType;
      DWORD dwData;
      dwData = 0;
      if (::WinRegGetValueW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrVersion;
      auto pwszVersion = wstrVersion.get_string_buffer(dwData);
      if (::WinRegGetValueW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, pwszVersion, &dwData) != ERROR_SUCCESS)
      {
         wstrVersion.release_string_buffer();
         goto ret1;
      }
      wstrVersion.release_string_buffer();

      wstring wstrMainSubKey = wstrVersion + L"\\Main";
      dwData = 0;

      if (::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrDir;
      auto pwszDir = wstrDir.get_string_buffer(dwData);
      if (::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, pwszDir, &dwData) != ERROR_SUCCESS)
      {
         wstrDir.release_string_buffer();
         goto ret1;
      }
      wstrDir.release_string_buffer();

      ::file::path strDir;

      strDir = unicode_to_utf8(wstrDir);

      strPath = strDir / "plugin-container.exe";
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}


bool CLASS_DECL_ACME_WINDOWS windows_get_in_proc_server(const ::string & pszCLSID, string & str)
{

   HKEY hKey = nullptr;
   bool b = false;
   if (RegOpenKeyW(HKEY_CLASSES_ROOT, L"CLSID", &hKey) == ERROR_SUCCESS)
   {
      HKEY hKeyCLSID = nullptr;
      if (RegOpenKeyW(hKey, wstring(pszCLSID), &hKeyCLSID) == ERROR_SUCCESS)

      {
         HKEY hKeyInProc = nullptr;
         if (RegOpenKeyW(hKeyCLSID, L"InProcServer32", &hKeyInProc) ==
            ERROR_SUCCESS)
         {
            wstring wstr;
            LPWSTR psz = wstr.get_string_buffer(_MAX_PATH);

            DWORD dwSize = _MAX_PATH * sizeof(WCHAR);
            DWORD dwType;
            ::i32 lRes = ::RegQueryValueExW(hKeyInProc, L"",
               nullptr, &dwType, (byte *)psz, &dwSize);

            str.release_string_buffer();
            str = wstr;
            b = (lRes == ERROR_SUCCESS);
            RegCloseKey(hKeyInProc);
         }
         RegCloseKey(hKeyCLSID);
      }
      RegCloseKey(hKey);
   }
   return b;
}



