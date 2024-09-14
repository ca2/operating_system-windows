// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/window.h"
#define ISOLATION_AWARE_ENABLED 1
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/operating_system/windows/window.h"
#include <commctrl.h>



namespace innate_ui_win32
{

   class innate_ui;

   class CLASS_DECL_INNATE_UI_WIN32 window :
      virtual public ::innate_ui::window,
      virtual public ::windows::window
   {
   public:


      //HWND m_hwnd;
      //HMENU m_hmenuSystem;
      int m_iChildIdSeed;
      int m_iCreateStyle;


      window();
      ~window() override;

      void set_text(const ::scoped_string & scopedstr) override;

      LONG_PTR _get_style();

//      void _post(const ::procedure & procedure);
      virtual const char * __get_class_name();
      virtual wstring _get_class_name();
      virtual ATOM _register_class();
      virtual void _get_class(WNDCLASSEXW & wcex);
      virtual void _create();
      virtual void _create_child(window * pwindow);

      void create() override;
      void create_child(::innate_ui::window * pwindow) override;
      void destroy_window() override;
      void center() override;

      void show() override;
      void hide() override;

      void set_position(const ::point_i32 & point) override;
      void set_size(const ::size_i32 & size) override;
      void adjust_for_client_size(const ::size_i32 & size) override;

      ::innate_ui_win32::innate_ui * innate_ui();

      virtual ::pointer < window > _get_child_with_id(int iId);
      virtual LRESULT _window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

      virtual bool _on_command();

      virtual int _get_id();

      void defer_show_system_menu(const ::point_i32 & pointAbsolute) override;

   };


} // namespace innate_ui_win32




