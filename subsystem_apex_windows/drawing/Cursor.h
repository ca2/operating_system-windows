//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "subsystem_apex/drawing/Cursor.h"
#include "subsystem_win32/_common_header.h"


namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 Cursor :
      virtual public ::subsystem::implementation<::subsystem_apex::CursorInterface>
   {
   public:

      Cursor();
      // Icon(HICON icon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(DWORD icon);
      ~Cursor() override;

      void * _HCURSOR() override;
      void _setHCURSOR(void * p) override;

      virtual void initialize_cursor(::subsystem_apex::CursorInterface * picon) override;
      virtual void initialize_cursor(::subsystem_apex::BitmapInterface * bitmap) override;
      virtual void initialize_cursor(::subsystem_apex::BitmapInterface * bitmap, ::subsystem_apex::BitmapInterface *mask) override;
      virtual void initialize_with_system_cursor(enum_cursor ecursor) override;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::subsystem_apex::BitmapInterface *bitmap, ::subsystem_apex::BitmapInterface *mask) override;

   // protected:
      HCURSOR m_hcursor;
      bool m_bHasOwnCursor;
   };


} // namespace innate_subsystem_win32


