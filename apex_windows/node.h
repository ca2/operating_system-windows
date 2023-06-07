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


      //__creatable_from_base(node, ::acme::node);


      node();
      ~node() override;


      void initialize(::particle * pparticle) override;

      string get_user_name();

      virtual void process_init();


      virtual void _001InitializeShellOpen() override;

      void shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon = -1) override;

      bool shell_link_target(::file::path& pathTarget, const ::file::path& pathLnk) override;

      bool shell_link_icon(::file::path& pathIcon, int & iIcon, const ::file::path& pathLnk) override;

      //virtual bool _os_calc_app_dark_mode();

      //virtual bool _os_calc_system_dark_mode();

      void integration_factory() override;


      virtual ::color::color get_default_color(::u64 u);

      virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);

      virtual void set_system_dark_mode1(bool bSet = true);

      virtual void set_app_dark_mode1(bool bSet = true);

      virtual double get_time_zone();

      //virtual void get_system_time(system_time_t * psystemtime);

      virtual void open_folder(::file::path& pathFolder);

      virtual void register_dll(const ::file::path& pathDll);

      virtual void system_main() override;

      void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);




      virtual string veriwell_multimedia_music_midi_get_default_implementation_name() override;


      virtual string multimedia_audio_mixer_get_default_implementation_name() override;


      virtual string multimedia_audio_get_default_implementation_name() override;


      //virtual bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;

      //virtual bool set_application_installed(const ::file::path& pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;

      //virtual bool set_last_run_application_path(string strAppId) override;


      //virtual ::u32       get_file_attributes(const ::string & pFileName);
      virtual ::u32       get_current_directory(string& str);
      virtual ::u32       get_temp_path(string& str);
      virtual ::i32        reg_query_value(HKEY hkey, const ::string& pszSubKey, string& str);
      virtual  HICON       extract_icon(HINSTANCE hInst, const ::string& pszExeFileName, ::u32 nIconIndex);
      virtual  void        delete_file(const ::string& pFileName);
      // virtual  i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
      //virtual  void        time_to_filetime(::matter* pobject, const ::earth::time& time, LPFILETIME pFileTime);

      virtual string get_version();
      virtual void show_wait_cursor(bool bShow);

      void node_post(const ::procedure& procedure) override;

      void create_app_shortcut(::acme::application* papp) override;


      void on_start_application(::apex::application * papplication) override;


      virtual error_code _windows_create_link(const ::wide_character* pszPathObj, const ::wide_character* pszPathLink, const ::wide_character* pszDesc, const ::wide_character* pszIconPath, ::i32 iIcon);


      void on_create_app_shortcut(::acme::application* papplication) override;


      ::file::path app_shortcut_path(::acme::application* papplication) override;


   };


} // namespace apex_windows



