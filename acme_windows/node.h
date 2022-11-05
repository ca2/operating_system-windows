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
      bool m_bInitializeCallstack;

      node();
      ~node() override;


      void initialize(::particle * pparticle) override;

      //virtual ::string dir_root() override;

      //virtual ::file::path get_memory_map_base_folder_path() const override;

      //virtual ::file::path home() override;

      //virtual ::file::path program_data() override;

      //virtual ::file::path roaming() override;


      //void call_async(const ::string& pszPath, const ::string& pszParam, const ::string& pszDir, ::e_display edisplay, bool bPrivileged, unsigned int* puiPid = nullptr) override;


      void shell_open(const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "") override;


      virtual bool win32_registry_windows_dark_mode_for_app();
      virtual bool win32_registry_windows_dark_mode_for_system();
      virtual bool win32_registry_windows_darkness();


      virtual ::color::color reinterpreted_windows_darkness_background_color();


      void fetch_user_color() override;


      virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension) override;



      void reboot() override;

      virtual platform_char** get_envp(wcsdup_array& a);


      //virtual void datetime_to_filetime(file_time_t* pFileTime, const ::earth::time& time) override;


      //virtual ::e_status ::windows::last_error_status(DWORD dwLastError);


      virtual ::e_status ExitCode_to_status(DWORD dwExitCode);


      virtual string audio_get_default_library_name() override;


      void create_process(const ::string& pszCommandLine, u32* pprocessId) override;


      void run_silent(const ::string& strFunct, const ::string& strstrParams) override;


      bool process_modules(string_array& stra, u32 processID) override;


      bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string& pszExceptDir) override;


      atom_array module_path_get_pid(const ::string& pszModulePath, bool bModuleNameIsPropertyFormatted) override;

      string module_path_from_pid(u32 pid) override;

      bool is_shared_library_busy(u32 processid, const string_array& stra) override;

      bool is_shared_library_busy(const string_array& stra) override;

      bool process_contains_module(string& strImage, ::u32 processID, const ::string& pszLibrary) override;

      void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string& pszLibrary) override;

      bool is_process_running(::u32 pid) override;

      string get_environment_variable(const ::string& pszEnvironmentVariable) override;

      string expand_environment_variables(const string& str) override;

      void set_environment_variable(const ::string& pszEnvironmentVariable, const ::string& pszValue) override;

      //virtual ::u32       get_file_attributes(const ::string & pFileName);
      virtual ::u32       get_current_directory(string& str);
      virtual ::u32       get_temp_path(string& str);
      virtual ::i32        reg_query_value(HKEY hkey, const ::string& pszSubKey, string& str);
      virtual  HICON       extract_icon(HINSTANCE hInst, const ::string& pszExeFileName, ::u32 nIconIndex);
      virtual  void        delete_file(const ::string& pFileName);
      //virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
      //virtual  void        time_to_filetime(::matter* pobject, const ::earth::time& time, LPFILETIME pFileTime);


      array <::serial::port_info> list_serial_ports() override;

      string get_user_language() override;
      
      
      ::pointer < security_attributes > get_application_exclusivity_security_attributes() override;


      void register_spa_file_type(const ::string& strAppIdHandler) override;
      void start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;


      void get_folder_path_from_user(::file::path& pathFolder) override;


      void register_dll(const ::file::path& pathDll);


      //::string expand_environment_variables(const ::string & str) override;

      virtual ::wstring expand_environment_variables(const ::wstring& wstr);

      void implement(::pointer<::acme::node> & pnode, ::pointer<::acme::system> & psystem)override;


      ::i64 get_current_process_id() override;


      void on_start_system() override;


      void create_app_shortcut(::acme::application* papp) override;


      //string get_local_mutex_name(const ::string& strAppId) override;
      //string get_local_id_mutex_name(const ::string& strAppId, const ::string& strId) override;
      //string get_global_mutex_name(const ::string& strAppId) override;
      //string get_global_id_mutex_name(const ::string& strAppId, const ::string& strId) override;


      void open_url(const ::string& strUrl) override;


      bool stdin_has_input_events() override;
      void flush_stdin_input_events() override;
      void flush_stdin() override;

      void defer_initialize_callstack() override;
      string get_callstack(const char * pszFormat, i32 iSkip, void * caller_address, int iCount) override;


      ::pointer < ::acme::exclusive > _get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr) override;
      i32 get_current_process_affinity_order() override;


      void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set, int * piExitCode) override;


      void launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount) override;
 

      //void shell_open(const ::file::path & path, const string & strParams = "", const ::file::path & pathFolder = {}) override;
      //void open_url(const ::string & strUrl) override; //
      void command_system(string_array & straOutput, int & iExitCode, const char * psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr) override;

      void shell_execute_async(const char * pszFile, const char * pszParams) override;
      void shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = minute()) override; 

      void root_execute_async(const char * pszFile, const char * pszParams) override;
      void root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = minute()) override;

               bool set_process_priority(::enum_priority epriority) override;
                ::string get_command_line() override;
             
            i32 get_current_processor_index() override;
             i32 get_current_process_maximum_affinity() override;
             
              //i32 get_current_process_affinity_order() override;
               ::u64 translate_processor_affinity(::i32 i) override;

   };


} // namespace acme






