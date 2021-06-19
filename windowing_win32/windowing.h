// Created by camilo on 2021-01-30 <3ThomasBS_!!
#pragma once


namespace windowing_win32
{


   class windowing :
      virtual public ::windowing::windowing
   {
   public:


      //i64_map < ::user::enum_key >     m_mapKey;


      critical_section                 m_criticalsection;
      window_map                       m_windowmap;
      __pointer(class display)         m_pdisplay;

//#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      __pointer(system_interaction)    m_psysteminteraction;

//#endif


      windowing();
      virtual ~windowing();


      virtual ::e_status initialize_windowing(::user::user * puser) override;

      virtual void defer_term_ui() override;

      virtual void finalize_windowing() override;

      virtual ::e_status finish() override;

      virtual ::e_status finalize() override;

      virtual void get_cursor_position(POINT_I32* ppoint) override;

      virtual bool defer_create_system_window();
      //virtual __pointer(::user::interaction) create_system_window();
      ::extended::transport < system_interaction > create_system_window();


      inline system_interaction * system_window() { return m_psysteminteraction; }

      virtual HICON _load_icon(string_array& straMatter, string strIcon, int cx, int cy);

      virtual hwnd_array _get_hwnda(const ::user::primitive_pointer_array& primitivepointera);

      virtual ::windowing::window * window(oswindow oswindow) override;

      virtual ::windowing_win32::window * _window(HWND hwnd);

      virtual ::windowing::display * display() override;

      //__pointer(::windowing::monitor) get_main_monitor();


      virtual ::extended::transport < ::windowing::icon > load_icon(const ::payload & payloadFile) override;


      virtual __pointer(::user::message) get_user_message(MESSAGE * pmsg);


      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array & itema) override;
      
      
      virtual ::windowing::window * get_desktop_window() override;


      virtual ::windowing::window * get_active_window(::thread * pthread) override;


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle);

      
      virtual zorder zorder_from_hwnd(HWND hwnd);
      virtual HWND zorder_to_hwnd(const zorder & zorder);

      
      virtual ::windowing::window * get_keyboard_focus(::thread * pthread) override;


      virtual ::windowing::window * get_mouse_capture(::thread * pthread) override;


      virtual ::e_status release_mouse_capture() override;


      

      virtual ::e_status erase_window(::windowing::window * pwindow);
    

      using windowing::windowing::get_cursor;


      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();


      //virtual enum_dialog_result message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox);


      virtual void get_cursor_pos(POINT_I32 * ppoint);

      virtual ::e_status set_cursor_position(const ::point_i32 & point);



      virtual int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(hwnd_array & a);


      virtual bool is_window(oswindow oswindow) override;

      bool _is_window(HWND hwnd);


      virtual void get_app_wnda(hwnd_array & wnda);

      __pointer(::windowing::window) window_from_point(::aura::application * papp, const ::point_i32 & point);

      
      virtual ::e_status windowing_branch(const ::routine& routine) override;


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;
      virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard) override;

      virtual ::e_status lock_set_foreground_window(bool bLock) override;

      virtual wstring _windows_register_window_class(::u32 nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
      //CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::object * pobject, ::u32 nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
      virtual bool _windows_register_class(WNDCLASSEXW* puserinteractionclass);
      //
      virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const char* pszMatter) override;
      virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction) override;
      virtual bool _windows_register_with_icon(WNDCLASSEXW* puserinteractionclass, const unichar* pszClassName, ::u32 nIDIcon);

      virtual void _window_create_caret(HWND hwnd, HBITMAP hbitmap);
      virtual void _window_create_solid_caret(HWND hwnd, i32 nWidth, i32 nHeight);
      virtual void _window_create_gray_caret(HWND hwnd, i32 nWidth, i32 nHeight);


      template < typename PRED >
      bool _top_level_contains_predicate(PRED pred);


      template < typename PREDICATE >
      bool _top_level_contains_bool_member(PREDICATE predicate);


      virtual bool _visible_top_level_contains_all_names(string_array& stra);
      virtual bool _visible_top_level_contains_name(string str);
      virtual bool _top_level_contains_name(string str);
      virtual string _get_window_text_timeout(oswindow oswindow, const ::duration & duration = 1_s);


   };


} // namespace windowing_win32



