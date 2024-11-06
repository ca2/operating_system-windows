#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/international.h"
#include "registry.h"


namespace acme_windows
{


   registry::registry()
   {

   }


   registry::~registry()
   {

   }

   
   ::payload registry::key::get(const ::scoped_string & scopedstrName)
   {

      DWORD dwType;

      DWORD cbData;

      /* auto estatus = */ _data_type_and_size(scopedstrName, dwType, cbData);

      //if (::failed(estatus))
      //{

      //   return estatus;

      //}

      if (dwType == REG_DWORD)
      {

         DWORD uData;

         auto estatus = _data(&uData, scopedstrName, dwType, cbData);

         if(!estatus)
         {

            return estatus;

         }

         return (unsigned int) uData;

      }
      else if (dwType == REG_SZ)
      {

         wstring wstrData;
       
         auto pwszData = wstrData.get_buffer(cbData);

         auto estatus = _data(pwszData, scopedstrName, dwType, cbData);

         if(!estatus)
         {

            return estatus;

         }
         
         wstrData.release_buffer();

         return string(wstrData);

      }
      else if (dwType == REG_BINARY)
      {

         ::memory memory;

         memory.set_size(cbData);

         auto estatus = _data(memory.data(), scopedstrName, dwType, cbData);
         
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

      m_hkey2 = nullptr;
      m_hkeySub = nullptr;

   }


   registry::key::key(HKEY hkey, const ::scoped_string& scopedstrSubKey, bool bCreate)
   {
      
      _open(hkey, scopedstrSubKey, bCreate); 
   
   }


   registry::key::~key()
   {

      if(m_hkeySub != nullptr)
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

         lstatus = ::RegCreateKeyW(hkey, wstring(scopedstrSubKey), &m_hkeySub);

      }
      else
      {

         lstatus = ::RegOpenKeyW(hkey, wstring(scopedstrSubKey), &m_hkeySub);
         
      }

      if (lstatus != ERROR_SUCCESS)
      {

         return false;

      }

      m_hkey2 = hkey;

      m_strSubKey = scopedstrSubKey;

      return true;

   }


   bool registry::key::data(void * pdata, const ::scoped_string & scopedstrName, DWORD & dwType, DWORD & cbData)
   { 
      
      return _data(pdata, scopedstrName, dwType, cbData);

   }


   bool registry::key::defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey) 
   { 
      
      return _defer_create(hkey, scopedstrSubKey);
   
   }

   
   void registry::key::close()
   {

      if(m_hkeySub != nullptr)
      {

         if(ERROR_SUCCESS == ::RegCloseKey(m_hkeySub))
         {

            m_hkeySub = nullptr;

         }

      }

      m_hkey2 = nullptr;

   }


   bool registry::key::_data(void* pdata, const ::scoped_string & scopedstrName, DWORD& dwType, DWORD& cbData)
   {

      if (ERROR_SUCCESS != ::RegQueryValueExW(m_hkeySub, wstring(scopedstrName), nullptr, (LPDWORD) &dwType, (unsigned char*)pdata, (LPDWORD) &cbData))
      {

         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrName, DWORD & dwData)
   {
      
      DWORD dwType;

      DWORD cbData;
      
      auto bOk = _data_type_and_size(scopedstrName, dwType, cbData);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_DWORD)
      {

         return false;

      }

      cbData = sizeof(dwData);

      bOk = _data(&dwData, scopedstrName, dwType, cbData);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrName, string &str)
   {

      DWORD dwType;

      DWORD cbData;

      bool bOk = _data_type_and_size(scopedstrName, dwType, cbData);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
      {

         return false;

      }

      wstring wstr;

      auto pwsz = wstr.get_buffer(cbData);

      bOk = _data(pwsz, scopedstrName, dwType, cbData);

      wstr.release_buffer();

      str = wstr;

      if(!bOk)
      {
         
         return false;

      }

      return true;

   }


   bool registry::key::_get(const ::scoped_string & scopedstrName, memory & mem)
   {

      DWORD dwType;

      DWORD cbData;

      auto bOk = _data_type_and_size(scopedstrName, dwType, cbData);

      if (!bOk)
      {

         return false;

      }

      if (dwType != REG_BINARY)
      {

         return false;

      }

      mem.set_size(cbData);

      bOk = _data(mem.data(), scopedstrName, dwType, cbData);

      if (!bOk)
      {

         mem.truncate(0);

         return false;

      }      
      
      return true;

   }

   
   void registry::key::_set_data(const void* pdata, const ::scoped_string & scopedstrName, DWORD dwType, DWORD cbData)
   {

      auto lstatus = ::RegSetValueExW(m_hkeySub, scopedstrName.is_empty() ? nullptr : wstring(scopedstrName), 0, dwType, (const unsigned char *) pdata, cbData);

      if (lstatus != ERROR_SUCCESS)
      {

         auto estatus = ::windows::last_error_status(lstatus);

         throw ::exception(estatus);

      }

      //return ::success;

   }


   bool registry::key::data_type_and_size(const ::scoped_string & scopedstrName, DWORD & dwType, DWORD & cbData)
   {

      return _data_type_and_size(scopedstrName, dwType, cbData);

   }


   bool registry::key::_data_type_and_size(const ::scoped_string& scopedstrName, DWORD& dwType, DWORD& cbData) 
   {
      
      return _data(nullptr, scopedstrName, dwType, cbData); 
   
   }


   //void registry::key::_set(const ::string & strDataName, const scoped_string & scopedstrData)
   //{

   //   return this->_set(strDataName, (const ::string &)scopedstrData);

   //}


   void registry::key::_set(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrData, int iType)
   {

      wstring wstr(scopedstrData);

      return _set_data(wstr.c_str(), scopedstrName, iType, (DWORD) wstr.character_count_in_bytes());

   }


   //void registry::key::_set(const ::scoped_string & scopedstrName, const ::string & pszData)
   //{

   //   return _set(pcszDataName, string(pszData));

   //}


   void registry::key::_set_binary(const ::scoped_string & scopedstrName, const memory & memData)
   {

      return _set_data(memData.data(), scopedstrName, REG_BINARY, (DWORD) memData.size());

   }


   void registry::key::_set(const ::scoped_string & scopedstrName, DWORD dwData)
   {

      return _set_data(&dwData, scopedstrName, REG_DWORD, sizeof(dwData));

   }


   bool registry::key::get(const ::scoped_string & scopedstrName, DWORD & dwData)
   { 
      
      return _get(scopedstrName, dwData);

      //__defer_throw_estatus(estatus);
   
   }


   bool registry::key::get(const ::scoped_string & scopedstrName, string & strData)
   { 
      
      return _get(scopedstrName, strData);

      //__defer_throw_estatus(estatus);
   
   }


   bool registry::key::get(const ::scoped_string & scopedstrName, memory & mem)
   { 
      
      return _get(scopedstrName, mem);
//
  ///    __defer_throw_estatus(estatus);
   
   }


   void registry::key::set(const ::scoped_string & scopedstrName, DWORD dwData)
   {
      
       _set(scopedstrName, dwData);

      //__defer_throw_estatus(estatus);

   
   }

   //void registry::key::set(const ::string & strDataName, const scoped_string & strData)
   //{

   //   this->set(strDataName, (const string &)strData);

   //}

   void registry::key::set(const ::scoped_string & scopedstrName, const scoped_string & scopedstrData, int iType)
   { 

      /*auto estatus = */ _set(scopedstrName, scopedstrData, iType);
      
      //__defer_throw_estatus(estatus);
   
   }


   //void registry::key::set(const ::string & strDataName, const ::string & strData)
   //{

   //   auto estatus = _set(strDataName, strData);

   //   __defer_throw_estatus(estatus);

   //}


   void registry::key::set_binary(const ::scoped_string & scopedstrName, const memory & mem)
   { 

      /*auto estatus =*/ _set_binary(scopedstrName, mem);
      
      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::erase_data(const ::scoped_string & scopedstrName)
   { 
      
      /*auto estatus = */ _erase_data(scopedstrName);

      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::erase_key(const ::scoped_string& scopedstrKey)
   { 

      /*auto estatus = */ _erase_key(scopedstrKey);
      
      // __defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_key(string_array & stra)
   { 

      /*auto estatus = */ _ls_key(stra);
      
      //__defer_throw_estatus(estatus);
   
   }


   void registry::key::ls_data(string_array & stra)
   {

      /*auto estatus = */ _ls_data(stra);

      //__defer_throw_estatus(estatus);

   }


   void registry::key::_erase_data(const ::scoped_string & scopedstrName)
   {

      wstring wstr(scopedstrName);

      if (ERROR_SUCCESS != ::RegDeleteValueW(m_hkeySub, (WCHAR *) wstr.c_str()))
      {

         throw ::exception(error_failed);

      }

      //return success;

   }


   void registry::key::_erase_key(const ::scoped_string& scopedstrKey)
   {

      //ASSERT(false);
      // please verify if
      // using nullptr for the data parameter
      // deletes the key.
      if (ERROR_SUCCESS != ::RegDeleteKeyW(m_hkeySub, wstring(scopedstrKey)))
      {

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   void registry::key::_ls_key(string_array & stra)
   {

      DWORD dwMaxSubKeyLen;

      RegQueryInfoKey(
      m_hkeySub,
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
      int iSize = maximum(dwMaxSubKeyLen, 1024u);
      wchar_t *buf = (wchar_t *) malloc(iSize * 2);
      int iKey = 0;
      while(::RegEnumKeyW(m_hkeySub, iKey, buf, iSize) == ERROR_SUCCESS)
      {
         stra.add(string(buf));
         iKey++;
      }
      free(buf);
      //return iKey;
   }


   ::string_array registry::key::ls_key()
   { 
      
      string_array stra; 
      
      ls_key(stra); 
      
      return stra; 
   
   }


   registry::key::operator HKEY()
   {
      
      return m_hkeySub;

   }


   void registry::key::_ls_data(string_array & stra)
   {
      
      DWORD dwMaxDataNameLen = 16384;

      wstring hwstr;
      
      auto pwsz=hwstr.get_buffer(dwMaxDataNameLen * 2);

      int l;

      DWORD dwIndex = 0;

      DWORD dwLen = dwMaxDataNameLen;

      while(ERROR_SUCCESS == (l = ::RegEnumValueW(
                                  m_hkeySub,
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

         dwLen = dwMaxDataNameLen;

      }
      
      //return ::success;

   }


   ::string_array registry::key::ls_data()
   { 
      
      string_array stra; 
      
      ls_data(stra); 
      
      return stra; 
   
   }


   //int reg_query_data(HKEY hkey, const ::string & pszSubKey, string & str)
   //{

   //   DWORD dwType = 0;
   //   DWORD dwSize = 0;
   //   int lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

   //   if (lResult != ERROR_SUCCESS)
   //      return lResult;
   //   ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
   //   if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
   //   {

   //      wstring wstr;
   //      
   //      auto pwsz = wstr.get_buffer(dwSize/sizeof(::wide_character));

   //      lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (unsigned char *)(unichar *)pwsz, &dwSize);

   //      wstr.release_buffer(dwSize / sizeof(::wide_character));

   //      str = wstr;

   //      //str.release_buffer(dwSize);

   //      return lResult;

   //   }
   //   else
   //   {

   //      return ERROR_NOT_SUPPORTED;

   //   }

   //}

   
   void registry::key::erase_tree()
   {

      //HKEY hkeySub = nullptr;

      //if (ERROR_SUCCESS == ::RegOpenKeyW(hkey, wstring(name), &hkeySub))
      {

         unsigned int dwAlloc = 1026 * 64;

         ::wstring wstr;

         auto szKey = wstr.get_buffer(dwAlloc * 2);

         unsigned int dwIndex = 0;

         while (ERROR_SUCCESS == ::RegEnumKeyW(m_hkeySub, dwIndex, szKey, dwAlloc))
         {

            wstr.release_buffer();

            key keySub;

            if (!keySub._open(m_hkeySub, string(szKey)))
            {

               throw ::exception(error_failed);

            }

            keySub.erase_tree();

            dwIndex++;

         }

         //memory_free_debug(szKey, 0);

         ::RegCloseKey(m_hkeySub);

      }

      ::RegDeleteKeyW(m_hkeySub, wstring(m_strSubKey));

   }


} // namespace acme_windows






typedef
LSTATUS
(APIENTRY * LPFN_RegGetDataW) (
   HKEY hkey,
   const ::wide_character * pSubKey,

   const ::wide_character * pData,

   unsigned int dwFlags,
   LPDWORD pdwType,
   PVOID pvData,
   LPDWORD pcbData
   );


LPFN_RegGetDataW g_pfnRegGetDataW = nullptr;


int WinRegGetDataW(HKEY hkey, const ::wide_character * pSubKey, const ::wide_character * lpData, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{

   if (g_pfnRegGetDataW != nullptr)
   {

      return g_pfnRegGetDataW(hkey, pSubKey, lpData, dwFlags, pdwType, pvData, pcbData);

   }
   else
   {

      LSTATUS lstatus = RegQueryValueExW(hkey, pSubKey, nullptr, pdwType, (unsigned char *)pvData, pcbData);

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

      unsigned int dwAlloc = 1026 * 64;

      ::wstring wstr;

      auto szKey = wstr.get_buffer(dwAlloc * 2);

      unsigned int dwIndex = 0;

      while (ERROR_SUCCESS == ::RegEnumKeyW(hkeySub, dwIndex, szKey, dwAlloc))
      {

         wstr.release_buffer();

         reg_delete_tree_dup(hkeySub, string(szKey));

         dwIndex++;

      }

      //memory_free_debug(szKey, 0);

      ::RegCloseKey(hkeySub);

   }

   ::RegDeleteKeyW(hkey, wstring(name));

}


//CLASS_DECL_ACME_WINDOWS void windows_registry_initialize()
//{
//
//   HMODULE hmoduleAdvApi32 = ::LoadLibraryW(L"AdvApi32");
//
//   g_pfnRegGetDataW = (LPFN_RegGetDataW) ::GetProcAddress(hmoduleAdvApi32, "RegGetDataW");
//
//}
//









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
      if (::WinRegGetDataW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrVersion;
      auto pwszVersion = wstrVersion.get_buffer(dwData);
      if (::WinRegGetDataW(hkeyMozillaFirefox, nullptr, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, pwszVersion, &dwData) != ERROR_SUCCESS)
      {
         wstrVersion.release_buffer();
         goto ret1;
      }
      wstrVersion.release_buffer();

      wstring wstrMainSubKey = wstrVersion + L"\\Main";
      dwData = 0;

      if (::WinRegGetDataW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, nullptr, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrDir;
      auto pwszDir = wstrDir.get_buffer(dwData);
      if (::WinRegGetDataW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, pwszDir, &dwData) != ERROR_SUCCESS)
      {
         wstrDir.release_buffer();
         goto ret1;
      }
      wstrDir.release_buffer();

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
            LPWSTR psz = wstr.get_buffer(_MAX_PATH);

            DWORD dwSize = _MAX_PATH * sizeof(WCHAR);
            DWORD dwType;
            int lRes = ::RegQueryValueExW(hKeyInProc, L"",
               nullptr, &dwType, (unsigned char *)psz, &dwSize);

            str.release_buffer();
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



