//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "apex/innate_subsystem/drawing/Cursor.h"
#include "subsystem_win32/_common_header.h"


namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 Cursor :
      virtual public ::subsystem::implementation<::innate_subsystem::CursorInterface>
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

      virtual void initialize_cursor(::innate_subsystem::CursorInterface * picon) override;
      virtual void initialize_cursor(::innate_subsystem::BitmapInterface * bitmap) override;
      virtual void initialize_cursor(::innate_subsystem::BitmapInterface * bitmap, ::innate_subsystem::BitmapInterface *mask) override;
      virtual void initialize_with_system_cursor(enum_cursor ecursor) override;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) override;

   // protected:
      HCURSOR m_hcursor;
      bool m_bHasOwnCursor;
   };


} // namespace innate_subsystem_win32


