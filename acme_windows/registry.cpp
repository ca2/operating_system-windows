#include "framework.h"
#include "acme/constant/id.h"


namespace windows
{


   registry::registry()
   {

   }


   registry::~registry()
   {

   }

   
   ::payload registry::key::get(const ::string & pcszValueName)
   {

      ::u32 dwType;

      ::u32 cbValue;

      auto estatus = _value_type_and_size(pcszValueName, dwType, cbValue);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (dwType == REG_DWORD)
      {

         ::u32 uValue;

         auto estatus = _value(&uValue, pcszValueName, dwType, cbValue);

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

         auto estatus = _value(pwszValue, pcszValueName, dwType, cbValue);

         if(!estatus)
         {

            return estatus;

         }
         
         wstrValue.release_string_buffer();

         return string(wstrValue);

      }
      else if (dwType == REG_BINARY)
      {

         memory mem;

         mem.set_size(cbValue);

         auto estatus = _value(mem.get_data(), pcszValueName, dwType, cbValue);
         
         if (!estatus)
         {

            return estatus;

         }

         return mem;

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


   void registry::key::open(HKEY hkey, const ::string & pcszSubKey, bool bCreate)
   { 
      
      __defer_throw_estatus(_open(hkey, pcszSubKey, bCreate));
   
   }


   ::e_status registry::key::_open(HKEY hkey, const ::string & pcszSubKey, bool bCreate)
   {

      LSTATUS lstatus;

      if(bCreate)
      {

         lstatus = ::RegCreateKeyW(hkey, wstring(pcszSubKey), &m_hkey);

         if (lstatus != ERROR_SUCCESS)
         {

            return ::error_failed;

         }

      }
      else
      {

         lstatus = ::RegOpenKeyW(hkey, wstring(pcszSubKey), &m_hkey);
         
         if (lstatus != ERROR_SUCCESS)
         {

            return ::error_open_failed;

         }

      }

      return ::success;

   }


   void registry::key::value(void * pvalue, const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue)
   { 
      
      auto estatus = _value(pvalue, pcszValueName, dwType, cbValue); 

      __defer_throw_estatus(estatus);
   
   }


   void registry::key::defer_create(HKEY hkey, const ::string & pcszSubKey) 
   { 
      
      __defer_throw_estatus(_defer_create(hkey, pcszSubKey));
   
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



   ::e_status registry::key::_value(void* pvalue, const ::string & pcszValueName, ::u32& dwType, ::u32& cbValue)
   {

      if (ERROR_SUCCESS != ::RegQueryValueExW(m_hkey, wstring(pcszValueName), nullptr, (LPDWORD) &dwType, (byte*)pvalue, (LPDWORD) &cbValue))
      {

         return error_failed;

      }

      return ::success;

   }


   ::e_status registry::key::_get(const ::string & pcszValueName, ::u32 & dwValue)
   {
      
      ::u32 dwType;

      ::u32 cbValue;
      
      auto estatus = _value_type_and_size(pcszValueName, dwType, cbValue);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (dwType != REG_DWORD)
      {

         return error_wrong_type;

      }

      cbValue = sizeof(dwValue);

      estatus = _value(&dwValue, pcszValueName, dwType, cbValue);

      if (::failed(estatus))
      {

         return estatus;

      }

      return success;

   }


   ::e_status registry::key::_get(const ::string & pcszValueName, string &str)
   {

      ::u32 dwType;

      ::u32 cbValue;

      auto estatus = _value_type_and_size(pcszValueName, dwType, cbValue);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (dwType != REG_SZ)
      {

         return error_wrong_type;

      }

      wstring wstr;

      auto pwsz = wstr.get_string_buffer(cbValue);

      estatus = _value(pwsz, pcszValueName, dwType, cbValue);

      wstr.release_string_buffer();

      str = wstr;

      if(!estatus)
      {
         
         return estatus;

      }

      return ::success;

   }


   ::e_status registry::key::_get(const ::string & pcszValueName, memory & mem)
   {

      ::u32 dwType;

      ::u32 cbValue;

      auto estatus = _value_type_and_size(pcszValueName, dwType, cbValue);

      if (::failed(estatus))
      {

         return estatus;

      }

      if (dwType != REG_BINARY)
      {

         return error_wrong_type;

      }

      mem.set_size(cbValue);

      estatus = _value(mem.get_data(), pcszValueName, dwType, cbValue);

      if (!estatus)
      {

         mem.truncate(0);

         return estatus;

      }      
      
      return ::success;

   }

   
   ::e_status registry::key::_set_value(const void* pvalue, const ::string & pcszValueName, ::u32 dwType, ::u32 cbValue)
   {

      auto lstatus = RegSetValueExW(m_hkey, wstring(pcszValueName), 0, dwType, (const byte *) pvalue, cbValue);

      if (lstatus != ERROR_SUCCESS)
      {

         return ::error_failed;

      }

      return ::success;

   }


   void registry::key::value_type_and_size(const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue)
   {

      auto estatus = _value_type_and_size(pcszValueName, dwType, cbValue);

      __defer_throw_estatus(estatus);

   }


   ::e_status registry::key::_set(const ::string & strValueName, const char * pszValue)
   {

      return this->_set(strValueName, (const ::string &) pszValue);

   }


   ::e_status registry::key::_set(const ::string & pcszValueName, const ::string & strValue)
   {

      wstring wstr(strValue);

      return _set_value(wstr.c_str(), pcszValueName, REG_SZ, (::u32) wstr.get_length_in_bytes_with_null_terminator());

   }


   //::e_status registry::key::_set(const ::string & pcszValueName, const ::string & pszValue)
   //{

   //   return _set(pcszValueName, string(pszValue));

   //}


   ::e_status registry::key::_set(const ::string & pcszValueName, const memory & memValue)
   {

      return _set_value(memValue.get_data(), pcszValueName, REG_BINARY, (::u32) memValue.get_size());

   }


   ::e_status registry::key::_set(const ::string & pcszValueName, ::u32 dwValue)
   {

      return _set_value(&dwValue, pcszValueName, REG_DWORD, sizeof(dwValue));

   }


   void registry::key::get(const ::string & pcszValueName, ::u32 & dwValue)
   { 
      
      auto estatus = _get(pcszValueName, dwValue); 

      __defer_throw_estatus(estatus);
   
   }


   void registry::key::get(const ::string & pcszValueName, string & strValue)
   { 
      
      auto estatus = _get(pcszValueName, strValue); 

      __defer_throw_estatus(estatus);
   
   }


   void registry::key::get(const ::string & pcszValueName, memory & mem)
   { 
      
      auto estatus = _get(pcszValueName, mem); 

      __defer_throw_estatus(estatus);
   
   }


   void registry::key::set(const ::string & pcszValueName, ::u32 dwValue)
   {
      
      auto estatus = _set(pcszValueName, dwValue); 

      __defer_throw_estatus(estatus);

   
   }

   void registry::key::set(const ::string & strValueName, const char * pszValue)
   {

      this->set(strValueName, (const string &)pszValue);

   }

   void registry::key::set(const ::string & pcszValueName, const ::string & strValue)
   { 

      auto estatus = _set(pcszValueName, strValue);
      
      __defer_throw_estatus(estatus);
   
   }


   //void registry::key::set(const ::string & strValueName, const ::string & strValue)
   //{

   //   auto estatus = _set(strValueName, strValue);

   //   __defer_throw_estatus(estatus);

   //}


   void registry::key::set(const ::string & pcszValueName, const memory & mem)
   { 

      auto estatus = _set(pcszValueName, mem);
      
      __defer_throw_estatus(estatus);
   
   }


   void registry::key::delete_value(const ::string & pcszValueName)
   { 
      
      auto estatus = _delete_value(pcszValueName); 

      __defer_throw_estatus(estatus);
   
   }


   void registry::key::delete_key()
   { 

      auto estatus = _delete_key();
      
      __defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_key(string_array & stra)
   { 

      auto estatus = _ls_key(stra);
      
      __defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_value(string_array & stra)
   {

      auto estatus = _ls_value(stra);

      __defer_throw_estatus(estatus);

   }


   ::e_status registry::key::_delete_value(const ::string & pcszValueName)
   {

      wstring wstr(pcszValueName);

      if (ERROR_SUCCESS != ::RegDeleteValueW(m_hkey, (WCHAR *) wstr.c_str()))
      {

         return error_failed;

      }

      return success;

   }


   ::e_status registry::key::_delete_key()
   {

      ASSERT(false);
      // please verify if
      // using nullptr for the value parameter
      // deletes the key.
      if (ERROR_SUCCESS != ::RegDeleteKey(m_hkey, nullptr))
      {

         return error_failed;

      }

      return ::success;

   }


   ::e_status registry::key::_ls_key(string_array & stra)
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
      return iKey;
   }


   registry::key::operator HKEY()
   {
      return m_hkey;
   }

   ::e_status registry::key::_ls_value(string_array & stra)
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
      
      return ::success;

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

         natural_wstring pwsz(byte_count, dwSize);

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (byte *)(unichar *)pwsz, &dwSize);

         str = pwsz;

         //str.release_string_buffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }



} // namespace windows






typedef
LSTATUS
(APIENTRY * LPFN_RegGetValueW) (
   HKEY hkey,
   const widechar * pSubKey,

   const widechar * pValue,

   u32 dwFlags,
   LPDWORD pdwType,
   PVOID pvData,
   LPDWORD pcbData
   );


LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;


int WinRegGetValueW(HKEY hkey, const widechar * pSubKey, const widechar * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
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

      strDir = ::str::international::unicode_to_utf8(wstrDir);

      strPath = strDir / "plugin-container.exe";
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}



