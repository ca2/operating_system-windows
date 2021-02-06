#include "framework.h"


namespace draw2d_gdi
{


   palette::palette(::layered * pobjectContext) :
      ::draw2d::palette(pobject)
   {

   }


   palette::~palette()
   {

   }



   palette::operator HPALETTE() const
   {

      return (HPALETTE)(this == nullptr ? nullptr : get_os_data());

   }


   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   {

      return Attach(::CreatePalette(lpLogPalette));

   }


   bool palette::CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics)
   {

      ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1() != nullptr);

      return Attach(::CreateHalftonePalette((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1()));

   }


   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

   }


   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {

      ASSERT(get_os_data() != nullptr);

      return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

   }


   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {

      ASSERT(get_os_data() != nullptr);

      ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

   }


   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);

   }


   bool palette::ResizePalette(UINT nNumEntries)
   {

      ASSERT(get_os_data() != nullptr);

      return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != false;

   }


   int palette::GetEntryCount()
   {

      ASSERT(get_os_data() != nullptr);

      WORD nEntries;

      get_object(sizeof(WORD), &nEntries);

      return (int)nEntries;

   }


} // namespace draw2d_gdi





