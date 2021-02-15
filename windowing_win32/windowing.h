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

      virtual void finalize() override;


      virtual bool defer_create_system_window();
      //virtual __pointer(::user::interaction) create_system_window();
      result_pointer < system_interaction > create_system_window();


      inline system_interaction * system_window() { return m_psysteminteraction; }



      virtual ::windowing::window * window(oswindow oswindow) override;

      virtual ::windowing_win32::window * _window(HWND hwnd);

      virtual ::windowing::display * display() override;

      //__pointer(::windowing::monitor) get_main_monitor();


      virtual result_pointer < ::windowing::icon > load_icon(const ::payload & payloadFile) override;


      virtual __pointer(::user::message) get_user_message(MESSAGE * pmsg);


      //virtual void enum_draw2d_fonts(::write_text::font_enum_item_array & itema) override;
      
      
      virtual ::windowing::window * get_desktop_window() override;


      virtual ::windowing::window * get_active_window(::thread * pthread) override;


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle);

      
      virtual zorder zorder_from_hwnd(HWND hwnd);
      virtual HWND zorder_to_hwnd(const zorder & zorder);

      
      virtual ::windowing::window * get_keyboard_focus(::thread * pthread) override;


      virtual ::windowing::window * get_mouse_capture(::thread * pthread) override;


      virtual ::e_status release_mouse_capture() override;


      

      virtual ::e_status remove_window(::windowing::window * pwindow);
    

      using windowing::windowing::get_cursor;
      //virtual bool set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor);
      //virtual bool set_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      //virtual bool set_default_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();


      virtual int message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox);


      virtual void get_cursor_pos(POINT_I32 * ppoint);

      virtual ::e_status set_cursor_position(const ::point_i32 & point);



      virtual int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(hwnd_array & a);


      virtual bool is_window(oswindow oswindow) override;

      bool _is_window(HWND hwnd);


      virtual void get_app_wnda(hwnd_array & wnda);

      __pointer(::windowing::window) window_from_point(::aura::application * papp, const ::point_i32 & point);

      


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;
      virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;


      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard) override;

      virtual ::e_status lock_set_foreground_window(bool bLock) override;

   };


} // namespace windowing_win32



