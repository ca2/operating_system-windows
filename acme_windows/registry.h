#pragma once


#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/payload.h"


#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS registry :
      virtual public ::particle
   {
   public:


      class CLASS_DECL_ACME_WINDOWS key
      {
      public:


         HKEY m_hkey;


         key();
         key(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate = false) { _open(hkey, scopedstrSubKey, bCreate); }
         virtual ~key();

      
         operator HKEY();

         bool open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate = false);
         bool _open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate = false);

         
         bool defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey);
         inline bool _defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey) { return _open(hkey, scopedstrSubKey, true); }


         void close();

         
         bool value(void * pvalue, const ::scoped_string & scopedstrValueName, DWORD & dwType, ::u32 & cbValue);
         bool _value(void * pvalue, const ::scoped_string & scopedstrValueName, DWORD & dwType, ::u32& cbValue);

         void _set_value(const void* pvalue, const ::scoped_string & scopedstrValueName, ::u32 dwType, ::u32 cbValue);


         bool value_type_and_size(const ::scoped_string & scopedstrValueName, DWORD & dwType, ::u32 & cbValue);
         bool _value_type_and_size(const ::scoped_string & scopedstrValueName, DWORD & dwType, ::u32& cbValue) { return _value(nullptr, scopedstrValueName, dwType, cbValue); }


         bool get(const ::scoped_string & scopedstrValueName, DWORD & dwValue);
         bool _get(const ::scoped_string & scopedstrValueName, DWORD & dwValue);

         
         bool get(const ::scoped_string & scopedstrValueName, string & strValue);
         bool _get(const ::scoped_string & scopedstrValueName, string &strValue);


         bool get(const ::scoped_string & scopedstrValueName, memory & mem);
         bool _get(const ::scoped_string & scopedstrValueName, memory & mem);


         ::payload get(const ::scoped_string & scopedstrValueName);


         void set(const ::scoped_string & scopedstrValueName, DWORD dwValue);
         void _set(const ::scoped_string & scopedstrValueName, DWORD dwValue);


         void set(const ::scoped_string & scopedstrValueName, const scoped_string & strValue, int iType = REG_SZ);
         //void set(const ::scoped_string & scopedstrValueName, const ::scoped_string & scopedstrValue);
         void _set(const ::scoped_string & scopedstrValueName, const scoped_string & strValue, int iType = REG_SZ);
         //void _set(const ::scoped_string & scopedstrValueName, const ::scoped_string & scopedstrValue);


         //void set(const ::scoped_string & scopedstrValueName, const ::string & pszValue);
         //void _set(const ::scoped_string & scopedstrValueName, const ::string & pszValue);


         void set_binary(const ::scoped_string & scopedstrValueName, const memory & mem);
         void _set_binary(const ::scoped_string & scopedstrValueName, const memory & mem);


         void delete_value(const ::scoped_string & scopedstrValueName);
         void _delete_value(const ::scoped_string & scopedstrValueName);


         void delete_key();
         void _delete_key();

         
         void ls_key(string_array & stra);
         inline auto ls_key() { string_array stra; ls_key(stra); return stra; }
         void _ls_key(string_array & stra);


         void ls_value(string_array & stra);
         inline auto ls_value() { string_array stra; ls_value(stra); return stra; }
         void _ls_value(string_array & stra);


      };

      registry();
      ~registry() override;

      
   };


} // namespace acme_windows


CLASS_DECL_ACME_WINDOWS void windows_registry_initialize();

CLASS_DECL_ACME_WINDOWS int WinRegGetValueW(HKEY hkey, const ::wide_character * pSubKey, const ::wide_character * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

CLASS_DECL_ACME_WINDOWS string file_get_mozilla_firefox_plugin_container_path();


