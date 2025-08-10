// Created by camilo on 2021-01-30 <3ThomasBS_!!
#pragma once


#include "keyboard_hook.h"
#include "mouse_hook.h"
#include "apex/input/input.h"


namespace input_win32
{


   class CLASS_DECL_INPUT_WIN32 input :
      virtual public ::input::input,
      virtual public keyboard_hook,
      virtual public mouse_hook
   {
   public:




      //i64_map < ::user::enum_key >     m_mapKey;


      //::critical_section               m_criticalsection;
      //::windows::window_map            m_windowmap;
      //::pointer<class display>         m_pdisplay;

//#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      //::pointer<system_interaction>    m_psysteminteraction;

//#endif

      //bool     m_bMouseHook = false;
      //bool     m_bKeyboardHook = false;


      ::task_pointer                   m_ptaskMouse;
      ::task_pointer                   m_ptaskKeyboard;

      input();
      ~input() override;


      //void initialize_windowing(::user::user * puser) override;

      //void defer_term_ui() override;

      //void finalize_windowing() override;

      //void destroy() override;

      ////void destroy() override;

      ////void get_cursor_position(::int_point* ppoint) override;

      //virtual bool defer_create_system_window();
      ////virtual ::pointer<::user::interaction>create_system_window();
      //::pointer<system_interaction>create_system_window();


      //inline system_interaction * system_interaction() { return m_psysteminteraction; }

      //virtual HICON _load_icon(string_array_base& straMatter, const ::scoped_string & scopedstrIcon, int cx, int cy);

      //virtual ::windows::hwnd_array _get_hwnda(const ::user::primitive_pointer_array& primitivepointera);

      //virtual ::windowing::window * window(oswindow oswindow) override;

      //virtual ::windowing_win32::window * _window(HWND hwnd);

      //virtual ::windowing::display * display() override;

      //::pointer<::windowing::monitor>get_main_monitor();


      //virtual ::extended::transport < ::windowing::icon > load_icon(const ::payload & payloadFile) override;


      //virtual ::pointer<::user::message>get_user_message(MESSAGE * pmsg);


      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array & itema) override;
      
      
      //virtual ::windowing::window * get_desktop_window() override;


      //virtual ::windowing::window * get_active_window(::thread * pthread) override;


      //virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, unsigned int & nExStyle, unsigned int & nStyle);

      //
      //virtual zorder zorder_from_hwnd(HWND hwnd);
      //virtual HWND zorder_to_hwnd(const zorder & zorder);


      //void aaa_clear_keyboard_focus(::user::element * pelementGainingFocusIfAny) override;

      //
      //::windowing::window * get_keyboard_focus(::thread * pthread) override;


      //::windowing::window * get_mouse_capture(::thread * pthread) override;

      //
      ////HWND _get_mouse_capture(itask itask);


      //bool defer_release_mouse_capture(::thread* pthread, ::windowing::window* pwindowDeferRelease) override;
      //

      //virtual void erase_window(::windowing::window * pwindow);
    

      //using windowing::windowing::get_cursor;


      //virtual ::windowing::cursor * get_cursor();
      //virtual ::windowing::cursor * get_default_cursor();


      ////virtual enum_dialog_result message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox);


      //virtual void get_cursor_pos(::int_point * ppoint);

      //virtual void set_cursor_position(const ::int_point & point);



      //virtual int_bool point_is_window_origin(::int_point ptHitTest, oswindow oswindowExclude, int iMargin);

      ////virtual void top_windows_by_z_order(hwnd_array & a);


      //virtual bool is_window(oswindow oswindow) override;

      //bool _is_window(HWND hwnd);


      //virtual void get_app_wnda(::windows::hwnd_array & wnda);

      //::pointer<::windowing::window>window_from_point(::aura::application * papp, const ::int_point & point);

      //
      ////virtual void windowing_post(const ::procedure & procedure) override;


      //static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      //virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam) override;
      //virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam) override;


      //virtual void initialize_keyboard(::windowing::keyboard * pkeyboard) override;

      //virtual void lock_set_foreground_window(bool bLock) override;

      //virtual wstring _windows_register_window_class(unsigned int nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
      ////CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::particle * pparticle, unsigned int nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
      //virtual bool _windows_register_class(WNDCLASSEXW* puserinteractionclass);
      ////
      //virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, unsigned int dwDefaultStyle, const ::scoped_string & scopedstrMatter) override;
      //virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction) override;
      //virtual bool _windows_register_with_icon(WNDCLASSEXW* puserinteractionclass, const unichar* pszClassName, unsigned int nIDIcon);

      //virtual void _window_create_caret(HWND hwnd, HBITMAP hbitmap);
      //virtual void _window_create_solid_caret(HWND hwnd, int nWidth, int nHeight);
      //virtual void _window_create_gray_caret(HWND hwnd, int nWidth, int nHeight);


      ////template < typename PRED >
      ////bool _top_level_contains_predicate(PRED pred);


      ////template < typename PREDICATE >
      ////bool _top_level_contains_bool_member(PREDICATE predicate);


      //bool _visible_top_level_contains_all_names(const string_array_base& stra) override;
      //bool _visible_top_level_contains_name(const ::scoped_string & scopedstr) override;
      //virtual bool _top_level_contains_name(const ::scoped_string & scopedstr);
      //virtual string _get_window_text_timeout(oswindow oswindow, const class time & time = 1_s);

      void defer_input() override;

      //void install_keyboard_hook(::matter* pmatterListener) override;
      //void uninstall_keyboard_hook(::matter* pmatterListener) override;

      //void install_mouse_hook(::matter* pmatterListener) override;
      //void uninstall_mouse_hook(::matter* pmatterListener) override;




      //virtual void register_windows_message();


      //::pointer < ::user::interaction > create_message_window(const ::scoped_string & scopedstrName, ::user::interaction_listener * plistener = nullptr) override;


      //void set_mouse_cursor(::windowing::cursor* pcursor) override;


      void handle_message(::message::message * pmessage) override;


   };


} // namespace windowing_win32



