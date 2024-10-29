// Create on 2021-03-21 20:00 <3ThomasBS_
#pragma once


#include "acme_windows_common/directory_system.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS directory_system :
      virtual public ::acme_windows_common::directory_system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCommonAppData;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;

      directory_system();
      ~directory_system() override;

      virtual void initialize(::particle * pparticle) override;


      virtual void init_system() override;

      ::file::path install() override;
      ::file::path default_install() override;
      ::file::path beforeca2() override;
      ::file::path module() override;
      ::file::path relative(::file::path path) override;
      ::string appid() override;
      ::file::path appdata() override; // appdata
      ::file::path archive() override;
      ::file::path tool() override;
      //::file::path public_system() override;
      ::file::path userconfig() override;
      ::file::path config() override;
      ::file::path local() override;
      ::file::path sensitive() override;
      ::file::path localconfig() override; // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
      ::file::path ca2roaming() override; // writable root (non-bin, non-exe)
      ::file::path ca2appdata() override; // writable root (non-bin, non-exe)
      ::file::path roaming() override;
      ::file::path program_data() override;
      ::file::path public_root() override; // writable common root (non-bin, non-exe)
      ::file::path bookmark() override;
      ::file::path home() override;
      ::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode) override;
      ::file::path program_files_x86() override;
      ::file::path program_files() override;
      //::file::path program_data() override;
      ::file::path stage(string strAppId, string strPlatform, string strConfiguration) override;
      ::file::path sys_temp() override;
      ::string dir_root() override;
      ::file::path temp() override;
      //::file::path home() override;
      //::file::path program_data() override;
      //::file::path roaming() override;
      ::file::path get_memory_map_base_folder_path() override;
      //::file::path ca2appdata() override;
      //::file::path ca2roaming() override;
      //::file::path localconfig() override;
      string system_short_name() override;


      //::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration) override;
      //::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration) override;
      ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration) override;
      ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration) override;


      void set_path_install_folder(const ::string & pszPath) override;

      bool _shell_get_special_folder_path(HWND hwnd, ::file::path& str, i32 csidl, bool fCreate);
      ::file::path _shell_get_special_folder_path(i32 csidl, bool fCreate = true, ::windowing::window* pwindow = nullptr);
      ::file::path _get_known_folder(REFKNOWNFOLDERID kfid);

      //::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode) override;

      ::file::path user_appdata_local() override;

      // bool _is(const char * path1) override;



// From acme/filesystem/file/dir.cpp by camilo 
// From acme_posix/directory_system.h
// on 2021-08-09 03:20 BRT
// <3ThomasBorregaardSorensen!!


// namespace posix
// {


// class CLASS_DECL_ACME_POSIX directory_system :
// virtual public ::directory_system
// {

// public:

// directory_system();
// ~directory_system() override;

      //virtual string name(const char * path1) override;


      //virtual ::file::path module_folder() override;
      
      //bool create(const char * path) override;

      //void __create(const char * path) override;

      //bool create_directory(const char * path) override;

      //void _create_directory(const char * path) override;

      //bool is(const char * path) override;

      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing & listing) override;

      //void rls_dir(::file::path_array & stra, const scoped_string & str) override;

      //void ls(::file::path_array & stra, const scoped_string & str) override;

      //void ls_dir(::file::path_array & stra, const scoped_string & str) override;

      //void ls_file(::file::path_array & stra, const scoped_string & str) override;

      //int make_path(const scoped_string & str) override;

      ::file::path get_current() override;
      void change_current(const ::file::path & path) override;


      //::file::path temp() override;


      //::file::path msys2() override;

      ::file::path windows() override;

      ::file::path system_drive() override;


      ::file::path ___fonts() override;
      ::file::path fonts() override;


   };


} // namespace acme_windows



