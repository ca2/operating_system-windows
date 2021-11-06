//
// Created by camilo on 21/01/2021. <33TBS!!
//
//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{

   
   namespace windows
   {


      class CLASS_DECL_ACME_WINDOWS node :
         virtual public ::acme::windows_common::node
      {
      public:


         ::file::path            m_strTimeFolder;
         ::file::path            m_strNetSeedFolder;

         ::file::path            m_strCommonAppData;
         ::file::path            m_strAppData;
         ::file::path            m_strPrograms;
         ::file::path            m_strCommonPrograms;


         node();
         ~node() override;


         virtual ::e_status initialize_matter(::matter* pmatter) override;

         //virtual ::string dir_root() override;

         //virtual ::file::path get_memory_map_base_folder_path() const override;

         //virtual ::file::path home() override;

         //virtual ::file::path program_data() override;

         //virtual ::file::path roaming() override;


         virtual bool win32_registry_windows_dark_mode_for_app();
         virtual bool win32_registry_windows_dark_mode_for_system();
         virtual bool win32_registry_windows_darkness();


         virtual ::color::color reinterpreted_windows_darkness_background_color();


         void fetch_user_color() override;


         virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension) override;



         ::e_status reboot() override;

         virtual platform_char** get_envp(wcsdup_array& a);


         virtual ::e_status datetime_to_filetime(filetime_t* pFileTime, const ::datetime::time& time) override;


         virtual ::e_status last_error_to_status(DWORD dwLastError);


         virtual ::e_status ExitCode_to_status(DWORD dwExitCode);


         virtual string audio_get_default_library_name() override;


         ::e_status create_process(const ::string & pszCommandLine, u32 * pprocessId) override;


         ::e_status run_silent(const ::string & strFunct, const ::string & strstrParams) override;


         bool process_modules(string_array& stra, u32 processID) override;


         bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;


         id_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;

         string module_path_from_pid(u32 pid) override;

         bool is_shared_library_busy(u32 processid, const string_array& stra) override;

         bool is_shared_library_busy(const string_array& stra) override;

         bool process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary) override;

         void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary) override;

         bool is_process_running(::u32 pid) override;

         string get_environment_variable(const ::string & pszEnvironmentVariable) override;

         string expand_environment_variables(const string & str) override;


         //virtual ::u32       get_file_attributes(const ::string & pFileName);
         virtual ::u32       get_current_directory(string& str);
         virtual ::u32       get_temp_path(string& str);
         virtual ::i32        reg_query_value(HKEY hkey, const ::string & pszSubKey, string& str);
         virtual  HICON       extract_icon(HINSTANCE hInst, const ::string & pszExeFileName, ::u32 nIconIndex);
         virtual  ::e_status        delete_file(const ::string & pFileName);
         //virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
         //virtual  void        time_to_filetime(::matter* pobject, const ::datetime::time& time, LPFILETIME pFileTime);


         array <::serial::port_info> list_serial_ports() override;

         string get_user_language() override;
         bool get_application_exclusivity_security_attributes(memory & memory) override;
         ::e_status register_spa_file_type(const ::string & strAppIdHandler) override;
         ::e_status start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;


         ::e_status get_folder_path_from_user(::file::path & pathFolder) override;


         ::e_status register_dll(const ::file::path & pathDll);


         //::string expand_environment_variables(const ::string & str) override;

         virtual ::wstring expand_environment_variables(const ::wstring & wstr);

         ::e_status implement() override;


         ::e_status on_start_system() override;


      };


   } // namespace windows


} // namespace acme



