//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme_windows/node.h"
#include "apex_windows_common/node.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS node :
      virtual public ::acme_windows::node,
      virtual public ::apex_windows_common::node
   {
   public:


      //__creatable_from_base(node, ::acme::node);


      node();
      ~node() override;


      void initialize(::particle * pparticle) override;

      string get_user_name();

      virtual void process_init();


      virtual void _001InitializeShellOpen() override;

      void shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon = -1) override;

      bool shell_link_target(::file::path& pathTarget, const ::file::path& pathLnk) override;

      bool shell_link_icon(::file::path& pathIcon, int & iIcon, const ::file::path& pathLnk) override;

      //virtual bool _os_calc_app_dark_mode();

      //virtual bool _os_calc_system_dark_mode();

      virtual ::color::color get_default_color(::u64 u);

      virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);

      virtual double get_time_zone();

      //virtual void get_system_time(system_time_t * psystemtime);

      virtual void open_folder(::file::path& pathFolder);

      virtual void register_dll(const ::file::path& pathDll);

      virtual void system_main() override;

      void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);




      virtual string veriwell_multimedia_music_midi_get_default_implementation_name() override;


      virtual string multimedia_audio_mixer_get_default_implementation_name() override;


      virtual string multimedia_audio_get_default_implementation_name() override;


      //virtual bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;

      //virtual bool set_application_installed(const ::file::path& pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;

      //virtual bool set_last_run_application_path(string strAppId) override;


      //virtual ::u32       get_file_attributes(const ::string & pFileName);
      virtual ::u32       get_current_directory(string& str);
      virtual ::u32       get_temp_path(string& str);
      virtual ::i32        reg_query_value(HKEY hkey, const ::string& pszSubKey, string& str);
      virtual  HICON       extract_icon(HINSTANCE hInst, const ::string& pszExeFileName, ::u32 nIconIndex);
      virtual  void        delete_file(const ::string& pFileName);
      // virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
      //virtual  void        time_to_filetime(::matter* pobject, const ::earth::time& time, LPFILETIME pFileTime);

      virtual string get_version();
      virtual void show_wait_cursor(bool bShow);

      void user_post(const ::procedure& procedure) override;

      void create_app_shortcut(::acme::application* papp) override;


      void on_start_application(::apex::application * papplication) override;


      virtual error_code _windows_create_link(const ::wide_character* pszPathObj, const ::wide_character* pszPathLink, const ::wide_character* pszDesc, const ::wide_character* pszIconPath, ::i32 iIcon);


      void on_create_app_shortcut(::acme::application* papplication) override;


      ::file::path app_shortcut_path(::acme::application* papplication) override;


      bool is_key_pressed(bool * pbPressed, ::user::enum_key ekey) override;


      string get_command_line() override;


      void reboot() override;
      void shutdown(bool bPowerOff) override;

      void terminate_processes_by_title(const ::string& lpszName) override;
      //virtual ::file::path get_module_path(HMODULE hmodule) override;
      ::process_identifier_array module_path_processes_identifiers(const ::scoped_string& scopedstrName) override;
      ::process_identifier_array title_processes_identifiers(const ::scoped_string& scopedstrName) override;
      ::process_identifier_array processes_identifiers() override;
      ::file::path process_identifier_module_path(::process_identifier dwPid) override;

      ::process_identifier current_process_identifier() override;


      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      void local_machine_set_run(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet) override;
      void local_machine_set_run_once(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet) override;
      void current_user_set_run(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet) override;
      void current_user_set_run_once(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet) override;
      void defer_register_ca2_plugin_for_mozilla() override;

      void file_extension_get_open_with_list_keys(string_array& straKey, const ::string& pszExtension) override;
      void file_extension_get_open_with_list_commands(string_array& straCommand, const ::string& pszExtension) override;

      void file_association_set_default_icon(const ::string& pszExtension, const ::string& pszExtensionNamingClass, const ::string& pszIconPath) override;
      void file_association_set_shell_open_command(const ::string& pszExtension, const ::string& pszExtensionNamingClass, const ::string& pszCommand, const ::string& pszParam) override;
      void file_association_get_shell_open_command(const ::string& pszExtension, string& strExtensionNamingClass, string& strCommand, string& strParam) override;

      void open_url_link_at_system_browser(const string& strUrl, const string& strProfile) override;

      bool open_in_ie(const ::string& pcsz);


      void file_open(const ::file::path& path, const string& strParams = "", const ::file::path& pathFolder = "") override;
      void hidden_start(const ::file::path& path, const string& strParams = "", const ::file::path& pathFolder = "") override;
      void hidden_run(const class time& timeWait, const ::file::path& path, const string& strParams = "", const ::file::path& pathFolder = "") override;

      //void browse_file_open(property_set & set) override;
      //void browse_file_save(property_set & set) override;
      //void browse_folder(property_set & set) override;
      //void browse_file_or_folder(property_set & set) override;

      virtual void enable_service() override;
      void disable_service() override;

      void start_service() override;
      void stop_service() override;

      void _getCredentialsForService(const string& strService, ::string& strUsername, ::string& strPassword);

      void enable_service(const ::string& strServiceName, const ::string& strDisplayName, const ::string& strCommand, const ::string& strUser = "", const ::string& strPass = "") override;
      void disable_service(const ::string& strServiceName) override;

      void start_service(const ::string& strServiceName) override;
      void stop_service(const ::string& strServiceName) override;

      string calc_service_name();

      //void edit_link_target(const ::file::path & path, const ::file::path & pathLink) override;
      //void edit_link_folder(const ::file::path & path, const ::file::path & pathLink) override;
      //void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink) override;

      //::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all) override;

      //virtual ::pointer < ::file::link > resolve_lnk_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);

      bool has_alias_in_path(const scoped_string& str, bool bNoUI = false, bool bNoMount = false) override;

      bool is_alias(const ::file::path& path) override;


      void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags);

      bool is_remote_session() override;

      void set_file_status(const ::file::path& path, const ::file::file_status& status) override;

      void initialize_wallpaper_fileset(::file::set* pset, bool bAddSearch) override;


      //virtual void set_system_dark_mode1(bool bSet);
      //virtual void set_app_dark_mode1(bool bSet);

      virtual void get_default_browser(string& strId, ::file::path& path, string& strParam) override;

      void register_user_auto_start(::acme::application * papplication, const string& strArguments, bool bRegister) override;

      bool is_user_auto_start(const ::string& strAppId) override;

      ::file::path get_app_path(const ::string& strAppId) override;

      void set_default_browser() override;

      void set_file_extension_mime_type(string_array& straExtension, string_array& straMimeType) override;

      //void list_process(::file::path_array & patha, ::process_identifier_array & uaPid) override;

      //virtual icon_pointer load_icon(const ::payload & payloadFile) override;

      void broadcast_environment_variable_change() override;


      bool has_ip4_internet() override;

      bool has_ip6_internet() override;

      
      void defer_innate_ui() override;


   };


} // namespace apex_windows



