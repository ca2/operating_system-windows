#pragma once


#include "innate_ui_win32/_.h"


#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif



#if defined(_innate_subsystem_win32_project)
#define CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS  CLASS_DECL_IMPORT
#endif




namespace innate_subsystem_windows
{


   class DeviceContext;
   class Bitmap;
   class BitmapGraphics;
   class Brush;
   class Font;
   class Graphics;
   class Icon;
   class Pen;
   class SolidBrush;


   class Window;

   class Control;

   class Dialog;


   class WindowMessageHandler;


} // namespace innate_subsystem_windows
