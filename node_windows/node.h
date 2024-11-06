//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "aura_windows/node.h"


namespace node_windows
{


   class CLASS_DECL_NODE_WINDOWS node :
      virtual public ::aura_windows::node
   {
   public:


      node();


      virtual ~node();


      string get_user_name();


      // virtual bool _os_calc_app_dark_mode() override;
      //
      //
      // virtual bool _os_calc_system_dark_mode() override;
      //
      //
      virtual ::color::color get_default_color(huge_natural u) override;


      //virtual void set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha) override;


      // virtual void set_system_dark_mode1(bool bSet = true);
      //
      //
      // virtual void set_app_dark_mode1(bool bSet = true);


      virtual double get_time_zone() override;


      //virtual void get_system_time(system_time_t * psystemtime) override;


      //virtual void open_folder(::file::path& pathFolder) override;


      //virtual void register_dll(const ::file::path& pathDll) override;


      virtual void system_main() override;


   };


} // namespace node_windows



