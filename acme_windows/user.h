#pragma once





//CLASS_DECL_ACME_WINDOWS WNDPROC __get_window_procedure();
//#define __window_procedure (*__get_window_procedure())
extern CLASS_DECL_ACME_WINDOWS const unichar gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_ACME_WINDOWS const unichar gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_ACME_WINDOWS const unichar gen_WndMDIFrame[];
extern CLASS_DECL_ACME_WINDOWS const unichar gen_WndFrameOrImpact[];
extern CLASS_DECL_ACME_WINDOWS const unichar gen_WndOleControl[];
//CLASS_DECL_ACME_WINDOWS bool __is_combo_box_control(::windowing::window * pwindow, ::u32 nStyle);
CLASS_DECL_ACME_WINDOWS bool __check_center_dialog(const ::string & pszResource);

//CLASS_DECL_ACME_WINDOWS bool __compare_class_name(::windowing::window * pwindow, const ::string & pszClassName);

//CLASS_DECL_ACME_WINDOWS oswindow __child_window_from_point(oswindow, const point_i32 &);
//CLASS_DECL_ACME_WINDOWS bool hook_window_create(::windows::interaction_impl * pwindow);
//CLASS_DECL_ACME_WINDOWS bool unhook_window_create();
CLASS_DECL_ACME_WINDOWS void reset_message_cache();




