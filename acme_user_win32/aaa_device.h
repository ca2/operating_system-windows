//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/device.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   namespace acme
   {


      namespace user
      {


         class CLASS_DECL_ACME device :
            virtual public ::nano::graphics::device
         {
         public:


            //CreatableFromBase(device, device);


            HDC         m_hdc;
            bool        m_bDelete;


            device();
            device(HDC hdc);
            ~device() override;


            void _draw_text(const ::scoped_string & scopedstr, const ::int_rectangle& rectangleText, const ::e_align& ealign, const ::e_draw_text& edrawtext, ::nano::graphics::brush* pnanobrushBack, ::nano::graphics::brush* pnanobrushText, ::nano::graphics::font* pnanofont) override;
            ::int_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font* pnanofont) override;
            void rectangle(const ::int_rectangle& rectangle, ::nano::graphics::brush* pnanobrush, ::nano::graphics::pen* pnanopen) override;


         };




      } // namespace user


   } // namespace acme



} // namespace windows



