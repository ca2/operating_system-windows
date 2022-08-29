#pragma once


#include "aura/_.h"
#include "aura_windows/_.h"


#ifdef _WINDOWING_WIN32_STATIC
#define CLASS_DECL_WINDOWING_WIN32
#elif defined(_WINDOWING_WIN32_LIBRARY)
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_IMPORT
#endif


namespace windows
{

   
   class devices;


} // namespace windows


namespace windowing_win32
{

   
   class windowing;
   class system_interaction;


} // namespace windowing_win32



namespace windows
{


   class hwnd_array;


} // namespace windows


//CLASS_DECL_WINDOWING_WIN32 void initialize_windows_devices(::windowing_win32::system_interaction * psysteminteraction);
//CLASS_DECL_WINDOWING_WIN32 void finalize_windows_devices();



