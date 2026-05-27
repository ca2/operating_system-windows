#include "framework.h"


namespace draw2d_gdi
{

   ::i32 get_os_fill_mode(::draw2d::e_fill_mode efillmode)
   {

      ::i32 nMode;
      switch(efillmode)
      {
      case ::draw2d::e_fill_mode_winding:
         nMode = WINDING;
         break;
      case ::draw2d::e_fill_mode_alternate:
         nMode = ALTERNATE;
         break;
      default:
         nMode = WINDING;
         break;
      }

      return nMode;

   }


   region::region(::particle * pparticle) :
      ::draw2d::region(pobject)
   {
      m_bUpdated = true;
   }


   region::~region()
   {

   }


   region::operator HRGN() const
   {

      return (HRGN)(this == nullptr ? nullptr : get_os_data());

   }


   bool region::create_rect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2)
   {

      return Attach(::CreateRectRgn(x1, y1, x2, y2));

   }


   bool region::create_rect(const ::i32_rectangle & rectangle)
   {

      return Attach(::CreateRectRgnIndirect(rectangle));

   }


   bool region::create_oval(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2)
   {

      return Attach(::CreateEllipticRgn(x1, y1, x2, y2));

   }


   bool region::create_oval(const ::i32_rectangle & rectangle)
   {

      return Attach(::CreateEllipticRgnIndirect(rectangle));

   }


   bool region::create_polygon(LPPOINT lpPoints, ::i32 nCount, ::draw2d::e_fill_mode efillmode)
   {

      return Attach(::CreatePolygonRgn(lpPoints, nCount, get_os_fill_mode(efillmode)));

   }

   bool region::create_poly_polygon(LPPOINT lpPoints, LPINT lpPolyCounts, ::i32 nCount, ::draw2d::e_fill_mode efillmode)
   {

      return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, get_os_fill_mode(efillmode)));

   }


   bool region::CreateRoundRectRgn(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3)
   {

      return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3));

   }


   bool region::CreateFromPath(::draw2d::graphics_pointer & pgraphics)
   {

      ASSERT(pgraphics != nullptr);

      return Attach(::PathToRegion((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1()));

   }


   bool region::CreateFromData(const XFORM* lpXForm, ::i32 nCount, const RGNDATA* pRgnData)
   {

      return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData));
   }
   ::i32 region::GetRegionData(LPRGNDATA lpRgnData, ::i32 nDataSize) const
   {

      ASSERT(get_os_data() != nullptr); return (::i32)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData);
   }
   void region::SetRectRgn(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2)
   {

      ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2);
   }

   void region::SetRectRgn(const ::i32_rectangle & rectangle)
   {

      ::SetRectRgn((HRGN)get_os_data(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

   }


   ::i32 region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, ::i32 nCombineMode)
   {

      ASSERT(get_os_data() != nullptr);

      return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(), (HRGN)pRgn2->get_os_data(), nCombineMode);

   }


   ::i32 region::CopyRgn(const ::draw2d::region* pRgnSrc)
   {

      ASSERT(get_os_data() != nullptr);

      return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY);

   }


   bool region::EqualRgn(const ::draw2d::region* pRgn) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()) != false;

   }


   ::i32 region::OffsetRgn(::i32 x, ::i32 y)
   {

      ASSERT(get_os_data() != nullptr);

      return ::OffsetRgn((HRGN)get_os_data(), x, y) != false;


   }


   ::i32 region::OffsetRgn(const ::i32_point & point)
   {

      ASSERT(get_os_data() != nullptr);

      return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y);

   }


   ::i32 region::GetRgnBox(RECT * prectangle) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::GetRgnBox((HRGN)get_os_data(), prectangle);

   }


   bool region::contains(::i32 x, ::i32 y) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::PtInRegion((HRGN)get_os_data(), x, y) != false;

   }


   bool region::contains(const ::i32_point & point) const
   {
      ASSERT(get_os_data() != nullptr);

      return ::PtInRegion((HRGN)get_os_data(), point.x, point.y) != false;

   }


   bool region::rectInRegion(const ::i32_rectangle & rectangle) const
   {

      ASSERT(get_os_data() != nullptr);

      return ::rectInRegion((HRGN)get_os_data(), rectangle) != false;

   }


   bool region::create()
   {

      ::draw2d_gdi::object::create();

      //for(::i32 i = 0; i <

      return true;

   }

   bool region::destroy()
   {

      ::draw2d::region::destroy();
      ::draw2d_gdi::object::destroy();

      return true;

   }

} // namespace draw2d_gdi





