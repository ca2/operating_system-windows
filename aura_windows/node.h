//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "apex_windows/node.h"
#include "aura_windows_common/node.h"


namespace aura_windows
{


   class CLASS_DECL_AURA_WINDOWS node :
      virtual public ::apex_windows::node,
      virtual public ::aura_windows_common::node
   {
   public:


      //__creatable_from_base(node, ::platform::node);


      node();
      ~node() override;


      string get_user_name();


      virtual bool _os_calc_app_dark_mode() override;

      virtual bool _os_calc_system_dark_mode() override;


      virtual ::color::color get_default_color(huge_natural u) override;

      virtual void set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha) override;

      //virtual void set_system_dark_mode1(bool bSet = true);

      //virtual void set_app_dark_mode1(bool bSet = true);

      virtual double get_time_zone() override;

      //virtual void get_system_time(system_time_t * psystemtime) override;


      virtual void open_folder(::file::path& pathFolder) override;

      virtual void register_dll(const ::file::path& pathDll) override;


      //void implement(::pointer<::platform::node>& pnode, ::pointer<::platform::system> & psystem) override;
      //void implement(::pointer<::platform::node> & pnode, ::pointer<::platform::system> & psystem) override;

      void node_main() override;

      virtual void system_main() override;


      virtual HICON extract_resource_icon(const ::string& strPath, int& cx, int& cy, int iIcon);

      //void* HICON_from_ico_file(const ::block& block);
      void* HICON_from_image(::image::image * pimage);


      ::pointer < ::input::input > create_input() override;


   };


} // namespace aura_windows



