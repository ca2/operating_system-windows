//
// Created by camilo on 09/04/2022.
// Modified 2023-10-05 23:50
//
#pragma once


#include "acme_windows/_.h"


#if defined(_nano_user_win32_project)
#define CLASS_DECL_NANO_USER_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO_USER_WIN32  CLASS_DECL_IMPORT
#endif


//void x11_check_status(int status, unsigned long window);



//#ifndef WITH_XI
//#define WITH_XI
//#endif

//#define pointer x11_pointer

// #include <wayland-client.h>
// #include <wayland-server.h>
// #include <wayland-cursor.h>
// #include <wayland-client-protocol.h>
// #include "wayland_static/wayland-gtk_shell1.h"
// #include "wayland_static/wayland-xdg_activation_v1.h"
// #include "wayland_static/wayland-xdg_wm_base.h"
//#include <X11/Xutil.h>
//#include <X11/extensions/Xrender.h>
//#include <X11/Xatom.h>

//#undef pointer



//Visual * get_32bit_visual(Display * pdisplay);


//void x11_kick_idle();


//void x11_wait_timer_or_event(Display * pdisplay);
//void __x11_hook_on_idle(Display * pdisplay);


//CLASS_DECL_ACME ::particle * user_synchronization();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


//::e_status deferx_initializex_x11();
//void x11_handle_just_hooks();
//void x11_defer_handle_just_hooks();
//int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
//bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


//class x11color32_t
//{
//public:
//
//
//   unsigned int m_u32;
//
//
//   x11color32_t(){m_u32=0;}
//   x11color32_t(const ::color::color & color)
//   {
//
//      auto opacity = color.u8_opacity();
//
//      m_u32 = make_u32(
//              color.u8_blue() * opacity / 255,
//              color.u8_green() * opacity / 255,
//              color.u8_red() * opacity / 255,
//              opacity);
//
//   }
//
//
//   operator unsigned long () const { return m_u32; }
//
//
//};

namespace windowing_system_win32
{


} // namespace windowing_system_win32

