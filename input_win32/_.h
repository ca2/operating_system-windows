#pragma once


#include "aura/_.h"
#include "aura_windows/_.h"


#if defined(_input_win32_project)
#define CLASS_DECL_INPUT_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_INPUT_WIN32  CLASS_DECL_IMPORT
#endif


namespace input_win32
{

   
   class input;


} // namespace input_win32



namespace windows
{


   class hwnd_array;


} // namespace windows


//CLASS_DECL_WINDOWING_WIN32 void initialize_windows_devices(::windowing_win32::system_interaction * psysteminteraction);
//CLASS_DECL_WINDOWING_WIN32 void finalize_windows_devices();



