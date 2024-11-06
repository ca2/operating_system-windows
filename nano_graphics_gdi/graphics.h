//
// Created by camilo on 2024-09-13 13:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/graphics.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI graphics :
            virtual public ::nano::graphics::graphics
         {
         public:

            ULONG_PTR gdiplusToken;
            graphics();
            ~graphics() override;


            //virtual void _defer_show_system_menu(HWND hwnd, HMENU * phmenuSystem, const ::int_point & pointAbsolute);
            //virtual bool _on_command(LRESULT & lresult, HWND hwnd, WPARAM wparam, LPARAM lparam);
            //virtual void _erase_minimize_box_style(HWND hwnd);

         };



      } // namespace graphics


   } // namespace nano

} // namespace windows



