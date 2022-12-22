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
         key(HKEY hkey, const ::string & pcszSubKey, bool bCreate = false) { _open(hkey, pcszSubKey, bCreate); }
         virtual ~key();

      
         operator HKEY();

         bool open(HKEY hkey, const ::string & pcszSubKey, bool bCreate = false);
         bool _open(HKEY hkey, const ::string & pcszSubKey, bool bCreate = false);

         
         bool defer_create(HKEY hkey, const ::string & pcszSubKey);
         inline bool _defer_create(HKEY hkey, const ::string & pcszSubKey) { return _open(hkey, pcszSubKey, true); }


         void close();

         
         bool value(void * pvalue, const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         bool _value(void * pvalue, const ::string & pcszValueName, ::u32& dwType, ::u32& cbValue);

         void _set_value(const void* pvalue, const ::string & pcszValueName, ::u32 dwType, ::u32 cbValue);


         bool value_type_and_size(const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         bool _value_type_and_size(const ::string & pcszValueName, ::u32& dwType, ::u32& cbValue) { return _value(nullptr, pcszValueName, dwType, cbValue); }


         bool get(const ::string & pcszValueName, ::u32 & dwValue);
         bool _get(const ::string & pcszValueName, ::u32 & dwValue);

         
         bool get(const ::string & pcszValueName, string & strValue);
         bool _get(const ::string & pcszValueName, string &strValue);


         bool get(const ::string & pcszValueName, memory & mem);
         bool _get(const ::string & pcszValueName, memory & mem);


         ::payload get(const ::string & pcszValueName);


         void set(const ::string & pcszValueName, ::u32 dwValue);
         void _set(const ::string & pcszValueName, ::u32 dwValue);


         void set(const ::string & strValueName, const scoped_string & strValue);
         void set(const ::string & strValueName, const ::string & strValue);
         void _set(const ::string & strValueName, const scoped_string & strValue);
         void _set(const ::string & strValueName, const ::string & strValue);


         //void set(const ::string & pcszValueName, const ::string & pszValue);
         //void _set(const ::string & pcszValueName, const ::string & pszValue);


         void set(const ::string & pcszValueName, const memory & mem);
         void _set(const ::string & pcszValueName, const memory & mem);


         void delete_value(const ::string & pcszValueName);
         void _delete_value(const ::string & pcszValueName);


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
      virtual ~registry();

      


      
   };


} // namespace acme_windows


CLASS_DECL_ACME_WINDOWS void windows_registry_initialize();

CLASS_DECL_ACME_WINDOWS int WinRegGetValueW(HKEY hkey, const ::wide_character * pSubKey, const ::wide_character * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

CLASS_DECL_ACME_WINDOWS string file_get_mozilla_firefox_plugin_container_path();


