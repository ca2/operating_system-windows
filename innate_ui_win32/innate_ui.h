// Created by camilo on 2024-09-13 01:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/innate_ui.h"


namespace innate_ui_win32
{

   class window;

   class CLASS_DECL_INNATE_UI_WIN32 innate_ui :
      virtual public ::innate_ui::innate_ui
   {
   public:


      bool m_bRunning;

      HANDLE m_hthread;
      DWORD m_dwThread;

      //ATOM m_atom;


      map < HWND, ::pointer < window > >     m_windowmap;
      string_map < ATOM >                    m_classmap;

      innate_ui();
      ~innate_ui() override;

      void on_initialize_particle() override;
      
      void _defer_run_innate_ui_win32_user_loop();
      
      void _main_post(const ::procedure & procedure) override;


      virtual LRESULT _window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

      //virtual void _defer_show_system_menu(HWND hwnd, const ::point_i32 & pointAbsolute);


   };

   LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

} // namespace innate_ui



