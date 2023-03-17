#pragma once



#include "acme/_operating_system.h"

//CLASS_DECL_APEX_WINDOWS bool windows_full_path(unichar * pszPathOut, const unichar * pszFileIn);

//CLASS_DECL_APEX_WINDOWS bool windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);
///CLASS_DECL_APEX_WINDOWS ::u32 vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, ::u32 nMax);

//CLASS_DECL_APEX_WINDOWS string windows_get_module_short_file_name(HINSTANCE hInst);

//CLASS_DECL_APEX_WINDOWS string windows_get_module_path(HINSTANCE hInst);

CLASS_DECL_APEX_WINDOWS string windows_get_short_file_name(const ::string & str);
///CLASS_DECL_APEX_WINDOWS void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);


#include "apex_windows_common/file_context.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS file_context :
      virtual public ::apex_windows_common::file_context
   {
   public:



      //__creatable_from_base(file_context, ::file_context);


      ::pointer<file_system>     m_pfilesystem;
      ::pointer<dir_system>      m_pdirsystem;


      file_context();
      ~file_context() override;


      void initialize(::particle * pparticle) override;


      void init_system() override;


      //virtual void get_status(const ::file::path & path, ::file::file_status & status);
      //virtual void set_status(const ::file::path & path, const ::file::file_status & status);



      //virtual bool FullPath(string & str, const ::string & pszFileIn);

      //virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      //virtual ::u32 GetFileName(const ::string & pszPathName, string & str);

      virtual string get_short_file_name(const ::string & str);
      virtual string get_module_short_file_name(HINSTANCE hinstance);

      
      ::payload length(const ::file::path & path) override;
      ::payload length(const ::file::path & path, ::payload * pvarQuery) override;

      void transfer(const ::file::path & pszNew, const ::file::path & psz) override;

      void erase(const ::file::path & psz) override;

      bool is_read_only(const ::file::path & psz) override;


      ::block get_main_resource_block() override;

      //::folder * _defer_resource_folder();
      //::file_pointer create_resource_file(const char* path) override;
      //bool resource_is_file_or_dir(const char* path) override;

      file_pointer resource_get_file(const ::file::path & path) override;

      virtual bool get_last_write_time(FILETIME * pfiletime, const ::string & strFilename);

      //void update_module_path() override;

      file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception) override;


      ::file::path dropbox_info_network_payload() override;


      //virtual ::file::path onedrive_global_ini(::particle * pparticle) override;
      //virtual ::file::path onedrive_cid_ini(::particle * pparticle) override;


   };


} // namespace apex_windows



