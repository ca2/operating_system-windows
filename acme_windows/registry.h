#pragma once


#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/prototype/particle.h"
#include "acme/prototype/prototype/payload.h"


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


         HKEY              m_hkey2;
         HKEY              m_hkeySub;
         ::string          m_strSubKey;


         key();
         key(HKEY hkey, const ::scoped_string& scopedstrSubKey, bool bCreate = false);
         virtual ~key();

      
         operator HKEY();

         bool open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate = false);
         bool _open(HKEY hkey, const ::scoped_string & scopedstrSubKey, bool bCreate = false);

         
         bool defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey);
         inline bool _defer_create(HKEY hkey, const ::scoped_string & scopedstrSubKey) { return _open(hkey, scopedstrSubKey, true); }


         void close();

         
         bool data(void * pvalue, const ::scoped_string & scopedstrName, DWORD & dwType, DWORD & cbData);
         bool _data(void * pvalue, const ::scoped_string & scopedstrName, DWORD & dwType, DWORD & cbData);

         void _set_data(const void* pvalue, const ::scoped_string & scopedstrName, DWORD dwType, DWORD cbData);


         bool data_type_and_size(const ::scoped_string & scopedstrName, DWORD & dwType, DWORD & cbData);
         bool _data_type_and_size(const ::scoped_string& scopedstrName, DWORD& dwType, DWORD& cbData);


         bool get(const ::scoped_string & scopedstrName, DWORD & dwData);
         bool _get(const ::scoped_string & scopedstrName, DWORD & dwData);

         
         bool get(const ::scoped_string & scopedstrName, string & strData);
         bool _get(const ::scoped_string & scopedstrName, string &strData);


         bool get(const ::scoped_string & scopedstrName, memory & mem);
         bool _get(const ::scoped_string & scopedstrName, memory & mem);


         ::payload get(const ::scoped_string & scopedstrName);


         void set(const ::scoped_string & scopedstrName, DWORD dwData);
         void _set(const ::scoped_string & scopedstrName, DWORD dwData);


         void set(const ::scoped_string & scopedstrName, const scoped_string & scopedstrData, int iType = REG_SZ);
         //void set(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrData);
         void _set(const ::scoped_string & scopedstrName, const scoped_string & scopedstrData, int iType = REG_SZ);
         //void _set(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrData);


         //void set(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrData);
         //void _set(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrData);


         void set_binary(const ::scoped_string & scopedstrName, const memory & mem);
         void _set_binary(const ::scoped_string & scopedstrName, const memory & mem);


         void erase_data(const ::scoped_string & scopedstrName);
         void _erase_data(const ::scoped_string & scopedstrName);


         void erase_key(const ::scoped_string & scopedstrKey);
         void _erase_key(const ::scoped_string& scopedstrKey);


         void erase_tree();

         
         void ls_key(string_array & stra);
         ::string_array ls_key();
         void _ls_key(string_array & stra);


         void ls_data(string_array & stra);
         ::string_array ls_data();
         void _ls_data(string_array & stra);


      };

      registry();
      ~registry() override;

      
   };


} // namespace acme_windows


//CLASS_DECL_ACME_WINDOWS void windows_registry_initialize();

//CLASS_DECL_ACME_WINDOWS int WinRegGetDataW(HKEY hkey, const ::wide_character * pSubKey, const ::wide_character * lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

//CLASS_DECL_ACME_WINDOWS string file_get_mozilla_firefox_plugin_container_path();


