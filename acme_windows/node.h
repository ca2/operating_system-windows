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


         virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension) override;



         ::e_status reboot() override;

         virtual platform_char** get_envp(wcsdup_array& a);


         



         //virtual bool memcnts();

         //virtual ::file::path memcnts_base_path();

         virtual ::e_status datetime_to_filetime(filetime_t* pFileTime, const ::datetime::time& time) override;


         virtual ::e_status last_error_to_status(DWORD dwLastError);


         virtual ::e_status ExitCode_to_status(DWORD dwExitCode);
         


         virtual string audio_get_default_library_name() override;


         virtual ::e_status on_start_system() override;

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

         string expand_env(string str) override;


         array <::serial::port_info> list_serial_ports() override;


      };


   } // namespace windows


} // namespace acme



