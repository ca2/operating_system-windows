// Created by camilo on 2021-01-30 <3ThomasBS_!!
#pragma once


namespace windowing_win32
{


   class windowing :
      virtual public ::windowing::windowing
   {
   public:


      i64_map < ::user::enum_key >     m_mapKey;


      critical_section                 m_criticalsection;
      window_map                       m_windowmap;
      __pointer(class display)         m_pdisplay;


      windowing();
      virtual ~windowing();


      virtual ::e_status initialize_windowing(::user::user * puser) override;

      virtual void defer_term_ui() override;

      virtual void finalize_windowing() override;

      virtual void finalize() override;


      virtual ::windowing::window * window(oswindow oswindow) override;

      virtual ::windowing_win32::window * _window(HWND hwnd);

      virtual ::windowing::display * display() override;

      //__pointer(::windowing::monitor) get_main_monitor();


      virtual __pointer(::message::base) get_message_base(MESSAGE * pmsg);


      virtual void enum_draw2d_fonts(::draw2d::font_enum_item_array & itema) override;
      
      
      virtual ::windowing::window * get_desktop_window() override;


      virtual ::windowing::window * get_active_window() override;


      virtual void __synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle);

      
      virtual zorder zorder_from_hwnd(HWND hwnd);
      virtual HWND zorder_to_hwnd(const zorder & zorder);

      
      virtual ::windowing::window * get_focus() override;


      virtual ::windowing::window * get_capture() override;


      virtual ::e_status release_capture() override;


      virtual void get_cursor_pos(POINT_I32 * ppoint);


      virtual ::e_status remove_window(::windowing::window * pwindow);
    

      using windowing::windowing::get_cursor;
      //virtual bool set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor);
      //virtual bool set_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      //virtual bool set_default_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();


      virtual int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(hwnd_array & a);


      virtual bool is_window(oswindow oswindow) override;

      bool _is_window(HWND hwnd);


      virtual void get_app_wnda(hwnd_array & wnda);

      __pointer(::windowing::window) window_from_point(::aura::application * papp, const ::point_i32 & point);

      
      __pointer(::user::interaction) create_system_window();


      static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      virtual void set(::message::key * pkey, HWND hwnd, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam);
      virtual void set(::message::mouse * pmouse, HWND hwnd, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam);


      virtual void initialize_keyboard(::user::keyboard * pkeyboard) override;


   };


} // namespace windowing_win32



