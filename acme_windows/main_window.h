// Created by camilo on 2023-04-15 19:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/main_window.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS main_window :
      virtual public ::operating_system::main_window
   {
   public:


      HWND m_hwnd;


      main_window();
      ~main_window() override;


      void from_application(::operating_system::application * papplication) override;

      void post_close() override;

      void post_application_exit() override;

      ::string get_window_text(const ::iptr_array & idPath) override;
      ::string indexed_get_window_text(const ::iptr_array & idPath) override;


   };


} //    namespace acme_windows




