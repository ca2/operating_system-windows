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


      //__creatable_from_base(node, ::platform::node);


      node();
      ~node() override;


      void initialize(::particle * pparticle) override;

      string get_user_name();

      virtual void process_init();


      virtual void _001InitializeShellOpen() override;

      void shell_create_link(::file::path pathObj, ::file::path pathLnk, const ::scoped_string & scopedstrDesc, ::file::path pathIco, int iIcon = -1) override;

      bool shell_link_target(::file::path& pathTarget, const ::file::path& pathLnk) override;

      bool shell_link_icon(::file::path& pathIcon, int & iIcon, const ::file::path& pathLnk) override;

      //virtual bool _os_calc_app_dark_mode();

      //virtual bool _os_calc_system_dark_mode();

      virtual ::color::color get_default_color(unsigned long long u);

      virtual void set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha);

      virtual double get_time_zone();

      //virtual void get_system_time(system_time_t * psystemtime);

      virtual void open_folder(::file::path& pathFolder);

      virtual void register_dll(const ::file::path& pathDll);

      virtual void system_main() override;

      void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);




      virtual string veriwell_multimedia_music_midi_get_default_implementation_name() override;


      virtual string multimedia_audio_mixer_get_default_implementation_name() override;


      virtual string multimedia_audio_get_default_implementation_name() override;


      //virtual bool is_application_installed(const ::file::path& pathExe, const ::scoped_string & scopedstrAppId, string& strBuild, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      //virtual bool set_application_installed(const ::file::path& pathExe, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrBuild, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;

      //virtual bool set_last_run_application_path(const ::scoped_string & scopedstrAppId) override;


      //virtual unsigned int       get_file_attributes(const ::scoped_string & scopedstrFileName);
      virtual unsigned int       get_current_directory(string& str);
      virtual unsigned int       get_temp_path(string& str);
      virtual int        reg_query_value(HKEY hkey, const ::scoped_string & scopedstrSubKey, string& str);
      virtual  HICON       extract_icon(HINSTANCE hInst, const ::scoped_string & scopedstrExeFileName, unsigned int nIconIndex);
      virtual  void        delete_file(const ::string& pFileName);
      // virtual  int     get_menu_string(HMENU hMenu, unsigned int uDItem, string& str, unsigned int flags);
      //virtual  void        time_to_filetime(::matter* pobject, const ::earth::time& time, LPFILETIME pFileTime);

      virtual string get_version();
      virtual void show_wait_cursor(bool bShow);

      void _user_post(const ::procedure& procedure) override;

      void create_app_shortcut(::platform::application* papp) override;


      void on_start_application(::apex::application * papplication) override;


      virtual error_code _windows_create_link(const ::wide_character* pszPathObj, const ::wide_character* pszPathLink, const ::wide_character* pszDesc, const ::wide_character* pszIconPath, int iIcon);


      void on_create_app_shortcut(::platform::application* papplication) override;


      ::file::path app_shortcut_path(::platform::application* papplication) override;


      bool is_key_pressed(bool * pbPressed, ::user::enum_key ekey) override;


      string get_command_line() override;


      void reboot() override;
      void shutdown(bool bPowerOff) override;

      void terminate_processes_by_title(const ::scoped_string & scopedstrName) override;
      //virtual ::file::path get_module_path(HMODULE hmodule) override;
      ::process_identifier_array module_path_processes_identifiers(const ::scoped_string& scopedstrName) override;
      ::process_identifier_array title_processes_identifiers(const ::scoped_string& scopedstrName) override;
      ::process_identifier_array processes_identifiers() override;
      ::file::path process_identifier_module_path(::process_identifier dwPid) override;

      ::process_identifier current_process_identifier() override;


      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      void local_machine_set_run(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void current_user_set_run(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void defer_register_ca2_plugin_for_mozilla() override;

      void file_extension_get_open_with_list_keys(string_array& straKey, const ::scoped_string & scopedstrExtension) override;
      void file_extension_get_open_with_list_commands(string_array& straCommand, const ::scoped_string & scopedstrExtension) override;

      void file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::file::path & pathIcon) override;
      void file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::file::path & pathExecutable, const ::scoped_string & scopedstrParam) override;
      void file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string& strExtensionNamingClass, string& strCommand, string& strParam) override;

      void open_internet_link(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrProfile, const ::scoped_string& scopedstTarget) override;

      bool open_in_ie(const ::scoped_string & scopedstr);


      void file_open(const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "") override;
      void hidden_start(const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "") override;
      void hidden_run(const class time& timeWait, const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "") override;

      //void browse_file_open(::property_set & set) override;
      //void browse_file_save(::property_set & set) override;
      //void browse_folder(::property_set & set) override;
      //void browse_file_or_folder(::property_set & set) override;

      virtual void enable_service() override;
      void disable_service() override;

      void start_service() override;
      void stop_service() override;

      void _getCredentialsForService(const ::scoped_string & scopedstrService, ::string& strUsername, ::string& strPassword);

      void enable_service(const ::scoped_string & scopedstrServiceName, const ::scoped_string & scopedstrDisplayName, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrUser = "", const ::scoped_string & scopedstrPass = "") override;
      void disable_service(const ::scoped_string & scopedstrServiceName) override;

      void start_service(const ::scoped_string & scopedstrServiceName) override;
      void stop_service(const ::scoped_string & scopedstrServiceName) override;

      string calc_service_name();

      //void edit_link_target(const ::file::path & path, const ::file::path & pathLink) override;
      //void edit_link_folder(const ::file::path & path, const ::file::path & pathLink) override;
      //void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink) override;

      //::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all) override;

      //virtual ::pointer < ::file::link > resolve_lnk_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);

      bool has_alias_in_path(const scoped_string& str, bool bNoUI = false, bool bNoMount = false) override;

      bool is_alias(const ::file::path& path) override;


      void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags);

      bool is_remote_session() override;

      void set_file_status(const ::file::path& path, const ::file::file_status& status) override;

      void initialize_wallpaper_fileset(::file::set* pset, bool bAddSearch) override;


      //virtual void set_system_dark_mode1(bool bSet);
      //virtual void set_app_dark_mode1(bool bSet);

      virtual void get_default_browser(string& strId, ::file::path& path, string& strParam) override;

      void register_user_auto_start(::platform::application * papplication, const ::scoped_string & scopedstrArguments, bool bRegister) override;

      bool is_user_auto_start(const ::scoped_string & scopedstrAppId) override;

      ::file::path get_app_path(const ::scoped_string & scopedstrAppId) override;

      void set_default_browser() override;

      void set_file_extension_mime_type(string_array& straExtension, string_array& straMimeType) override;

      //void list_process(::file::path_array & patha, ::process_identifier_array & uaPid) override;

      //virtual icon_pointer load_icon(const ::payload & payloadFile) override;

      void broadcast_environment_variable_change() override;


      bool has_ip4_internet() override;

      bool has_ip6_internet() override;

      
      void defer_innate_ui() override;

      ::string get_host_name() override;

   };


} // namespace apex_windows



