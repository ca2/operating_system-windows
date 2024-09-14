#pragma once

#include "innate_ui_win32/_.h"
#include "aura/_.h"
#include "aura_windows/_.h"


#if defined(_windowing_win32_project)
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_IMPORT
#endif


namespace windowing_win32
{

   
   class windowing;
   class system_interaction;
   class window;


   class master_device_listener;


   class devices;


} // namespace windowing_win32



namespace windows
{


   class hwnd_array;


} // namespace windows


//CLASS_DECL_WINDOWING_WIN32 void initialize_windows_devices(::windowing_win32::system_interaction * psysteminteraction);
//CLASS_DECL_WINDOWING_WIN32 void finalize_windows_devices();



