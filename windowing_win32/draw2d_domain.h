//
//  domain.h
//  aura
//
//  Created by camilo on 2026-10-19 09:48 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "aura/graphics/draw2d/domain.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 draw2d_domain :
      virtual public ::draw2d::domain
   {
   public:


      ::pointer < ::windowing_win32::window > m_pwindow;  


      draw2d_domain();
      ~draw2d_domain() override;


   };


} // namespace draw2d



