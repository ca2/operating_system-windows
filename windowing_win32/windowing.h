// Created by camilo on 2021-01-30 <3ThomasBS_!!
#pragma once


#include "acme_windowing_win32/windowing.h"
#include "aura/windowing/windowing.h"
#include "win32.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 windowing :
      virtual public ::windowing::windowing,
      virtual public ::win32::acme::windowing::windowing
   {
   public:


      enum_message                                       m_emessageWindowsTaskbarCreatedMessage;
      //__creatable_from_base(windowing, ::windowing::windowing);


      //i64_map < ::user::enum_key >     m_mapKey;


      ::critical_section               m_criticalsection;
      ::windows::window_map            m_windowmap;
      //::pointer<class display>         m_pdisplay;

//#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      ::pointer<system_interaction>    m_psysteminteraction;

//#endif


      windowing();
      ~windowing() override;


      void initialize_windowing() override;

      void defer_term_ui() override;

      void finalize_windowing() override;

      void destroy() override;

      //void destroy() override;

      //void get_cursor_position(::point_i32* ppoint) override;

      virtual void initialize_system_interaction();
      //virtual ::pointer<::user::interaction>create_system_window();
      ::pointer<system_interaction>create_system_interaction();
      
      
      void kick_idle() override;


      virtual system_interaction * system_interaction();

      virtual HICON _load_icon(string_array& straMatter, string strIcon, int cx, int cy);

      virtual ::windows::hwnd_array _get_hwnda(const ::user::interaction_array& userinteractiona);

      virtual ::windowing::window * window(oswindow oswindow) override;

      virtual ::windowing_win32::window * _window(HWND hwnd);

      //virtual ::windowing::display * display() override;

      //::pointer<::windowing::monitor>get_main_monitor();


      //virtual ::extended::transport < ::windowing::icon > load_icon(const ::payload & payloadFile) override;


      //virtual ::pointer<::user::message>get_user_message(MESSAGE * pmsg);


      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array & itema) override;
      
      
      virtual ::windowing::window * get_desktop_window() override;


      virtual ::windowing::window * get_active_window(::thread * pthread) override;


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle);

      
      virtual zorder zorder_from_hwnd(HWND hwnd);
      virtual HWND zorder_to_hwnd(const zorder & zorder);


      void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny) override;

      
      ::acme::windowing::window * get_keyboard_focus(::thread * pthread) override;


      ::windowing::window * get_mouse_capture(::thread * pthread) override;

      
      //HWND _get_mouse_capture(itask_t itask);


      bool defer_release_mouse_capture(::thread* pthread, ::windowing::window* pwindowDeferRelease) override;
      

      virtual void erase_window(::windowing::window * pwindow);
    

      using windowing::windowing::get_cursor;


      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();


      //virtual enum_dialog_result message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox);


      //virtual void get_cursor_pos(::point_i32 * ppoint);

      //virtual void set_cursor_position(const ::point_i32 & point);



      virtual int_bool point_is_window_origin(::point_i32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(hwnd_array & a);


      virtual bool is_window(oswindow oswindow) override;

      bool _is_window(HWND hwnd);


      virtual void get_app_wnda(::windows::hwnd_array & wnda);

      ::pointer<::windowing::window>window_from_point(::aura::application * papp, const ::point_i32 & point);

      
      //virtual void windowing_post(const ::procedure & procedure) override;


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;
      virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;


      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard) override;

      virtual void lock_set_foreground_window(bool bLock) override;

      virtual wstring _windows_register_window_class(::u32 nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
      //CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::particle * pparticle, ::u32 nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
      virtual bool _windows_register_class(WNDCLASSEXW* puserinteractionclass);
      //
      virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const ::string & pszMatter) override;
      virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction) override;
      virtual bool _windows_register_with_icon(WNDCLASSEXW* puserinteractionclass, const unichar* pszClassName, ::u32 nIDIcon);

      virtual void _window_create_caret(HWND hwnd, HBITMAP hbitmap);
      virtual void _window_create_solid_caret(HWND hwnd, i32 nWidth, i32 nHeight);
      virtual void _window_create_gray_caret(HWND hwnd, i32 nWidth, i32 nHeight);


      //template < typename PRED >
      //bool _top_level_contains_predicate(PRED pred);


      //template < typename PREDICATE >
      //bool _top_level_contains_bool_member(PREDICATE predicate);

      void set_dark_mode(bool bDarkMode) override;

      bool _visible_top_level_contains_all_names(const string_array& stra) override;
      bool _visible_top_level_contains_name(string str) override;
      virtual bool _top_level_contains_name(string str);
      virtual string _get_window_text_timeout(oswindow oswindow, const class time & time = 1_s);


      void windowing_application_main_loop() override;
      void windowing_post_quit() override;



      virtual void register_windows_message();


      ::pointer < ::user::interaction > create_message_window(const ::string & pszName, ::user::interaction_listener * plistener = nullptr) override;


      void set_mouse_cursor2(::windowing::cursor* pcursor) override;


   };


} // namespace windowing_win32



