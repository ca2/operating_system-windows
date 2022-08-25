// Created by camilo on 2021-08-17 00:17 <3ThomasBS_!!
#pragma once


#include "aura/windowing/desktop_environment.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 desktop_environment :
      virtual public ::windowing::desktop_environment
   {
   public:
      desktop_environment();
      ~desktop_environment() override;

   };


} // namespace windowing_win32