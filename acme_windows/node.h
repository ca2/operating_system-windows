//
// Created by camilo on 21/01/2021. <33TBS!!
//
//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme_windows_common/node.h"
#include "acme/primitive/collection/numeric_array.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS node :
      virtual public ::acme_windows_common::node
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


      void initialize(::particle * pparticle) override;

      //virtual ::string dir_root() override;

      //virtual ::file::path get_memory_map_base_folder_path() const override;

      //virtual ::file::path home() override;

      //virtual ::file::path program_data() override;

      //virtual ::file::path roaming() override;


      //void call_async(const ::string& pszPath, const ::string& pszParam, const ::string& pszDir, ::e_display edisplay, bool bPrivileged, unsigned int* puiPid = nullptr) override;


      //void initialize_integration();

      void shell_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "") override;


      virtual bool win32_registry_windows_dark_mode_for_app();
      virtual bool win32_registry_windows_dark_mode_for_system();
      virtual bool win32_registry_windows_darkness();


      virtual ::color::color reinterpreted_windows_darkness_background_color();


      void fetch_user_color() override;


      virtual void install_crash_dump_reporting(const string & strModuleNameWithTheExeExtension) override;



      void reboot() override;

      virtual platform_char ** get_envp(wcsdup_array & a);


      //virtual void datetime_to_filetime(file_time_t* pFileTime, const ::earth::time& time) override;


      //virtual ::e_status ::windows::last_error_status(DWORD dwLastError);


      virtual ::e_status ExitCode_to_status(DWORD dwExitCode);


      virtual string audio_get_default_implementation_name() override;


      ::process_identifier create_process(const ::string & pszCommandLine) override;


      void run_silent(const ::string & strFunct, const ::string & strstrParams) override;


      ::file::path_array process_identifier_modules_paths(::process_identifier processidentifier) override;

      
      //::file::path_array modules_paths() override;


      bool load_modules_diff(string_array & straOld, string_array & straNew, const ::string & pszExceptDir) override;


      ::process_identifier_array module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;

      string process_identifier_module_path(::process_identifier processidentifier) override;

      ////bool is_shared_library_busy(::process_identifier processidentifier, const string_array & stra) override;

      ////bool is_shared_library_busy(const string_array & stra) override;
      //bool node::is_shared_library_busy(::process_identifier processidentifier, const string_array & stra)
      //{

      //   process_modules

      //      straSuffix.surround("\\");

      //   return ::windows::for_each_process_module(processidentifier, [&](auto & moduleentry32)
      //      {

      //            return !straSuffix.case_insensitive_suffixes(string(moduleentry32.szModule)) && !stra.case_insensitive_contains(string(moduleentry32.szModule));

      //      });

      //}


      //bool node::is_shared_library_busy(const string_array & stra)
      //{

      //   return ::acme_windows::predicate_process([&](auto pid)
      //      {

      //            return !is_shared_library_busy(pid, stra);

      //      });

      //}



      bool process_contains_module(string & strImage, ::process_identifier processidentifier, const ::string & pszLibrary) override;

      ::process_identifier_array shared_library_process(string_array & straProcesses, const ::string & pszLibrary) override;

      bool is_process_running(::process_identifier processidentifier) override;

      ::process_identifier_array processes_identifiers();

      ::string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;

      ::string expand_environment_variables(const ::scoped_string & scopedstr) override;

      void set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string & scopedstrValue) override;

      //virtual ::u32       get_file_attributes(const ::string & pFileName);
      //virtual ::file::path       get_current_directory();
      virtual ::i32              reg_query_value(HKEY hkey, const ::string & pszSubKey, string & str);
      virtual  HICON             extract_icon(HINSTANCE hInst, const ::string & pszExeFileName, ::u32 nIconIndex);
      virtual  void              delete_file(const ::file::path & path);
      //virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
      //virtual  void        time_to_filetime(::matter* pobject, const ::earth::time& time, LPFILETIME pFileTime);


      array <::serial::port_info> list_serial_ports() override;

      string get_user_language() override;


      ::pointer < security_attributes > get_application_exclusivity_security_attributes() override;


      void register_spa_file_type(const ::string & strAppIdHandler) override;
      void start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;


      void get_folder_path_from_user(::file::path & pathFolder) override;


      void register_dll(const ::file::path & pathDll);


      //::string expand_environment_variables(const ::string & str) override;

      virtual ::wstring expand_environment_variables(const ::wstring & wstr);

      void implement(::pointer<::acme::node> & pnode, ::pointer<::acme::system> & psystem)override;


      ::process_identifier current_process_identifier() override;


      void on_start_system() override;


      void create_app_shortcut(::acme::application * papp) override;


      //string get_local_mutex_name(const ::string& strAppId) override;
      //string get_local_id_mutex_name(const ::string& strAppId, const ::string& strId) override;
      //string get_global_mutex_name(const ::string& strAppId) override;
      //string get_global_id_mutex_name(const ::string& strAppId, const ::string& strId) override;


      void open_url(const ::string & strUrl) override;
      void shell_launch(const ::string & strUrl) override;


      bool stdin_has_input_events() override;
      void flush_stdin_input_events() override;
      void flush_stdin() override;

      //void defer_initialize_callstack() override;
      //string get_callstack(const scoped_string & strFormat, i32 iSkip, void * caller_address, int iCount) override;


      ::pointer < ::acme::exclusive > _get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr) override;
      i32 get_current_process_affinity_order() override;


      void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode) override;


      void launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount) override;


      //void shell_open(const ::file::path & path, const string & strParams = "", const ::file::path & pathFolder = {}) override;
      //void open_url(const ::string & strUrl) override; //
      //void command_system(string_array & straOutput, int & iExitCode, const scoped_string & str, enum_command_system ecommandsystem = e_command_system_none, const class time & timeTimeout = ::time::infinity(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr) override;
      int command_system(const ::scoped_string& scopedstr, const trace_function& tracefunction = nullptr) override;

      void open_terminal_and_run(const ::scoped_string& scopedstr);

      void shell_execute_async(const scoped_string & strFile, const scoped_string & strParams) override;
      void shell_execute_sync(const scoped_string & strFile, const scoped_string & strParams, const class time & timeTimeout = 1_minute) override;

      void root_execute_async(const scoped_string & strFile, const scoped_string & strParams) override;
      void root_execute_sync(const scoped_string & strFile, const scoped_string & strParams, const class time & timeTimeout = 1_minute) override;

      bool set_process_priority(::enum_priority epriority) override;
      ::string get_command_line() override;

      i32 get_current_processor_index() override;
      i32 get_current_process_maximum_affinity() override;

      //i32 get_current_process_affinity_order() override;
      ::u64 translate_processor_affinity(::i32 i) override;


      void _node_file_dialog(::file::file_dialog * pdialog) override;
      void _node_folder_dialog(::file::folder_dialog* pdialog) override;

      //::file::path library_file_name(const ::scoped_string & scopedstr) override;

      virtual ::string registry_environment_variable_to_system(const ::scoped_string & scopedstr);
      virtual ::string system_environment_variable_to_registry(const ::scoped_string & scopedstr);
      virtual int environment_variable_registry_payload_type(const ::scoped_string& scopedstr);

      ::string get_user_permanent_environment_variable(const ::scoped_string & scopedstr) override;
      void set_user_permanent_environment_variable(const ::scoped_string & scopedstr, const ::scoped_string & strPayload) override;


#ifdef WINDOWS_DESKTOP

      void _beta_use_unicode_utf8() override;

#endif

      void set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string& scopedstrCommand) override;
     

      ////void unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip) override;


      ////https ://social.msdn.microsoft.com/Forums/vstudio/en-US/45668d18-2840-4887-87e1-4085201f4103/visual-c-to-unzip-a-zip-file-to-a-specific-directory
      //// removed return type and changed error returns to exceptions
      //// replace __try __finally with at_end_of_scope
      //// changed arguments to ansi_character * and used bstring class for string conversion
      //// use of comptr to guard COM objets and variant to guard VARIANTs
      //virtual void _unzip_to_folder(const char* pszZip, const char* pszFolder);
   
      ::pointer <::operating_system::summary > operating_system_summary() override;

      void launch_app(const ::string & psz, const char ** argv, int iFlags) override;


      ::pointer < ::operating_system::application > module_path_application(const ::scoped_string & scopestr) override;



   };


} // namespace acme






