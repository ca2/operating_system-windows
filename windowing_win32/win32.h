#pragma once



CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::layered * pobjectContext, ::u32 nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
//CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::layered * pobjectContext, ::u32 nClassStyle, hcursor hCursor = 0, HBRUSH hbrBackground = 0, hicon hIcon = 0);
//CLASS_DECL_WINDOWING_WIN32 bool windows_register_class(WNDCLASSEXW* pwndclass);
//
CLASS_DECL_WINDOWING_WIN32 wstring windows_calc_icon_window_class(::user::interaction * pinteraction, u32 dwDefaultStyle, const char * pszMatter);
CLASS_DECL_WINDOWING_WIN32 wstring windows_get_user_interaction_window_class(::user::interaction * pinteraction);
CLASS_DECL_WINDOWING_WIN32 bool windows_register_with_icon(WNDCLASSEXW * pwndclass, const unichar * pszClassName, ::u32 nIDIcon);

CLASS_DECL_WINDOWING_WIN32 void window_create_caret(HWND hwnd, HBITMAP hbitmap);
CLASS_DECL_WINDOWING_WIN32 void window_create_solid_caret(HWND hwnd, i32 nWidth, i32 nHeight);
CLASS_DECL_WINDOWING_WIN32 void window_create_gray_caret(HWND hwnd, i32 nWidth, i32 nHeight);



