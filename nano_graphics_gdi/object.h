//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/object.h"
#include "acme/_win32_gdi.h"



      namespace nano_graphics_gdi
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI object :
            virtual public ::nano::graphics::object
         {
         public:


            HGDIOBJ     m_hgdiobj;


            object();
            ~object();


            void* operating_system_data() override;


            void destroy() override;


         };



      } // namespace nano_graphics_gdi

