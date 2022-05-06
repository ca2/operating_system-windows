#pragma once


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

      void terminate_processes_by_title(const ::string & lpszName) override;
      //virtual ::file::path get_module_path(HMODULE hmodule) override;
      bool path_pid(u32& dwPid, const ::string & lpszName) override;
      bool title_pid(u32& dwPid, const ::string & lpszName) override;
      void get_all_processes(u32_array & dwa) override;
      ::file::path get_process_path(u32 dwPid) override;

      int get_pid() override;


      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      void local_machine_set_run(const ::string & pszKey, const ::string & pszCommand, const ::string& strArguments, bool bSet) override;
      void local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand, const ::string& strArguments, bool bSet) override;
      void current_user_set_run(const ::string & pszKey, const ::string & pszCommand, const ::string & strArguments, bool bSet) override;
      void current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand, const ::string& strArguments, bool bSet) override;
      void defer_register_ca2_plugin_for_mozilla() override;

      void file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension) override;
      void file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension) override;

      void file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath) override;
      void file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszCommand, const ::string & pszParam) override;
      void file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      void link_open(const string& strUrl, const string& strProfile) override;

      bool open_in_ie(const ::string & pcsz);


      void file_open(const ::file::path & path, const string & strParams = "", const ::file::path & pathFolder = "") override;

      void browse_file_open(property_set & set) override;
      void browse_file_save(property_set & set) override;
      void browse_folder(property_set & set) override;
      void browse_file_or_folder(property_set & set) override;

      virtual void enable_service() override;
      void disable_service() override;

      void start_service() override;
      void stop_service() override;

      void _getCredentialsForService(const string& strService, WCHAR* szUsername, WCHAR* szPassword);

      void enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "") override;
      void disable_service(const ::string & strServiceName) override;

      void start_service(const ::string & strServiceName) override;
      void stop_service(const ::string & strServiceName) override;

      string calc_service_name();

      comptr < IShellLinkW > _get_IShellLinkW(const ::file::path & pathLink);

      void edit_link_target(const ::file::path & path, const ::file::path & pathLink) override;
      void edit_link_folder(const ::file::path & path, const ::file::path & pathLink) override;

      bool resolve_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr) override;

      bool resolve_lnk_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr);

      bool has_alias_in_path(const char * psz, bool bNoUI = false, bool bNoMount = false) override;

      bool is_alias(const char * psz) override;


      DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags);

      bool is_remote_session() override;

      void set_file_status(const ::string & pszFileName, const ::file::file_status& status) override;



      void initialize_wallpaper_fileset(::file::set* pset, bool bAddSearch) override;

      void set_dark_mode(bool bDarkMode) override;

      virtual void set_system_dark_mode1(bool bSet);
      virtual void set_app_dark_mode1(bool bSet);

      virtual void get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      void register_user_auto_start(const string & strAppId, const string & strCommand, const string & strArguments, bool bRegister) override;

      bool is_user_auto_start(const ::string & strAppId) override;

      ::file::path get_app_path(const ::string & strAppId) override;

      void set_default_browser() override;

      void add_default_program(string_array & straExtension, string_array & straMimeType) override;

      void list_process(::file::path_array & patha, u32_array & uaPid) override;

      //virtual icon_pointer load_icon(const ::payload & payloadFile) override;

      void broadcast_environment_variable_change() override;


   };


} // namespace apex_windows



