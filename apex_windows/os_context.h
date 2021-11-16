#pragma once


//CLASS_DECL_APEX_WINDOWS HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, string strDesc, ::file::path pathIcon = nullptr, int iIcon = 0);

namespace windows
{


   class CLASS_DECL_APEX_WINDOWS os_context :
      virtual public ::os_context
   {
   public:


      os_context();
      ~os_context() override;


      string get_command_line() override;


      bool reboot() override;
      bool shutdown(bool bPowerOff) override;

      void terminate_processes_by_title(const ::string & lpszName) override;
      //virtual ::file::path get_module_path(HMODULE hmodule) override;
      bool get_pid_by_path(const ::string & lpszName, u32 & dwPid) override;
      bool get_pid_by_title(const ::string & lpszName, u32 & dwPid) override;
      void get_all_processes(u32_array & dwa) override;
      ::file::path get_process_path(u32 dwPid) override;

      int get_pid() override;


      ::payload connection_settings_get_auto_detect() override;
      ::payload connection_settings_get_auto_config_url() override;


      bool local_machine_set_run(const ::string & pszKey, const ::string & pszCommand, bool bSet) override;
      bool local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand, bool bSet) override;
      bool current_user_set_run(const ::string & pszKey, const ::string & pszCommand, bool bSet) override;
      bool current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand, bool bSet) override;
      bool defer_register_ca2_plugin_for_mozilla() override;

      bool file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension) override;
      bool file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension) override;

      bool file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath) override;
      bool file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszCommand, const ::string & pszParam) override;
      bool file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      ::e_status link_open(const string& strUrl, const string& strProfile) override;

      bool open_in_ie(const ::string & pcsz);


      bool file_open(::file::path path, string strParams = "", string strFolder = "") override;

      bool browse_file_open(property_set & set) override;
      bool browse_file_save(property_set & set) override;
      bool browse_folder(property_set & set) override;
      bool browse_file_or_folder(property_set & set) override;

      virtual ::e_status enable_service() override;
      ::e_status disable_service() override;

      ::e_status start_service() override;
      ::e_status stop_service() override;

      bool _getCredentialsForService(const string& strService, WCHAR* szUsername, WCHAR* szPassword);

      bool enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "") override;
      bool disable_service(const ::string & strServiceName) override;

      bool start_service(const ::string & strServiceName) override;
      bool stop_service(const ::string & strServiceName) override;

      string calc_service_name();


      bool resolve_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr) override;

      bool resolve_lnk_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr);


      DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags);

      bool is_remote_session() override;

      void set_file_status(const ::string & pszFileName, const ::file::file_status& status) override;



      virtual bool initialize_wallpaper_fileset(::file::set* pset, bool bAddSearch) override;

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      bool register_user_auto_start(string strId, string strCommand, bool bRegister) override;

      bool is_user_auto_start(string strId) override;

      ::file::path get_app_path(const ::string & strApp) override;

      bool set_default_browser() override;

      bool add_default_program(string_array & straExtension, string_array & straMimeType) override;

      void list_process(::file::patha & patha, u32_array & uaPid) override;

      //virtual icon_transport load_icon(const ::payload & payloadFile) override;

      ::e_status broadcast_environment_variable_change() override;


   };


} // namespace windows



