//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace aura
{


   namespace windows
   {


      class CLASS_DECL_AURA_WINDOWS node :
         virtual public ::apex::windows::node,
         virtual public ::aura::windows_common::node
      {
      public:


         //__creatable_from_base(node, ::acme::node);


         node();
         ~node() override;


         string get_user_name();


         virtual bool _os_calc_app_dark_mode() override;

         virtual bool _os_calc_system_dark_mode() override;


         virtual ::color::color get_default_color(::u64 u) override;

         virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha) override;

         //virtual void set_system_dark_mode1(bool bSet = true);

         //virtual void set_app_dark_mode1(bool bSet = true);

         virtual double get_time_zone() override;

         //virtual void get_system_time(system_time_t * psystemtime) override;


         virtual void open_folder(::file::path& pathFolder) override;

         virtual void register_dll(const ::file::path& pathDll) override;


         virtual void system_main() override;


         virtual HICON extract_resource_icon(const ::string & strPath, int & cx, int & cy, int iIcon);

         void * HICON_from_ico_file(const ::block& block);

         
      };


   }  // namespace windows


} // namespace aura



