//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace windows
{


   namespace apex
   {


      class CLASS_DECL_APEX_WINDOWS node :
         virtual public ::windows::acme::node,
         virtual public ::apex::node
      {
      public:


         node();
         virtual ~node();


         virtual ::e_status initialize(::object* pobject) override;


         string get_user_name();

         virtual ::e_status process_init();


         virtual ::e_status _001InitializeShellOpen() override;

         virtual ::e_status shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon);


         virtual bool _os_calc_app_dark_mode();

         virtual bool _os_calc_system_dark_mode();


         virtual ::color::color get_default_color(::u64 u);

         virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);

         virtual ::e_status set_system_dark_mode1(bool bSet = true);

         virtual ::e_status set_app_dark_mode1(bool bSet = true);

         virtual double get_time_zone();

         //virtual ::e_status get_system_time(system_time_t * psystemtime);

         virtual ::e_status open_folder(::file::path& pathFolder);

         virtual ::e_status register_dll(const ::file::path& pathDll);

         virtual ::e_status system_main() override;

         ::e_status get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);




         virtual string veriwell_multimedia_music_midi_get_default_library_name() override;


         virtual string multimedia_audio_mixer_get_default_library_name() override;


         virtual string multimedia_audio_get_default_library_name() override;


         virtual bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema) override;

         virtual bool set_application_installed(const ::file::path& pathExe, string strAppId, const char* pszBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema) override;

         virtual bool set_last_run_application_path(string strAppId) override;


         //virtual ::u32       get_file_attributes(const char* pFileName);
         virtual ::u32       get_current_directory(string& str);
         virtual ::u32       get_temp_path(string& str);
         virtual ::i32        reg_query_value(HKEY hkey, const char* pszSubKey, string& str);
         virtual  HICON       extract_icon(HINSTANCE hInst, const char* pszExeFileName, ::u32 nIconIndex);
         virtual  bool        delete_file(const char* pFileName);
         // virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
         //virtual  void        time_to_filetime(::matter* pobject, const ::datetime::time& time, LPFILETIME pFileTime);


         virtual string get_version();
         virtual void show_wait_cursor(bool bShow);



      };


   } // namespace apex


} // namespace node_windows



