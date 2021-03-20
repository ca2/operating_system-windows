//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace windows
{


   class CLASS_DECL_APEX_WINDOWS apex :
      virtual public ::apex::apex
   {
   public:


      apex();

      virtual ~apex();


      string get_user_name();

      virtual ::e_status process_init() override;
      
      virtual ::e_status shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon);


      virtual bool _os_calc_app_dark_mode();

      virtual bool _os_calc_system_dark_mode();


      virtual ::color::color get_default_color(::u64 u);

      virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);

      virtual ::e_status set_system_dark_mode1(bool bSet = true);

      virtual ::e_status set_app_dark_mode1(bool bSet = true);

      virtual double get_time_zone();

      virtual ::e_status get_system_time(system_time_t * psystemtime);

      virtual ::e_status open_folder(::file::path & pathFolder);

      virtual ::e_status register_dll(const ::file::path & pathDll);

      virtual ::e_status start();

      ::e_status get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);

   };


} // namespace node_windows



