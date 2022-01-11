#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS registry :
      virtual public ::matter
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

         void open(HKEY hkey, const ::string & pcszSubKey, bool bCreate = false);
         void _open(HKEY hkey, const ::string & pcszSubKey, bool bCreate = false);

         
         void defer_create(HKEY hkey, const ::string & pcszSubKey);
         inline void _defer_create(HKEY hkey, const ::string & pcszSubKey) { return _open(hkey, pcszSubKey, true); }


         void close();

         
         void value(void * pvalue, const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         void _value(void * pvalue, const ::string & pcszValueName, ::u32& dwType, ::u32& cbValue);

         void _set_value(const void* pvalue, const ::string & pcszValueName, ::u32 dwType, ::u32 cbValue);


         void value_type_and_size(const ::string & pcszValueName, ::u32 & dwType, ::u32 & cbValue);
         void _value_type_and_size(const ::string & pcszValueName, ::u32& dwType, ::u32& cbValue) { return _value(nullptr, pcszValueName, dwType, cbValue); }


         void get(const ::string & pcszValueName, ::u32 & dwValue);
         void _get(const ::string & pcszValueName, ::u32 & dwValue);

         
         void get(const ::string & pcszValueName, string & strValue);
         void _get(const ::string & pcszValueName, string &strValue);


         void get(const ::string & pcszValueName, memory & mem);
         void _get(const ::string & pcszValueName, memory & mem);


         ::payload get(const ::string & pcszValueName);


         void set(const ::string & pcszValueName, ::u32 dwValue);
         void _set(const ::string & pcszValueName, ::u32 dwValue);


         void set(const ::string & strValueName, const char * pszValue);
         void set(const ::string & strValueName, const ::string & strValue);
         void _set(const ::string & strValueName, const char * pszValue);
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


} // namespace windows


CLASS_DECL_ACME_WINDOWS void windows_registry_initialize();

CLASS_DECL_ACME_WINDOWS int WinRegGetValueW(HKEY hkey, const widechar * pSubKey, const widechar * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

CLASS_DECL_ACME_WINDOWS string file_get_mozilla_firefox_plugin_container_path();


