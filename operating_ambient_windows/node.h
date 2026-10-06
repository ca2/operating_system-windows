//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
// Copied as operating_ambient by camilo on 2024-11-16 16:04 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "node_windows/node.h"


namespace operating_ambient_windows
{


   class CLASS_DECL_OPERATING_AMBIENT_WINDOWS node :
      virtual public ::node_windows::node
   {
   public:



      node();
      ~node() override;


      string get_user_name();


      // virtual bool _os_calc_app_dark_mode() override;
      //
      //
      // virtual bool _os_calc_system_dark_mode() override;
      //
      //
      virtual ::color::color get_default_color(::u64 u) override;


      //virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha) override;


      // virtual void set_system_dark_mode1(bool bSet = true);
      //
      //
      // virtual void set_app_dark_mode1(bool bSet = true);


      virtual ::f64 get_time_zone() override;


      //virtual void get_system_time(system_time_t * psystemtime) override;


      //virtual void open_folder(::file::path& pathFolder) override;


      //virtual void register_dll(const ::file::path& pathDll) override;


      virtual void system_main() override;


   };


} // namespace operating_ambient_windows



