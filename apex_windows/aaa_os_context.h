#pragma once


#include "apex/platform/os_context.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS os_context :
      virtual public ::os_context
   {
   public:


      //__creatable_from_base(os_context, ::os_context);


      os_context();
      ~os_context() override;


      string get_command_line() override;


      void reboot() override;
      void shutdown(bool bPowerOff) override;

      void terminate_processes_by_title(const ::scoped_string & scopedstrName) override;
      //virtual ::file::path get_module_path(HMODULE hmodule) override;
      ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrName) override;
      ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName) override;
      ::process_identifier_array processes_identifiers() override;
      ::file::path process_identifier_module_path(::process_identifier dwPid) override;

      ::process_identifier current_process_identifier() override;


      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      void local_machine_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void current_user_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet) override;
      void defer_register_ca2_plugin_for_mozilla() override;

      void file_extension_get_open_with_list_keys(string_array_base & straKey, const ::scoped_string & scopedstrExtension) override;
      void file_extension_get_open_with_list_commands(string_array_base & straCommand, const ::scoped_string & scopedstrExtension) override;

      void file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath) override;
      void file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam) override;
      void file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      void link_open(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile) override;

      bool open_in_ie(const ::scoped_string & scopedstr);


      void file_open(const ::file::path & path, const ::scoped_string & scopedstrParams = "", const ::file::path & pathFolder = "") override;
      void hidden_start(const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "") override;
      void hidden_run(const class time & timeWait, const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "") override;

      //void browse_file_open(::property_set & set) override;
      //void browse_file_save(::property_set & set) override;
      //void browse_folder(::property_set & set) override;
      //void browse_file_or_folder(::property_set & set) override;

      virtual void enable_service() override;
      void disable_service() override;

      void start_service() override;
      void stop_service() override;

      void _getCredentialsForService(const ::scoped_string & scopedstrService, ::string & strUsername, ::string & strPassword);

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

      bool has_alias_in_path(const scoped_string & str, bool bNoUI = false, bool bNoMount = false) override;

      bool is_alias(const ::file::path & path) override;


      void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags);

      bool is_remote_session() override;

      void set_file_status(const ::file::path & path, const ::file::file_status& status) override;

      void initialize_wallpaper_fileset(::file::set* pset, bool bAddSearch) override;

      void set_dark_mode(bool bDarkMode) override;

      virtual void set_system_dark_mode1(bool bSet);
      virtual void set_app_dark_mode1(bool bSet);

      virtual void get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      void register_user_auto_start(const ::scoped_string & scopedstrAppId, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bRegister) override;

      bool is_user_auto_start(const ::scoped_string & scopedstrAppId) override;

      ::file::path get_app_path(const ::scoped_string & scopedstrAppId) override;

      void set_default_browser() override;

      void set_file_extension_mime_type(string_array_base & straExtension, string_array_base & straMimeType) override;

      //void list_process(::file::path_array & patha, ::process_identifier_array & uaPid) override;

      //virtual icon_pointer load_icon(const ::payload & payloadFile) override;

      void broadcast_environment_variable_change() override;


   };


} // namespace apex_windows



