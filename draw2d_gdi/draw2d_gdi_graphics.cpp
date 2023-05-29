#include "framework.h"
#include <math.h>


CLASS_DECL_THREAD image_descriptor_map * t_pimagemap = nullptr;


inline ::size_i32 rect_size(const ::rectangle_i32 & rectangle)
{

   return ::size_i32(width(rectangle), height(rectangle));

}


namespace draw2d_gdi
{


   graphics::graphics(::particle * pparticle) :
      ::object(pobject),
      ::draw2d::graphics(pobject)
   {

      m_hdc                = nullptr;
      m_bPrinting          = false;

   }


   graphics::~graphics()
   {

      synchronous_lock ml(synchronization());

      for(int i = 0; i < m_ptraObject.get_count(); i++)
      {

         try
         {
            ::draw2d_gdi::particle * pparticle = m_ptraObject[i];

            pobject->m_ptraGraphics.erase(this);

         }
         catch(...)
         {
         }

      }

      if (get_handle1() != nullptr)
      {

         ::DeleteDC(detach_hdc());

      }

   }


   graphics::operator HDC() const
   {

      return this == nullptr ? nullptr : (HDC) get_os_data();

   }


   HDC graphics::get_handle1() const
   {

      return this == nullptr ? nullptr : (HDC) m_hdc;

   }


   HDC graphics::get_handle2() const
   {

      return this == nullptr ? nullptr : (HDC) m_hdc;

   }


   void * graphics::get_os_data() const
   {

      return (void *) get_handle1();

   }


   void * graphics::get_os_data_ex(int i) const
   {
      switch((e_data) i)
      {
      case data_graphics:
         return m_hdc;
      case data_bitmap:
         return ::GetCurrentObject(m_hdc, OBJ_BITMAP);
      case data_pen:
         return ::GetCurrentObject(m_hdc, OBJ_PEN);
      case data_brush:
         return ::GetCurrentObject(m_hdc, OBJ_BRUSH);
      case data_font:
         return ::GetCurrentObject(m_hdc, OBJ_FONT);
      case data_palette:
         return ::GetCurrentObject(m_hdc, OBJ_PAL);
      case data_region:
         return ::GetCurrentObject(m_hdc, OBJ_REGION);
      default:
         break;
      };

      return ::draw2d::graphics::get_os_data_ex(i);

   }


   HDC graphics::get_handle() const
   {

      return get_handle1();

   }


   bool graphics::IsPrinting()
   {

      return m_bPrinting;

   }


   bool graphics::CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData)
   {

      return attach_hdc(::CreateDCW(wstring(lpszDriverName), wstring(lpszDeviceName), wstring(lpszOutput), (const DEVMODEW*)lpInitData)) != false;

   }


   bool graphics::CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData)
   {

      return attach_hdc(::CreateICW(wstring(lpszDriverName), wstring(lpszDeviceName), wstring(lpszOutput), (const DEVMODEW*) lpInitData)) != false;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics_pointer & pgraphics)
   {

      if(pgraphics == nullptr)
      {

         return attach_hdc(::CreateCompatibleDC(nullptr)) != false;

      }
      else
      {

         return attach_hdc(::CreateCompatibleDC((HDC)(dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1())) != false;

      }

   }


   int graphics::ExcludeUpdateRgn(::user::primitive * pwindow)
   {

      ASSERT(get_handle1() != nullptr);

//      return ::ExcludeUpdateRgn(get_handle1(), (oswindow) pwindow->get_handle()) ;
      return 0;

   }


   int graphics::GetDeviceCaps(int nIndex)
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetDeviceCaps(get_handle2(), nIndex) ;

   }


   point_i32 graphics::GetBrushOrg()
   {

      ASSERT(get_handle1() != nullptr);

      ::point_i32 point;

      VERIFY(::GetBrushOrgEx(get_handle1(), &point));

      return point;

   }


   point_i32 graphics::SetBrushOrg(int x, int y)
   {

      ASSERT(get_handle1() != nullptr);

      ::point_i32 point;

      VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));

      return point;

   }


   ::point_i32 graphics::SetBrushOrg(const ::point_i32 & point)
   {

      ASSERT(get_handle1() != nullptr);

      ::point_i32 pointRet;

      VERIFY(::SetBrushOrgEx(get_handle1(), point.x(), point.y(), pointRet));

      return pointRet;

   }


   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {

      ASSERT(get_handle2() != nullptr);

      return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData) ;

   }


   ::draw2d::bitmap * graphics::SelectObject(::draw2d::bitmap * pbitmap)
   {

      if(get_handle1() == nullptr)
         return nullptr;

      if(pbitmap == nullptr)
         return nullptr;

      synchronous_lock ml(synchronization());

      pbitmap->m_bUpdated = true;

      ::SelectObject(get_handle1(), pbitmap->get_os_data());

      on_select_object(pbitmap);


      m_pbitmap = pbitmap;

      return m_pbitmap;

   }

   void graphics::on_select_object(::draw2d::particle * pparticleParam)
   {

      synchronous_lock ml(synchronization());

      ::draw2d_gdi::particle * pparticle = dynamic_cast <::draw2d_gdi::object *> (pobjectParam);

      pobject->m_ptraGraphics.add_unique(this);

      m_ptraObject.add_unique(pobject);

   }


   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
   {

      ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object

      return (hObject != nullptr) ? ::SelectObject(get_handle1(), hObject) : nullptr;

   }

   ::color::color graphics::GetNearestColor(::color::color crColor)
   {

      return ::GetNearestColor(get_handle2(), crColor) ;

   }



   UINT graphics::RealizePalette()
   {

      return ::RealizePalette(get_handle1());

   }



   void graphics::UpdateColors()
   {

      ::UpdateColors(get_handle1());

   }



   ::color::color graphics::GetBkColor()
   {

      return ::GetBkColor(get_handle2());

   }



   int graphics::GetBkMode()
   {

      return ::GetBkMode(get_handle2());

   }



   int graphics::GetPolyFillMode()
   {

      return ::GetPolyFillMode(get_handle2());

   }



   int graphics::GetROP2()
   {

      return ::GetROP2(get_handle2());

   }



   int graphics::GetStretchBltMode()
   {

      return ::GetStretchBltMode(get_handle2());

   }




   ::color::color graphics::GetTextColor()
   {

      return ::GetTextColor(get_handle2());

   }


   int graphics::GetMapMode()
   {

      return ::GetMapMode(get_handle2());

   }


   int graphics::GetGraphicsMode()
   {

      return ::GetGraphicsMode(get_handle2());

   }


   bool graphics::GetWorldTransform(XFORM* pXform)
   {

      return ::GetWorldTransform(get_handle2(),pXform) != false;

   }


   point_i32 graphics::GetViewportOrg()
   {

      ::point_i32 point;

      ::GetViewportOrgEx(get_handle2(), &point);

      return point;

   }


   ::size_i32 graphics::GetViewportExt()
   {

      ::size_i32 size;

      ::GetViewportExtEx(get_handle2(), &size);

      return size;

   }

   point_i32 graphics::GetWindowOrg()
   {

      ::point_i32 point;

      ::GetWindowOrgEx(get_handle2(), &point);

      return point;

   }


   ::size_i32 graphics::GetWindowExt()
   {

      ::size_i32 size;

      ::GetWindowExtEx(get_handle2(), &size);

      return size;

   }


   // non-virtual helpers calling virtual mapping functions
   ::point_i32 graphics::SetViewportOrg(const ::point_i32 & point)
   {

      return SetViewportOrg(point.x(), point.y());

   }


   ::size_i32 graphics::SetViewportExt(const ::size_i32 & size)
   {

      return SetViewportExt(size.cx(), size.cy());

   }


   ::point_i32 graphics::SetWindowOrg(const ::point_i32 & point)
   {

      return SetWindowOrg(point.x(), point.y());

   }


   ::size_i32 graphics::set_window_ext(const ::size_i32 & size)
   {

      return set_window_ext(size.cx(), size.cy());

   }


   void graphics::DPtoLP(POINT * lpPoints, count nCount)
   {

      ::DPtoLP(get_handle2(), lpPoints, (int) nCount);

   }


   void graphics::DPtoLP(RECT * prectangle)
   {

      ::DPtoLP(get_handle2(), (LPPOINT)prectangle, 2);

   }




   void graphics::LPtoDP(LPPOINT lpPoints, count nCount)
   {

      ::LPtoDP(get_handle2(), lpPoints, (int) nCount);

   }




   void graphics::LPtoDP(RECT * prectangle)
   {

      ::LPtoDP(get_handle2(), (LPPOINT)prectangle, 2);

   }




   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;

   }


   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight)
   {

      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;

   }


   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      ASSERT(get_handle1() != nullptr);

      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;

   }


   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      ASSERT(get_handle1() != nullptr);

      return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;

   }


   bool graphics::PtVisible(int x, int y)
   {

      ASSERT(get_handle1() != nullptr);

      return ::PtVisible(get_handle1(), x, y) != false;

   }


   bool graphics::PtVisible(const ::point_i32 & point)
   {

      ASSERT(get_handle1() != nullptr);

      return PtVisible(point.x(), point.y()) != false;

   }


   bool graphics::rectVisible(const ::rectangle_i32 & rectangle)
   {

      ASSERT(get_handle1() != nullptr);

      return ::rectVisible(get_handle1(),&rectangle) != false;

   }


   point_f64 graphics::current_position()
   {

      ASSERT(get_handle2() != nullptr);

      ::point_i32 point;

      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));

      return point;

   }


   bool graphics::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Arc(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;

   }


   bool graphics::Arc(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Arc(get_handle1(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y()) != false;

   }


   bool graphics::polyline(const POINT* lpPoints, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      return ::polyline(get_handle1(), lpPoints, (int) nCount) != false;

   }


   bool graphics::fill_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::brush * pbrush)
   {

      ASSERT(get_handle1() != nullptr);

      ::color::color color32 = pbrush->m_color;

      if (m_pimage->is_null())
      {

         ::SetBkColor(get_handle1(), color32);
         ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);

      }
      else if (colorref_get_a_value(color32) == 255)
      {

         m_pimage->fill_rectangle(rectangle, argb(255, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32)));

      }
      else
      {

         ::image_pointer pimage = fill_image_work(color32, rectangle.size(), false);

         BLENDFUNCTION bf;
         bf.BlendOp = AC_SRC_OVER;
         bf.BlendFlags = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, ::width(rectangle), ::height(rectangle), (HDC)pimage->g()->get_os_data(), 0, 0, ::width(rectangle), ::height(rectangle), bf);

      }

      return true;

   }


   void graphics::frame_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::brush* pbrush)
   {

      ASSERT(get_handle1() != nullptr);

      ::FrameRect(get_handle1(), rectangle, (HBRUSH)pbrush->get_os_data());

   }


   void graphics::invert_rectangle(const ::rectangle_i32 & rectangle)
   {

      ASSERT(get_handle1() != nullptr);

      ::InvertRect(get_handle1(), rectangle);

   }


   bool graphics::DrawIcon(int x, int y, ::draw2d::icon * picon)
   {

      ASSERT(get_handle1() != nullptr);

      if (picon == nullptr)
      {

         return false;

      }

      return false;
      //      return ::DrawIcon(get_handle1(), x, y, picon->m_hicon)) != false;

   }


   bool graphics::DrawIcon(const ::point_i32 & point, ::draw2d::icon * picon)
   {

      ASSERT(get_handle1() != nullptr);

      if(picon == nullptr)
         return false;

      return false;
      //return ::DrawIcon(get_handle1(), point.x(), point.y(), picon->m_hicon) != false;

   }

   bool graphics::DrawIcon(int x, int y, ::draw2d::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {

      ASSERT(get_handle1() != nullptr);

      if(picon == nullptr)
         return false;

      if(m_pimage->is_null())
      {

         return ::DrawIconEx(get_handle1(), x, y, (HICON) picon->m_picon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags) != false;

      }
      else
      {

         ::image_pointer pimage;

         pimage = create_image({cx, cy});

         pimage->fill(0, 0, 0, 0);

         ::DrawIconEx((HDC)pimage->get_graphics()->get_os_data(), 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK);

         pimage->div_alpha();

         m_pimage->from(::point_i32(x, y), pimage, ::point_i32(), size_i32(cx, cy));

         return true;

      }

   }


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), hBrush,
   //                      nullptr, (LPARAM)hBitmap, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_BITMAP) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(),
   //                      nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_BITMAP) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), hBrush, nullptr,
   //                      (LPARAM)hIcon, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_ICON) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr,
   //                      (LPARAM)hIcon, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_ICON) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, const ::string & lpszText, UINT nFlags, bool bPrefixText, int nTextLen, HBRUSH hBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), hBrush,
   //                      nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x(), point.y(), size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, const ::string & lpszText, UINT nFlags, bool bPrefixText, int nTextLen, ::draw2d::brush* pBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(),
   //                      nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x(), point.y(), size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), hBrush,
   //                      lpDrawProc, lData, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;

   //}


   //bool graphics::DrawState(const ::point_i32 & point, ::size_i32 size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(),
   //                      lpDrawProc, lData, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;

   //}


   bool graphics::DrawEdge(RECT * prectangle, UINT nEdge, UINT nFlags)
   {

      ASSERT(get_handle1() != nullptr);

      return ::DrawEdge(get_handle1(), prectangle, nEdge, nFlags) != false;

   }


   bool graphics::DrawFrameControl(RECT * prectangle, UINT nType, UINT nState)
   {

      ASSERT(get_handle1() != nullptr);

      return ::DrawFrameControl(get_handle1(), prectangle, nType, nState) != false;

   }


   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;

   }


   bool graphics::Chord(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Chord(get_handle1(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y()) != false;

   }


   void graphics::DrawFocusRect(const ::rectangle_i32 & rectangle)
   {

      ASSERT(get_handle1() != nullptr);

      ::DrawFocusRect(get_handle1(), &rectangle);

   }


   bool graphics::ellipse(const ::rectangle_f64 & rectangle)
   {

      if(width(rectangle) <= 0 || height(rectangle) <= 0)
         return false;

      bool bOk = internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path_ellipse, (void *) &rectangle, rectangle, m_pbrush, m_ppen);

      return bOk;

   }


   bool graphics::draw_ellipse(const ::rectangle_f64 & rectangle)
   {

      if(width(rectangle) <= 0 || height(rectangle) <= 0)
         return false;

      bool bOk = internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_ellipse, (void *) &rectangle, rectangle, m_ppen);

      return bOk;

   }


   bool graphics::fill_ellipse(const ::rectangle_f64 & rectangle)
   {

      if(width(rectangle) <= 0 || height(rectangle) <= 0)
         return false;

      bool bOk = internal_fill_path(&::draw2d_gdi::graphics::internal_set_path_ellipse, (void *) &rectangle, rectangle, m_pbrush);

      return bOk;

   }


   bool graphics::rectangle_i32(const ::rectangle_i32 & rectangle)
   {

      if (width(rectangle) <= 0 || height(rectangle) <= 0)
      {

         return false;

      }

      bool bOk = internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path_rectangle, (void *)&rectangle, rectangle, m_pbrush, m_ppen);

      return bOk;

   }


   bool graphics::draw_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::pen * ppen)
   {

      if (width(rectangle) <= 0 || height(rectangle) <= 0)
      {

         return false;

      }

      ::draw2d::pen_pointer ppenPrevious = m_ppen;

      SelectObject(ppen);

      bool bOk = false;

      try
      {

         bOk = internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_rectangle, (void *)&rectangle, rectangle, m_ppen);

      }
      catch (...)
      {

      }

      SelectObject(ppenPrevious);

      return bOk;

   }


   bool graphics::draw_rectangle(const ::rectangle_i32 & rectangle)
   {

      if (width(rectangle) <= 0 || height(rectangle) <= 0)
      {

         return false;

      }

      bool bOk = internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_rectangle, (void *)&rectangle, rectangle, m_ppen);

      return bOk;

   }


   bool graphics::fill_rectangle(const ::rectangle_i32 & rectangle)
   {

      if (width(rectangle) <= 0 || height(rectangle) <= 0)
      {

         return false;

      }

      bool bOk = internal_fill_path(&::draw2d_gdi::graphics::internal_set_path_rectangle, (void *)&rectangle, rectangle, m_pbrush);

      return bOk;

   }


   bool graphics::polygon_i32(const POINT * lppoints, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if(rectangle.width() <= 0 || rectangle.height() <= 0)
         return false;

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.nCount = nCount;

      bool bOk = internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path_polygon, (void *) &item, rectangle, m_pbrush, m_ppen);

      return bOk;

   }


   bool graphics::draw_polygon(const POINT * lppoints, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if(rectangle.width() <= 0 || rectangle.height() <= 0)
         return false;

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.nCount = nCount;

      bool bOk = internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_polygon, (void *) &item, rectangle, m_ppen);

      return bOk;

   }


   bool graphics::fill_polygon(const POINT * lppoints, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if(rectangle.width() <= 0 || rectangle.height() <= 0)
         return false;

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.nCount = nCount;

      bool bOk = internal_fill_path(&::draw2d_gdi::graphics::internal_set_path_polygon, (void *) &item, rectangle, m_pbrush);

      return bOk;

   }


   bool graphics::poly_polygon(const POINT * lppoints, const INT * lpPolyCounts, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if (rectangle.width() <= 0 || rectangle.height() <= 0)
      {

         return false;

      }

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.lpPolyCounts = lpPolyCounts;

      item.nCount = nCount;

      bool bOk = internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path_poly_polygon, (void *) &item, rectangle,m_pbrush, m_ppen);

      return bOk;

   }


   bool graphics::draw_poly_polygon(const POINT * lppoints, const INT * lpPolyCounts, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if(rectangle.width() <= 0 || rectangle.height() <= 0)
         return false;

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.lpPolyCounts = lpPolyCounts;

      item.nCount = nCount;

      bool bOk = internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_poly_polygon, (void *) &item, rectangle, m_ppen);

      return bOk;

   }


   bool graphics::fill_poly_polygon(const POINT * lppoints, const INT * lpPolyCounts, count nCount)
   {

      ::rectangle_i32 rectangle;

      rectangle.get_bounding_rect(lppoints, nCount);

      if(rectangle.width() <= 0 || rectangle.height() <= 0)
         return false;

      draw_item item;

      zero(item);

      item.lpPoints = lppoints;

      item.lpPolyCounts = lpPolyCounts;

      item.nCount = nCount;

      bool bOk = internal_fill_path(&::draw2d_gdi::graphics::internal_set_path_poly_polygon, (void *) &item, rectangle, m_pbrush);

      return bOk;

   }


   bool graphics::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;

   }


   bool graphics::Pie(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Pie(get_handle1(), rectangle.left, rectangle.top,
                   rectangle.right, rectangle.bottom, pointStart.x(), pointStart.y(),
                   pointEnd.x(), pointEnd.y()) != false;

   }


   bool graphics::round_rectangle(const ::rectangle_i32 & rectangle, const ::point_i32 & point)
   {

      ASSERT(get_handle1() != nullptr);

      return ::RoundRect(get_handle1(), rectangle.left, rectangle.top, ::width(rectangle), ::height(rectangle), point.x(), point.y()) != false;

   }


   bool graphics::PatBlt(int x, int y, int nWidth, int nHeight, u32 dwRop)
   {

      ASSERT(get_handle1() != nullptr);

      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != false;

   }


   bool graphics::draw(const ::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::point_i32 & point, u32 dwRop)
   {

      i32 x = rectangle.left;
      i32 y = rectangle.top;
      i32 nWidth = ::width(rectangle);
      i32 nHeight = ::height(rectangle);
      i32 xSrc = point.x();
      i32 ySrc = point.y();

      synchronous_lock ml(synchronization());

      if(get_handle1() == nullptr)
         return false;

      if(m_pimage->is_null() || GDI_GRAPHICS(pgraphicsSrc)->m_pimage->is_null())
      {

         return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, GDI_HDC(pgraphicsSrc), xSrc, ySrc, dwRop) != false;

      }
      else
      {

         GdiFlush();


         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {
            ::point_i32 pointDst(x, y);
            ::size_i32 size(nWidth, nHeight);
            ::point_i32 pointSrc(xSrc, ySrc);

            ::image_pointer pimage = pgraphicsSrc->m_pimage;


            if(xSrc < 0)
            {
               pointDst.x() -= xSrc;
               xSrc = 0;
            }
            if(ySrc < 0)
            {
               pointDst.x() -= ySrc;
               ySrc = 0;
            }

            if(pointDst.x() < 0)
            {
               size.cx() += pointDst.x();
               pointDst.x() = 0;
            }

            if(size.cx() < 0)
               return true;

            if(pointDst.y() < 0)
            {
               size.cy() += pointDst.y();
               pointDst.y() = 0;
            }

            if(size.cy() < 0)
               return true;

            int xEnd = minimum(size.cx(), minimum(pimage->width() - pointSrc.x(), m_pimage->width() - pointDst->x));

            int yEnd = minimum(size.cy(), minimum(pimage->height() - pointSrc.y(), m_pimage->height() - pointDst->y));

            if(xEnd < 0)
               return false;

            if(yEnd < 0)
               return false;


            size.cx() = xEnd;
            size.cy() = yEnd;

            pimage = image_work(size, false);

            if(pimage->is_ok())
               return false;

            pimage->from(::point_i32(), pgraphicsSrc->m_pimage, ::point_i32(xSrc, ySrc), size);


            BLENDFUNCTION bf;
            bf.BlendOp     = AC_SRC_OVER;
            bf.BlendFlags  = 0;
            bf.SourceConstantAlpha = 0xFF;
            bf.AlphaFormat = AC_SRC_ALPHA;
            /*
            ::color::color * pcolorref = GDI_GRAPHICS(pgraphicsSrc)->m_pimage->m_pcolorref;
            i32 cx = GDI_GRAPHICS(pgraphicsSrc)->m_pimage->cx;
            i32 cy = GDI_GRAPHICS(pgraphicsSrc)->m_pimage->cy;
            i32 scan = GDI_GRAPHICS(pgraphicsSrc)->m_pimage->scan;

            ::color::color * pcolorref1 = m_pimage->m_pcolorref;
            i32 cx1 = m_pimage->cx;
            i32 cy1 = m_pimage->cy;
            i32 scan1 = m_pimage->scan;

            ::point_i32 point = GetViewportOrg();
            x += point.x();
            y += point.y();

            nWidth  = minimum(nWidth   , minimum(cx - xSrc, cx1 - x));
            nHeight = minimum(nHeight  , minimum(cy - ySrc, cy1 - y));

            for(int i = 0; i < nHeight; i++)
            {
            byte * p = &((byte *) pcolorref)[scan * (i + ySrc) + xSrc * sizeof(::color::color)];
            byte * p1 = &((byte *) pcolorref1)[scan1 * (i + y) + x * sizeof(::color::color)];
            for(int j = 0; j < nWidth; j++)
            {
            p1[0] = ((p[0] * p[3]) + ((255 - p[3]) * p1[0]))/ 255;
            p1[1] = ((p[1] * p[3]) + ((255 - p[3]) * p1[1]))/ 255;
            p1[2] = ((p[2] * p[3]) + ((255 - p[3]) * p1[2]))/ 255;
            p1[3] = ((p[3] * p[3]) + ((255 - p[3]) * p1[3]))/ 255;

            /*if(p1[3] == 0)
            {
            p1[0] = 0;
            p1[1] = 0;
            p1[2] = 0;
            }
            else
            {
            p1[0] = (p1[0] * 255 / p1[3]);
            p1[1] = (p1[1] * 255 / p1[3]);
            p1[2] = (p1[2] * 255 / p1[3]);
            }*/
            /*
            p += 4;
            p1 += 4;
            }
            }
            */

            pimage->mult_alpha();

            /*      i64 iArea = pimage->area();

            byte * pcolorref = (byte *) pimage->get_data();

            GdiFlush();

            for(int y = 0; y < pimage->cy; y++)
            {
            byte * p = &pcolorref[pimage->scan * y];
            for(int x = 0; x < pimage->cx; x++)
            {
            p[0] = (p[0] * p[3] / 255);
            p[1] = (p[1] * p[3] / 255);
            p[2] = (p[2] * p[3] / 255);
            p += 4;
            }
            }*/

            GdiFlush();

            ::AlphaBlend(m_hdc, pointDst.x(), pointDst.y(), size.cx(), size.cy(), (HDC) pimage->g()->get_os_data(), 0, 0, size.cx(), size.cy(), bf);

            /*for(int y = 0; y < nHeight; y++)
            {
            byte * p = &((byte *) pcolorref)[scan * (y + ySrc) + xSrc * sizeof(::color::color)];
            for(int x = 0; x < nWidth; x++)
            {
            if(p[3] == 0)
            {
            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            }
            else
            {
            p[0] = (p[0] * 255 / p[3]);
            p[1] = (p[1] * 255 / p[3]);
            p[2] = (p[2] * 255 / p[3]);
            }
            p += 4;
            }
            }*/

            /*            for(int i = 0; i < nHeight; i++)
            {
            byte * p1 = &((byte *) pcolorref1)[scan1 * (i + y) + x * sizeof(::color::color)];
            for(int j = 0; j < nWidth;jx++)
            {
            if(p1[3] == 0)
            {
            p1[0] = 0;
            p1[1] = 0;
            p1[2] = 0;
            }
            else
            {
            p1[0] = (p1[0] * 255 / p1[3]);
            p1[1] = (p1[1] * 255 / p1[3]);
            p1[2] = (p1[2] * 255 / p1[3]);
            }
            p1 += 4;
            }
            }*/

            return true;

         }
         else
         {

            m_pimage->from(::point_i32(x, y), GDI_GRAPHICS(pgraphicsSrc)->m_pimage, ::point_i32(), size_i32(nWidth, nHeight));

            return true;

         }

      }


   }




   bool graphics::StretchBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, u32 dwRop)
   {

      synchronous_lock ml(synchronization());

      if (get_handle1() == nullptr)
         return false;

      if(m_pimage->is_null())
      {

         return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, GDI_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight,  dwRop) != false;

      }
      else
      {

         ::image_pointer pimage1 = image_work(size(nWidth, nHeight), false);

         if(pimage1->is_null())
            return false;

         ::image_pointer pimage2 = image_work(size(nSrcWidth, nSrcHeight), false);

         if(pimage2->is_null())
            return false;

         pimage2->from(::point_i32(), pgraphicsSrc->m_pimage, ::point_i32(xSrc, ySrc), pimage2->size());


         //   ::StretchDIBits(
//   GDI_HDC(m_spgraphics.m_p),
//   0, 0,
//   pimage1->m_pdata.width(), pimage1->m_pdata.height(),
//   0, 0,
//   pimage->get_size().cx(), pimage->get_size().cy(),
//   pimage->get_data(),
//   &dynamic_cast < image_impl * > (image_impl)->m_info,
//   DIB_RGB_COLORS,
//   SRCCOPY);

//         pimage1->stretch_image(pimage2);

         ::image_pointer pimpl1 = pimage1->m_pimpl;

         pimpl1->stretch_image(pimage2);

         pimage1->mult_alpha();

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         return ::AlphaBlend(m_hdc,x,y,nWidth,nHeight,(HDC)pimage1->get_graphics()->get_os_data(),0,0,nWidth,nHeight,bf) != false;



      }

   }


   ::color::color graphics::GetPixel(int x, int y)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetPixel(get_handle1(), x, y);

   }


   ::color::color graphics::GetPixel(const ::point_i32 & point)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetPixel(get_handle1(), point.x(), point.y());

   }


   ::color::color graphics::SetPixel(int x, int y, ::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetPixel(get_handle1(), x, y, crColor);

   }


   ::color::color graphics::SetPixel(const ::point_i32 & point, ::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetPixel(get_handle1(), point.x(), point.y(), crColor);

   }


   bool graphics::FloodFill(int x, int y, ::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::FloodFill(get_handle1(), x, y, crColor) != false;

   }


   bool graphics::ExtFloodFill(int x, int y, ::color::color crColor, UINT nFillType)
   {

      ASSERT(get_handle1() != nullptr);

      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != false;

   }



   bool graphics::text_out(double x, double y, const ::string & lpszString, strsize nCount)
   {

      synchronous_lock ml(synchronization());

      if (::draw2d::graphics::text_out(x, y, lpszString, nCount))
         return true;

      if (get_handle1() == nullptr)
         return false;

      ASSERT(get_handle1() != nullptr);

      string str(lpszString, nCount);

      wstring wstr = utf8_to_unicode(str);

      ::draw2d::brush & brush = *get_current_brush();
      ::write_text::font & font = *get_current_font();

      select_font();

      if(m_pimage->is_null())
      {

         ::SetBkMode(m_hdc, TRANSPARENT);

         ::SetTextColor(m_hdc, rgb(colorref_get_r_value(brush.m_color), colorref_get_g_value(brush.m_color), colorref_get_b_value(brush.m_color)));

         return ::TextOutW(get_handle1(), (int) x, (int) y, wstr, (int) wstr.length()) != false;

      }
      else
      {

         ::size_i32 size;

         if(!::GetTextExtentPoint32W(get_handle2(), wstr, (int) wstr.get_length(), &size))
         {

            return false;

         }

         ::image_pointer pimage = image_work(size, true);

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         if(!GDI_DIB(pimage.m_p)->process_initialize(&brush))
            return false;

         if(GDI_BRUSH(&brush)->m_bProcess)
         {

            GDI_GRAPHICS(pimage->g())->SetTextColor(rgb(255, 255, 255));

         }
         else
         {

            //GDI_GRAPHICS(pimage->g())->SetTextColor(rgb(colorref_get_r_value(brush.m_color), colorref_get_g_value(brush.m_color), colorref_get_b_value(brush.m_color)));
            GDI_GRAPHICS(pimage->g())->SetTextColor(rgb(colorref_get_b_value(brush.m_color), colorref_get_g_value(brush.m_color), colorref_get_r_value(brush.m_color)));

         }


         pimage->g()->SelectObject(&font);

         ::SetBkMode((HDC) pimage->g()->get_os_data(), TRANSPARENT);

         ::TextOutW((HDC) pimage->g()->get_os_data(), 0, 0, wstr, (int) wstr.length());

         ::point_i32 point = GetViewportOrg();

         GDI_DIB(pimage.m_p)->process_blend(&brush, (int) x + point.x(), (int) y + point.y(), m_ealphamode, m_pimage);

         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {

            pimage->dc_select();

            ::AlphaBlend(m_hdc, (int) x, (int) y, size.cx(), size.cy(), (HDC) pimage->g()->get_os_data(), 0, 0, size.cx(), size.cy(), bf);

         }

         return true;

      }


   }



   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::text_out(int x, int y, const ::string & str)
   {

      return text_out(x, y, str, (int) str.length());

   }

   // call virtual

   bool graphics::ExtTextOut(int x, int y, UINT nOptions, const ::rectangle_i32 & rectangle, const ::string & lpszString, strsize nCount, LPINT lpDxWidths)
   {

      ASSERT(get_handle1() != nullptr);

      return ::ExtTextOutW(get_handle1(), x, y, nOptions, &rectangle, wstring(lpszString), (UINT) nCount, lpDxWidths) != false;

   }


   bool graphics::ExtTextOut(int x, int y, UINT nOptions, const ::rectangle_i32 & rectangle, const ::string & str, LPINT lpDxWidths)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(str);

      return ::ExtTextOut(get_handle1(), x, y, nOptions, &rectangle, wstr, wstr.get_length(), lpDxWidths) != false;

   }


   ::size_i32 graphics::TabbedTextOut(int x, int y, const ::string & lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(lpszString);

      return (u32) ::TabbedTextOutW(get_handle1(), x, y, wstr,wstr.get_length(), (int) nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   ::size_i32 graphics::TabbedTextOut(int x, int y, const ::string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(str);

      return (u32) ::TabbedTextOutW(get_handle1(), x, y, wstr, (int)wstr.get_length(), (int) nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   bool graphics::draw_text(const ::string & lpszString, strsize nCount, const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      return _DrawText(lpszString, nCount, rectangle, nFormat);

   }


   bool graphics::draw_text(const ::string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      return draw_text(str, (int) str.length(), rectangle, nFormat);

   }


   bool graphics::draw_text_ex(const ::string & lpszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   {

      wstring wstr(string(lpszString, nCount));

      return DrawTextExW(get_handle(), (wchar_t *) (const wchar_t *)  wstr, (int) wstr.get_length(),(LPRECT) &rectangle, nFormat, lpDTParams);

   }


   bool graphics::draw_text_ex(const ::string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   {

      return draw_text_ex((char *) (const ::string &) str, (int) str.length(), rectangle, nFormat, lpDTParams);

   }


   ::size_i32 graphics::GetTabbedTextExtent(const ::string & lpszString,strsize nCount,count  nTabPositions,LPINT lpnTabStopPositions)
   {

      ASSERT(get_handle2() != nullptr);
      wstring wstr(string(lpszString, nCount));

      return (u32) ::GetTabbedTextExtent(get_handle2(), wstr, (int)wstr.get_length() , (int)nTabPositions, lpnTabStopPositions);

   }


   ::size_i32 graphics::GetTabbedTextExtent(const ::string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ASSERT(get_handle2() != nullptr);

      wstring wstr(str);

      return (u32) ::GetTabbedTextExtentW(get_handle2(), wstr, (int)wstr.get_length(), (int) nTabPositions, lpnTabStopPositions);

   }


   ::size_i32 graphics::GetOutputTabbedTextExtent(const ::string & lpszString,strsize nCount, count nTabPositions,LPINT lpnTabStopPositions)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(string(lpszString, nCount));

      return (u32) ::GetTabbedTextExtent(get_handle1(), wstr, (int) wstr.get_length(), (int) nTabPositions, lpnTabStopPositions);

   }


   ::size_i32 graphics::GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(str);

      return (u32) ::GetTabbedTextExtent(get_handle1(), wstr, (int)wstr.get_length(), (int) nTabPositions, lpnTabStopPositions);

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(), (GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;

   }


   UINT graphics::GetTextAlign()
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetTextAlign(get_handle2());

   }


   int graphics::GetTextFace(count nCount, LPTSTR lpszFacename)
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetTextFace(get_handle2(), (int) nCount, lpszFacename);

   }


   int graphics::GetTextFace(string & rString)
   {

      ASSERT(get_handle2() != nullptr);

      wstring wstr;

      int nResult = ::GetTextFaceW(get_handle2(), 256, wstr.get_buffer(256)); wstr.release_buffer();

      rString = wstr;

      return nResult;

   }


   bool graphics::get_text_metrics(::write_text::text_metric * lpMetrics)
   {

      HDC h2 = get_handle2();

      if (h2 == nullptr)
         return false;

      TEXTMETRICW tm;

      if(!::GetTextMetricsW(h2,&tm))
         return false;

      lpMetrics->tmAscent = tm.tmAscent;
      //lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;
      lpMetrics->tmBreakChar = tm.tmBreakChar;
      lpMetrics->tmCharSet = tm.tmCharSet;
      lpMetrics->tmDefaultChar = tm.tmDefaultChar;
      lpMetrics->tmDescent = tm.tmDescent;
      lpMetrics->tmDigitizedAspectX = tm.tmDigitizedAspectX;
      lpMetrics->tmDigitizedAspectY = tm.tmDigitizedAspectY;
      lpMetrics->tmExternalLeading = tm.tmExternalLeading;
      lpMetrics->tmFirstChar = tm.tmFirstChar;
      lpMetrics->tmHeight = tm.tmHeight;
      lpMetrics->tmInternalLeading = tm.tmInternalLeading;
      lpMetrics->tmItalic = tm.tmItalic;
      lpMetrics->tmLastChar = tm.tmLastChar;
      //lpMetrics->tmMaxCharWidth = tm.tmMaxCharWidth;
      lpMetrics->tmOverhang = tm.tmOverhang;
      lpMetrics->tmPitchAndFamily = tm.tmPitchAndFamily;
      lpMetrics->tmStruckOut = tm.tmStruckOut;
      lpMetrics->tmUnderlined = tm.tmUnderlined;
      lpMetrics->tmWeight = tm.tmWeight;

      return true;

   }


   bool graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
   {

      ASSERT(get_handle1() != nullptr);

      TEXTMETRICW tm;

      if(!::GetTextMetricsW(get_handle1(),&tm))
         return false;

      lpMetrics->tmAscent = tm.tmAscent;
      //lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;
      lpMetrics->tmBreakChar = tm.tmBreakChar;
      lpMetrics->tmCharSet = tm.tmCharSet;
      lpMetrics->tmDefaultChar = tm.tmDefaultChar;
      lpMetrics->tmDescent = tm.tmDescent;
      lpMetrics->tmDigitizedAspectX = tm.tmDigitizedAspectX;
      lpMetrics->tmDigitizedAspectY = tm.tmDigitizedAspectY;
      lpMetrics->tmExternalLeading = tm.tmExternalLeading;
      lpMetrics->tmFirstChar = tm.tmFirstChar;
      lpMetrics->tmHeight = tm.tmHeight;
      lpMetrics->tmInternalLeading = tm.tmInternalLeading;
      lpMetrics->tmItalic = tm.tmItalic;
      lpMetrics->tmLastChar = tm.tmLastChar;
      //lpMetrics->tmMaxCharWidth = tm.tmMaxCharWidth;
      lpMetrics->tmOverhang = tm.tmOverhang;
      lpMetrics->tmPitchAndFamily = tm.tmPitchAndFamily;
      lpMetrics->tmStruckOut = tm.tmStruckOut;
      lpMetrics->tmUnderlined = tm.tmUnderlined;
      lpMetrics->tmWeight = tm.tmWeight;

      return true;


   }


   int graphics::GetTextCharacterExtra()
   {
      ASSERT(get_handle2() != nullptr); return ::GetTextCharacterExtra(get_handle2());

   }


   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {
      ASSERT(get_handle2() != nullptr); return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != false;

   }


   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != false;

   }


   u32 graphics::GetFontLanguageInfo()
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetFontLanguageInfo(get_handle1());

   }



   u32 graphics::GetCharacterPlacement(const ::string & lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(string(lpString, nCount));

      return ::GetCharacterPlacementW(get_handle1(), wstr, (int)wstr.get_length(), (int) nMaxExtent, lpResults, dwFlags);

   }


   u32 graphics::GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
   {

      ASSERT(get_handle1() != nullptr);

      wstring wstr(str);

      return ::GetCharacterPlacementW(get_handle1(), wstr, (int) wstr.get_length(), (int) nMaxExtent, lpResults, dwFlags);

   }




   size_i32 graphics::GetAspectRatioFilter()
   {
      ASSERT(get_handle2() != nullptr);
      ::size_i32 size;
      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
      return size;
   }
   bool graphics::ScrollDC(int dx, int dy,
                           const ::rectangle_i32 & lpRectScroll, const ::rectangle_i32 & lpRectClip,
                           ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
   {

      ASSERT(get_handle1() != nullptr);

      return ::ScrollDC(get_handle1(), dx, dy, &lpRectScroll,
                        &lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;

   }



   // Printer Escape Functions
   int graphics::Escape(int nEscape, int nCount, const ::string & lpszInData, LPVOID lpOutData)
   {

      ASSERT(get_handle1() != nullptr);

      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);
   }

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const ::rectangle_i32 & rectangleBounds, UINT flags)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetBoundsRect(get_handle1(), &rectangleBounds, flags);

   }


   UINT graphics::GetBoundsRect(LPRECT rectangleBounds, UINT flags)
   {
      ASSERT(get_handle2() != nullptr); return ::GetBoundsRect(get_handle2(), rectangleBounds, flags);

   }


   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   { ASSERT(get_handle2() != nullptr); return ::ResetDC(get_handle2(), lpDevMode) != nullptr; }
   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm)
   {
      ASSERT(get_handle2() != nullptr); return ::GetOutlineTextMetricsW(get_handle2(), cbData, lpotm) != false;

   }


   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc)
   {
      ASSERT(get_handle2() != nullptr); return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != false;

   }


   u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData,
                                  u32 cbData)
   {
      ASSERT(get_handle2() != nullptr); return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);

   }


   int graphics::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair)
   {
      ASSERT(get_handle2() != nullptr); return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);

   }


   u32 graphics::GetGlyphOutline(UINT nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm,
                                      u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2)
   {
      ASSERT(get_handle2() != nullptr); return ::GetGlyphOutline(get_handle2(), nChar, nFormat,
            lpgm, cbBuffer, lpBuffer, lpmat2);

   }



   // ::userbase::document handling functions
   int graphics::StartDoc(LPDOCINFOW lpDocInfo)
   {

      ASSERT(get_handle1() != nullptr);

      return ::StartDocW(get_handle1(), lpDocInfo);

   }


   int graphics::StartPage()
   {

      ASSERT(get_handle1() != nullptr);

      return ::StartPage(get_handle1());

   }


   int graphics::EndPage()
   {

      ASSERT(get_handle1() != nullptr);

      return ::EndPage(get_handle1());

   }


   int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }


   int graphics::AbortDoc()
   {

      ASSERT(get_handle1() != nullptr);

      return ::AbortDoc(get_handle1());

   }


   int graphics::EndDoc()
   {

      ASSERT(get_handle1() != nullptr);

      return ::EndDoc(get_handle1());

   }



   bool graphics::MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                          int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask, u32 dwRop)
   {

      ASSERT(get_handle1() != nullptr);

      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, GDI_HDC(pgraphicsSrc),
                       xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;

   }


   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
                         int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask)
   {

      ASSERT(get_handle1() != nullptr);

      return ::PlgBlt(get_handle1(), lpPoint, GDI_HDC(pgraphicsSrc), xSrc, ySrc, nWidth,
                      nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != false;

   }


   bool graphics::SetPixelV(int x, int y, ::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetPixelV(get_handle1(), x, y, crColor) != false;

   }


   bool graphics::SetPixelV(const ::point_i32 & point, ::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetPixelV(get_handle1(), point.x(), point.y(), crColor) != false;

   }


   bool graphics::AngleArc(int x, int y, int nRadius,
                           float fStartAngle, float fSweepAngle)
   {

      ASSERT(get_handle1() != nullptr);

      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != false;

   }




   bool graphics::ArcTo(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd)
   {

      ASSERT(get_handle1() != nullptr); return ArcTo(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y()) != false;

   }




   int graphics::GetArcDirection()
   {

      ASSERT(get_handle2() != nullptr); return ::GetArcDirection(get_handle2());

   }




   bool graphics::poly_polyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      return ::poly_polyline(get_handle1(), lpPoints, (const DWORD *) lpPolyPoints, (int) nCount) != false;

   }




   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != false;

   }


   void graphics::set_original_object(int iType)
   {

      switch(iType)
      {
      case OBJ_BITMAP:
         ::SelectObject(m_hdc, m_hbitmapOriginal);
         return;
      case OBJ_PEN:
         ::SelectObject(m_hdc, m_hpenOriginal);
         return;
      case OBJ_BRUSH:
         ::SelectObject(m_hdc, m_hbrushOriginal);
         return;
      case OBJ_FONT:
         ::SelectObject(m_hdc, m_hfontOriginal);
         return;
      case OBJ_REGION:
         ::SelectObject(m_hdc, m_hrgnOriginal);
         return;
      default:
         break;
      }

   }


   ::draw2d::pen * graphics::get_current_pen()
   {

      if(m_ppen.is_set())
         return m_ppen;

      ASSERT(get_handle2() != nullptr);

      ::draw2d_gdi::attach(this, m_ppen, OBJ_PEN);

      return m_ppen;

   }


   ::draw2d::brush * graphics::get_current_brush()
   {

      if (m_pbrush.is_set())
      {

         return m_pbrush;

      }

      ASSERT(get_handle2() != nullptr);

      ::draw2d_gdi::attach(this, m_pbrush, OBJ_BRUSH);

      LOGBRUSH lb;

      (dynamic_cast < ::draw2d_gdi::brush * > (((graphics *) this)->m_pbrush.m_p))->GetLogBrush(&lb);

      m_pbrush->m_color = lb.lbColor | 255 << 24;

      m_pbrush->m_etype = ::draw2d::brush::type_solid;

      m_pbrush->m_bUpdated = true;

      return m_pbrush;

   }


   ::draw2d::palette * graphics::get_current_palette()
   {


      return ((::draw2d::palette *) nullptr);


   }


   ::write_text::font * graphics::get_current_font()
   {

      if(m_pfont.is_set())
         return m_pfont;

      ASSERT(get_handle2() != nullptr);

      ::draw2d_gdi::attach(this, m_pbrush, OBJ_FONT);

      return m_pfont;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      if(m_pbitmap.is_set() && m_pbitmap->get_os_data() == (void *) ::GetCurrentObject(get_handle2(), OBJ_BITMAP))
         return m_pbitmap;

      ASSERT(get_handle2() != nullptr);

      ::draw2d_gdi::attach(this, m_pbrush, OBJ_BITMAP);

      return m_pbitmap;

   }


   bool graphics::poly_bezier(const POINT* lpPoints, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      return ::poly_bezier(get_handle1(), lpPoints, (DWORD) nCount) != false;

   }


   int graphics::DrawEscape(int nEscape, int nInputSize, const ::string & lpszInputData)
   {

      ASSERT(get_handle1() != nullptr);

      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }




   int graphics::Escape(int nEscape, int nInputSize, const ::string & lpszInputData, int nOutputSize, char * lpszOutputData)
   {

      ASSERT(get_handle1() != nullptr);

      return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);

   }




   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF)
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != false;

   }


   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer)
   {

      ASSERT(get_handle2() != nullptr);

      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != false;

   }


   bool graphics::abort_path()
   {

      ASSERT(get_handle1() != nullptr);

      return ::AbortPath(get_handle1()) != false;

   }


   bool graphics::begin_path()
   {

      if(get_handle1() == nullptr)
         return false;

      return ::BeginPath(get_handle1()) != false;

   }


   bool graphics::close_figure()
   {

      ASSERT(get_handle1() != nullptr);

      return ::CloseFigure(get_handle1()) != false;

   }


   bool graphics::end_path()
   {

      if(get_handle1() == nullptr)
         return false;

      return ::EndPath(get_handle1()) != false;

   }


   bool graphics::fill_path()
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_fill_path(&::draw2d_gdi::graphics::internal_set_path, m_sppath.m_p, rectangle, m_pbrush);

      /*if(m_sppath.is_null())
      return false;

      ASSERT(get_handle1() != nullptr);

      ::draw2d::brush & brush = get_current_brush();

      if(m_pimage->is_null())
      {

      set(m_sppath);

      return ::FillPath(get_handle1()) != false;

      }
      else
      {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      ::image_pointer pimage = image_work(rectangle.size());

      BLENDFUNCTION bf;
      bf.BlendOp     = AC_SRC_OVER;
      bf.BlendFlags  = 0;
      bf.SourceConstantAlpha = 0xFF;
      bf.AlphaFormat = AC_SRC_ALPHA;

      if(!GDI_DIB(pimage.m_p)->process_initialize(&brush))
      return false;

      pimage->g()->SelectObject(&brush);

      GDI_GRAPHICS(pimage->g())->SetViewportOrg(-rectangle.top_left());

      GDI_GRAPHICS(pimage->g())->set(m_sppath);

      ::FillPath((HDC) pimage->g()->get_os_data());

      GDI_DIB(pimage.m_p)->process_blend(&brush, rectangle.left, rectangle.top, m_ealphamode);

      GDI_GRAPHICS(pimage->g())->SetViewportOrg(0, 0);

      ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), (HDC) pimage->g()->get_os_data(), 0, 0, rectangle.width(), rectangle.height(), bf);

      return true;

      }*/

   }


   bool graphics::fill_path(::draw2d::brush * pbrush)
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_fill_path(&::draw2d_gdi::graphics::internal_set_path,m_sppath.m_p,rectangle,pbrush);



   }


   void graphics::internal_set_path(void * pparam)
   {

      ::draw2d::path * ppath = (::draw2d::path *) pparam;

      set(ppath);

   }


   void graphics::internal_set_path_ellipse(void * pparam)
   {

      LPRECT lprect = (LPRECT) pparam;

      begin_path();

      ::Ellipse(m_hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);

      end_path();

   }


   void graphics::internal_set_path_rectangle(void * pparam)
   {

      LPRECT lprect = (LPRECT) pparam;

      begin_path();

      ::rectangle(m_hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);

      end_path();

   }


   void graphics::internal_set_path_line(void * pparam)
   {

      LPRECT lprect = (LPRECT) pparam;

      begin_path();

      ::MoveToEx(m_hdc, lprect->left, lprect->top, nullptr);

      ::LineTo(m_hdc, lprect->right, lprect->bottom);

      end_path();

   }


   void graphics::internal_set_path_polygon(void * pparam)
   {

      draw_item * pitem = (draw_item *) pparam;

      begin_path();

      ::Polygon(m_hdc, pitem->lpPoints, (int) pitem->nCount);

      end_path();

   }


   void graphics::internal_set_path_poly_polygon(void * pparam)
   {

      draw_item * pitem = (draw_item *) pparam;

      begin_path();

      ::PolyPolygon(m_hdc, pitem->lpPoints, pitem->lpPolyCounts, (int) pitem->nCount);

      end_path();

   }


   bool graphics::internal_fill_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam,const ::rectangle_i32 & rectangleParam,::draw2d::brush * pbrush)
   {

      synchronous_lock ml(synchronization());

      ASSERT(get_handle1() != nullptr);

      ::draw2d::brush & brush = *pbrush;

      if(brush.m_etype == ::draw2d::brush::e_type_null)
         return true;

      if(m_pimage->is_null())
      {

         (this->*pfnInternalSetPath)(pparam);

         return ::FillPath(get_handle1()) != false;

      }
      else
      {

         ::rectangle_i32 rectangle(rectangleParam);

         ::image_pointer pimage = image_work(rectangle.size(), false);

         if (pimage)
         {

            return false;

         }

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         if(!GDI_DIB(pimage.m_p)->process_initialize(&brush))
            return false;

         pimage->g()->SelectObject(&brush);

         GDI_GRAPHICS(pimage->g())->SetViewportOrg(-rectangle.top_left());

         (GDI_GRAPHICS(pimage->g())->*pfnInternalSetPath)(pparam);

         ::FillPath((HDC) pimage->g()->get_os_data());

         GDI_DIB(pimage.m_p)->process_blend(&brush, rectangle.left, rectangle.top, m_ealphamode, m_pimage);

         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {

            GDI_GRAPHICS(pimage->g())->SetViewportOrg(0, 0);

            ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), (HDC) pimage->g()->get_os_data(), 0, 0, rectangle.width(), rectangle.height(), bf);

         }

         return true;

      }

   }


   bool graphics::flatten_path()
   {

      ASSERT(get_handle1() != nullptr);

      return ::FlattenPath(get_handle1()) != false;

   }


   float graphics::GetMiterLimit()
   {

      ASSERT(get_handle1() != nullptr);

      float fMiterLimit;

      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));

      return fMiterLimit;

   }


   int graphics::GetPath(LPPOINT lpPoints, byte * lpTypes, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetPath(get_handle1(), lpPoints, lpTypes, (int) nCount);

   }




   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != false;

   }


   bool graphics::stroke_and_fill_path(::draw2d::brush * pbrush, ::draw2d::pen * ppen)
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path,m_sppath.m_p,rectangle,pbrush,ppen);

   }


   bool graphics::stroke_path(::draw2d::pen * ppen)
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path,m_sppath.m_p,rectangle,ppen);

   }


   bool graphics::stroke_and_fill_path()
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_fill_and_stroke_path(&::draw2d_gdi::graphics::internal_set_path, m_sppath.m_p, rectangle, m_pbrush, m_ppen);

   }


   bool graphics::stroke_path()
   {

      ::rectangle_i32 rectangle;

      m_sppath->get_bounding_rect(rectangle);

      return internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path, m_sppath.m_p, rectangle, m_ppen);

   }


   bool graphics::internal_stroke_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam,const ::rectangle_i32 & rectangleParam,::draw2d::pen * ppen)
   {

      synchronous_lock ml(synchronization());

      ASSERT(get_handle1() != nullptr);

      ::draw2d::pen & pen = *ppen;

      if(pen.m_etype == ::draw2d::pen::e_type_null)
         return true;

      if(m_pimage->is_null())
      {

         (this->*pfnInternalSetPath)(pparam);

         return ::FillPath(get_handle1()) != false;

      }
      else
      {

         ::rectangle_i32 rectangleBound(rectangleParam);

         //m_sppath->get_bounding_rect(rectangleBound);

         ::rectangle_i32 rectangle(rectangleBound);

         rectangle.left   -= (i32) floor(pen.m_dWidth / 2.0);
         rectangle.right  += (i32) ceil(pen.m_dWidth / 2.0);
         rectangle.top    -= (i32) floor(pen.m_dWidth / 2.0);
         rectangle.bottom += (i32) ceil(pen.m_dWidth / 2.0);

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         ::image_pointer pimage = image_work(rectangle.size(), false);

         if(pimage->is_ok())
            return false;

         if(!GDI_DIB(pimage.m_p)->process_initialize(&pen))
            return false;

         pimage->g()->SelectObject(&pen);

         pimage->g()->SetViewportOrg(-rectangleBound.top_left());

         (GDI_GRAPHICS(pimage->g())->*pfnInternalSetPath)(pparam);

         ::StrokePath(GDI_HDC(pimage->g()));

         GDI_DIB(pimage.m_p)->process_blend(&pen, rectangle.left, rectangle.top, m_ealphamode, m_pimage);

         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {

            GDI_GRAPHICS(pimage->g())->SetViewportOrg(0, 0);

            ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), (HDC) pimage->g()->get_os_data(), 0, 0, rectangle.width(), rectangle.height(), bf);

         }

         return true;

      }

   }


   bool graphics::internal_fill_and_stroke_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam,const ::rectangle_i32 & rectangleParam,::draw2d::brush * pbrush,::draw2d::pen * ppen)
   {

      synchronous_lock ml(synchronization());

      ASSERT(get_handle1() != nullptr);

      ::draw2d::pen & pen = *ppen;

      if(pen.m_etype == ::draw2d::pen::e_type_null)
         return internal_fill_path(pfnInternalSetPath, pparam, rectangleParam, pbrush);

      ::draw2d::brush & brush = *pbrush;

      if(brush.m_etype == ::draw2d::brush::e_type_null)
         return internal_stroke_path(pfnInternalSetPath, pparam, rectangleParam, ppen);

      if(m_pimage->is_null())
      {

         (this->*pfnInternalSetPath)(pparam);

         return ::StrokeAndFillPath(get_handle1()) != false;

      }
      else
      {

         ::rectangle_i32 rectangleBound(rectangleParam);

         ::rectangle_i32 rectangle(rectangleBound);

         rectangle.left   -= (i32) floor(pen.m_dWidth / 2.0);
         rectangle.right  += (i32) floor(pen.m_dWidth / 2.0);
         rectangle.top    -= (i32) floor(pen.m_dWidth / 2.0);
         rectangle.bottom += (i32) floor(pen.m_dWidth / 2.0);

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         ::image_pointer pimage = image_work(rectangle.size(), false);

         if(pimage->is_ok())
            return false;

         if(GDI_DIB(pimage.m_p)->process_initialize(&brush))
         {

            pimage->g()->SelectObject(&brush);

            GDI_GRAPHICS(pimage->g())->SetViewportOrg(-rectangle.top_left() + ::size_i32((i32) floor(pen.m_dWidth / 2.0), (i32) floor(pen.m_dWidth / 2.0)));

            (GDI_GRAPHICS(pimage->g())->*pfnInternalSetPath)(pparam);

            ::FillPath((HDC) pimage->g()->get_os_data());

            if(GDI_DIB(pimage.m_p)->process_blend(&brush, rectangle.left, rectangle.top, m_ealphamode, m_pimage))
            {

               if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
               {

                  GDI_GRAPHICS(pimage->g())->SetViewportOrg(0, 0);

                  ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), (HDC) pimage->g()->get_os_data(), 0, 0, rectangle.width(), rectangle.height(), bf);

               }
               /*
               else
               {

               m_pimage->from_ignore_alpha(rectangle_i32->top_left() + GetViewportOrg(), pimage, ::point_i32(), rectangle_i32->size());

               }
               */

            }

         }


         //::image_pointer pimage2 = image_work(rectangle.size());

         if(GDI_DIB(pimage.m_p)->process_initialize(&pen))
         {

            // pimage2->from(point_i32((i32) floor(pen.m_dWidth / 2.0), (i32) floor(pen.m_dWidth / 2.0)), pimage, ::point_i32(), rectangle.size());

            pimage->g()->SelectObject(&pen);

            pimage->g()->SetViewportOrg(-rectangleBound.top_left());

            (GDI_GRAPHICS(pimage->g())->*pfnInternalSetPath)(pparam);

            ::StrokePath(GDI_HDC(pimage->g()));

            if(GDI_DIB(pimage.m_p)->process_blend(&pen, rectangle.left, rectangle.top, m_ealphamode, m_pimage))
            {

               if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
               {

                  GDI_GRAPHICS(pimage->g())->SetViewportOrg(0, 0);

                  ::AlphaBlend(m_hdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), (HDC) pimage->g()->get_os_data(), 0, 0, rectangle.width(), rectangle.height(), bf);

               }
               /*
               else
               {

               m_pimage->from_ignore_alpha(rectangle_i32->top_left() + GetViewportOrg(), pimage, ::point_i32(), rectangle_i32->size());

               }
               */

            }

         }

         return true;

      }

   }


   bool graphics::widen_path()
   {

      ASSERT(get_handle1() != nullptr);

      return ::WidenPath(get_handle1()) != false;

   }




   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != false;

   }


   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::rectangle_i32 & rectangleBounds)
   {

      return ::PlayEnhMetaFile(get_handle1(), hEnhMF, rectangleBounds) != false;

   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   /*bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BLENDFUNCTION blend)
   {


   if(get_handle1() == nullptr)
   return false;


   if(m_pimageAlphaBlend->is_set())
   {


   ::rectangle_i32 rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


   ::image_pointer pimageWork = nullptr;
   ::image_pointer pimageWork2 = nullptr;
   //         ::image_pointer pimageWork3 = nullptr;
   ::image_pointer pimageWork4 = nullptr;


   ::point_i32 pointSrc(xSrc, ySrc);
   ::point_i32 pointDest(xDest, yDest);
   ::size_i32 size(nDestWidth, nDestHeight);



   ::image_pointer pimage;

   if(imageWork == nullptr)
   {

   pimage->create(this);

   imageWork = pimage;

   }

   if(imageWork == nullptr)
   return false;

   if(!imageWork = create_image(size))
   return false;

   if(!imageWork.from(::point_i32(), pgraphicsSrc, pointSrc, size))
   return false;




   ::image_pointer pimage2;
   if(imageWork2 == nullptr)
   {
   pimage2->create(this);
   imageWork2 = pimage2;
   }


   ::image_pointer pimage4;
   if(imageWork4 == nullptr)
   {
   image4.create(this);
   imageWork4 = image4;
   }
   if(imageWork4 == nullptr)
   return false;
   if(!imageWork4 = create_image(size))
   return false;


   imageWork4.Fill(255, 0, 0, 0);

   imageWork4.from(point_i32(maximum(0, m_pointAlphaBlend.x() - xDest), maximum(0, m_pointAlphaBlend.y() - yDest)),
   m_pimageAlphaBlend->get_graphics(), point_i32(maximum(0, xDest - m_pointAlphaBlend.x()), maximum(0, yDest - m_pointAlphaBlend.y())), size);

   imageWork.channel_multiply(::color::e_channel_alpha, imageWork4);


   keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


   return pdraw2d->imaging().true_blend(this, pointDest, size, imageWork.get_graphics(), pointSrc) != false;

   }



   return ::AlphaBlend(get_handle1(), xDest, yDest,
   nDestWidth, nDestHeight, GDI_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
   nSrcHeight, blend) != false;
   }*/

   bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dOpacity)
   {


      if(get_handle1() == nullptr)
         return false;


      if(m_pimageAlphaBlend->is_set())
      {

         ::rectangle_i32 rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::point_i32 pointSrc(xSrc, ySrc);

         ::point_i32 pointDest(xDest, yDest);

         ::size_i32 size(nDestWidth, nDestHeight);

         ::image_pointer pimage1 = create_image(size);

         if (!pimage1)
         {

            return false;

         }

         if (!pimage1->from(::point_i32(), pgraphicsSrc, pointSrc, size))
         {

            return false;

         }

         ::image_pointer pimage4 = create_image(size);

         if (!image4)
         {

            return false;

         }

         image4.fill(255, 0, 0, 0);

         image4.from(point_i32(maximum(0, m_pointAlphaBlend.x() - xDest), maximum(0, m_pointAlphaBlend.y() - yDest)),
                     m_pimageAlphaBlend->get_graphics(), point_i32(maximum(0, xDest - m_pointAlphaBlend.x()), maximum(0, yDest - m_pointAlphaBlend.y())), size);

         pimage1->channel_multiply(::color::e_channel_alpha, image4);


         __keep(m_pimageAlphaBlend->m_pimpl, nullptr);


         return BitBlt(pointDest.x(), pointDest.y(), size.cx(), size.cy(), pimage1->g(), pointSrc.x(), pointSrc.y(), SRCCOPY) != false;

      }
      if(dOpacity < 0.0)
         dOpacity = 0.0;
      else if(dOpacity > 1.0)
         dOpacity = 1.0;

      BLENDFUNCTION bf;
      bf.BlendOp     = AC_SRC_OVER;
      bf.BlendFlags  = 0;
      bf.SourceConstantAlpha = (BYTE) (dOpacity * 0xFF);
      bf.AlphaFormat = AC_SRC_ALPHA;


      return ::AlphaBlend(get_handle1(), xDest, yDest,
                          nDestWidth, nDestHeight, GDI_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
                          nSrcHeight, bf) != false;
   }


   bool graphics::TransparentBlt(int xDest, int yDest, int nDestWidth,
                                 int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth,
                                 int nSrcHeight, UINT crTransparent)
   {

      ASSERT(get_handle1() != nullptr);

      return ::TransparentBlt(get_handle1(), xDest, yDest,
                              nDestWidth, nDestHeight, GDI_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
                              nSrcHeight, crTransparent) != false;

   }


   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                               void * pMesh, ULONG nMeshElements, u32 dwMode)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GradientFill(get_handle1(), pVertices, nVertices,
                            pMesh, nMeshElements, dwMode) != false;

   }



   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   // Always Inline. Functions only in Win98/Win2K or later

   inline ::color::color graphics::GetDCBrushColor()
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetDCBrushColor(get_handle1());

   }


   inline ::color::color graphics::SetDCBrushColor(::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetDCBrushColor(get_handle1(), crColor);

   }



   inline ::color::color graphics::GetDCPenColor()
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetDCPenColor(get_handle1());

   }


   inline ::color::color graphics::SetDCPenColor(::color::color crColor)
   {

      ASSERT(get_handle1() != nullptr);

      return ::SetDCPenColor(get_handle1(), crColor);

   }



   inline bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != false;

   }


   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer)
   {

      ASSERT(get_handle1() != nullptr);

      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != false;

   }


   bool graphics::get_text_extent(size_f64 & size, const ::string & lpszString, strsize nCount, strsize iIndex)
   {

      ::size_i32 sz = get_text_extent(string(lpszString), iIndex);

      size.cx() = sz.cx();
      size.cy() = sz.cy();

      return true;

   }



   inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)
   {
      ENSURE(lpSize != nullptr);
      ASSERT(get_handle1() != nullptr);
      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize) != false;

   }


   inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize)
   {
      ENSURE(lpSize != nullptr);
      ASSERT(get_handle1() != nullptr);
      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, lpSize) != false;

   }









   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)

#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE lpSize)
   {

      int nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained ::collection::map mode, ::collection::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         DPtoLP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);

      }


      else
      {
         // ::collection::map against logical inch for non-constrained mapping modes
         int cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);

         }


         else
         {

            cxPerInch = 96;
            cyPerInch = 96;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
         lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);

      }


   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize)
   {

      int nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained ::collection::map mode, ::collection::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         LPtoDP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);

      }


      else
      {
         // ::collection::map against logical inch for non-constrained mapping modes
         int cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);

         }


         else
         {

            cxPerInch = 96;
            cyPerInch = 96;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
         lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);

      }


   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize)
   {

      LPtoDP(lpSize);
      DPtoHIMETRIC(lpSize);

   }



   void graphics::HIMETRICtoLP(LPSIZE lpSize)
   {

      HIMETRICtoDP(lpSize);
      DPtoLP(lpSize);

   }



   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush(::particle * pparticle)
   {
      /*      ::windows_definition::LockGlobals(CRIT_HALFTONEBRUSH);
      if (::windows_definition::HalftoneBrush == nullptr)
      {
      WORD grayPattern[8];
      for (int i = 0; i < 8; i++)
      grayPattern[i] = (WORD)(0x5555 << (i & 1));
      HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
      if (grayBitmap != nullptr)
      {
      ::windows_definition::HalftoneBrush = ::CreatePatternBrush(grayBitmap);
      ::DeleteObject(grayBitmap);

      }


      }
      if (!::windows_definition::WingdixTerm)
      ::windows_definition::WingdixTerm = (char)!atexit(&::windows_definition::WingdixTerm);
      ::windows_definition::UnlockGlobals(CRIT_HALFTONEBRUSH);

      return ::draw2d_gdi::brush::from_handle(papp, ::windows_definition::HalftoneBrush);
      */
      return nullptr;
   }



   //void graphics::DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_i32 & size,
   //                            const ::rectangle_i32 & rectangleLast, const ::size_i32 & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   // first, determine the update region and select it
   //   ::draw2d::region_pointer rgnNew(e_create);
   //   ::draw2d::region_pointer rgnOutside(e_create), rgnInside(e_create);
   //   rgnOutside->create_rect(&rectangle);
   //   const ::rectangle_i32 & rectangle = rectangle;
   //   rectangle.inflate(-size.cx(), -size.cy());
   //   rectangle.intersect(rectangle, &rectangle);
   //   rgnInside->create_rect(rectangle);
   //   rgnNew->create_rect_dim(0, 0, 0, 0);
   //   rgnNew->combine(rgnOutside, rgnInside, ::draw2d::region::combine_xor);

   //   ::draw2d::brush* pBrushOld = nullptr;
   //   if (pBrush == nullptr)
   //   {
   //      pBrush = graphics::GetHalftoneBrush(get_application());

   //   }



   //   ENSURE(pBrush);

   //   if (pBrushLast == nullptr)
   //   {
   //      pBrushLast = pBrush;
   //   }

   //   ::draw2d::region_pointer rgnLast(e_create), rgnUpdate(e_create);
   //   if (!IsRectEmpty(&lpRectLast))
   //   {
   //      // find difference between new region and old region
   //      rgnLast->create_rect_dim(0, 0, 0, 0);
   //      rgnOutside->create_rect(&lpRectLast);
   //      rectangle = lpRectLast;
   //      rectangle.inflate(-sizeLast.cx(), -sizeLast.cy());
   //      rectangle.intersect(rectangle, &lpRectLast);
   //      rgnInside->create_rect(rectangle);
   //      rgnLast->combine(rgnOutside, rgnInside, ::draw2d::region::combine_xor);

   //      // only diff them if brushes are the same
   //      if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //      {
   //         rgnUpdate->create_rect_dim(0, 0, 0, 0);
   //         rgnUpdate->combine(rgnLast, rgnNew, ::draw2d::region::combine_xor);

   //      }


   //   }
   //   if (pBrush->get_os_data() != pBrushLast->get_os_data() && !IsRectEmpty(&lpRectLast))
   //   {
   //      // brushes are different -- erase old region first
   //      SelectClipRgn(rgnLast);
   //      get_clip_box(&rectangle);
   //      pBrushOld = SelectObject(pBrushLast);
   //      PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
   //      SelectObject(pBrushOld);
   //      pBrushOld = nullptr;
   //   }

   //   // draw into the update/new region
   //   SelectClipRgn(rgnUpdate->get_os_data() != nullptr ? rgnUpdate : rgnNew);
   //   get_clip_box(&rectangle);
   //   pBrushOld = SelectObject(pBrush);
   //   PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

   //   // cleanup DC
   //   if (pBrushOld != nullptr)
   //      SelectObject(pBrushOld);
   //   SelectClipRgn(nullptr);

   //}


   image graphics::image_work(const ::size_i32 & size, bool bReset)
   {

      if (size.area() < 0)
      {

         return image();

      }

      image_descriptor d;

      d.m_etype = image_type_complex;
      d.m_color = 0;
      d.m_size = size;

      if (t_pimagemap == nullptr)
      {

         t_pimagemap = new image_descriptor_map(get_application());

      }

      ::image_pointer pimage = t_pimagemap->operator[](d);

      if(bReset)
      {

         pimage->fill(0, 0, 0, 0);

      }

      return pimage;

   }


   image graphics::fill_image_work(::color::color clr, const ::size_i32 & size, bool bReset)
   {

      image_descriptor d;

      d.m_etype = image_type_plain_color;

      d.m_color = clr;

      d.m_size = size;

      if (t_pimagemap == nullptr)
      {

         t_pimagemap = new image_descriptor_map(get_application());

      }

      ::image_pointer pimage = t_pimagemap->operator[](d);

      if(bReset)
      {

         pimage->fill(colorref_get_a_value(clr), colorref_get_r_value(clr) * colorref_get_a_value(clr) / 255, colorref_get_g_value(clr) * colorref_get_a_value(clr) / 255, colorref_get_b_value(clr) * colorref_get_a_value(clr) / 255);

      }

      return pimage;

   }


   void graphics::fill_rectangle(const ::rectangle_i32 & rectangle, ::color::color color32)
   {

      synchronous_lock ml(synchronization());

      if(m_pimage->is_null())
      {

         ::SetBkColor(get_handle1(), color32);

         ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);

      }
      else if(colorref_get_a_value(color32) == 255)
      {

         ::point_i32 point = GetViewportOrg();

         m_pimage->fill_rectangle(rectangle, argb(255, colorref_get_r_value(color32), colorref_get_g_value(color32), colorref_get_b_value(color32)));

      }
      else
      {

         int x = rectangle.left;

         int y = rectangle.top;

         int cx = ::width(rectangle);

         int cy = ::height(rectangle);

         ::image_pointer pimage = fill_image_work(color32, ::size_i32(rectangle), false);

         BLENDFUNCTION bf;
         bf.BlendOp     = AC_SRC_OVER;
         bf.BlendFlags  = 0;
         bf.SourceConstantAlpha = 0xFF;
         bf.AlphaFormat = AC_SRC_ALPHA;

         ::AlphaBlend(m_hdc, x, y, cx, cy, (HDC) pimage->g()->get_os_data(), 0, 0, cx, cy, bf);

      }

   }


   void graphics::draw_inset_3d_rectangle(const ::rectangle_i32 & rectangle, ::color::color crTopLeft, ::color::color crBottomRight, const ::e_border & eborder)
   {

      int x = rectangle.left;
      int y = rectangle.top;
      int cx = ::width(rectangle);
      int cy = ::height(rectangle);

      if (eborder & e_border_top)
      {

         fill_solid_rect_dim(x, y, cx - 1, 1, crTopLeft);

      }

      if (eborder & e_border_left)
      {

         fill_solid_rect_dim(x, y, 1, cy - 1, crTopLeft);

      }

      if (eborder & e_border_right)
      {

         fill_solid_rect_dim(rectangle.right, y, -1, cy, crBottomRight);

      }

      if (eborder & e_border_bottom)
      {

         fill_solid_rect_dim(x, rectangle.bottom, cx, -1, crBottomRight);

      }

   }


   void graphics::assert_ok() const
   {

      object::assert_ok();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << get_handle1();
      dumpcontext << "\nm_hAttribDC = " << get_handle2();
      dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";

   }


   bool graphics::attach_hdc(HDC hdc)
   {

      if (hdc == nullptr)
      {

         return false;

      }

      if(m_hdc != nullptr)
      {

         DeleteDC();

      }

      m_hdc = hdc;


      m_hbitmapOriginal    = (HBITMAP) ::GetCurrentObject(m_hdc, OBJ_BITMAP);
      m_hpenOriginal       = (HPEN)    ::GetCurrentObject(m_hdc, OBJ_PEN);
      m_hbrushOriginal     = (HBRUSH)  ::GetCurrentObject(m_hdc, OBJ_BRUSH );
      m_hfontOriginal      = (HFONT)   ::GetCurrentObject(m_hdc, OBJ_FONT);
      m_hrgnOriginal       = (HRGN)    ::GetCurrentObject(m_hdc, OBJ_REGION);


      return true;

   }


   HDC graphics::detach_hdc()
   {

      HDC hdc = get_handle1();

      m_hdc = nullptr;

      return hdc;

   }


   bool graphics::DeleteDC()
   {


      if (get_handle1() == nullptr)
         return false;

      return ::DeleteDC(detach_hdc()) != false;


   }




   int graphics::StartDoc(const ::string & lpszDocName)
   {

      DOCINFOW di;

      memory_set(&di, 0, sizeof(DOCINFOW));

      di.cbSize = sizeof(DOCINFOW);

      di.lpszDocName = wstring (lpszDocName);

      return StartDocW(&di);

   }



   int graphics::SaveDC()
   {

      int nRetVal = 0;

      if(get_handle2() != nullptr)
         nRetVal = ::SaveDC(get_handle2());

      if(get_handle1() != nullptr && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
         nRetVal = -1;   // -1 is the only valid restore value for complex DCs

      return nRetVal;

   }


   bool graphics::RestoreDC(int nSavedDC)
   {

      bool bRetVal = true;

      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != false;

      if(get_handle2() != nullptr)
         bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC)) != false;

      return bRetVal;

   }

   //::draw2d::object* graphics::SelectStockObject(int nIndex)
   //{

   //   HGDIOBJ hObject = ::GetStockObject(nIndex);

   //   HGDIOBJ hOldObj = nullptr;

   //   ASSERT(hObject != nullptr);

   //   if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //      hOldObj = ::SelectObject(get_handle1(), hObject);

   //   if(get_handle2() != nullptr)
   //      hOldObj = ::SelectObject(get_handle2(), hObject);

   //   return ::draw2d_gdi::object::from_handle(get_application(), hOldObj);

   //}



   ::draw2d::pen * graphics::SelectObject(::draw2d::pen * ppen)
   {

      if(get_handle1() == nullptr)
         return nullptr;

      if(ppen == nullptr)
         return nullptr;

      synchronous_lock ml(synchronization());

      SelectObject(ppen->get_os_data());

      on_select_object(ppen);

      m_ppen = ppen;

      return m_ppen;


   }



   ::draw2d::brush * graphics::SelectObject(::draw2d::brush * pbrush)
   {

      if(get_handle1() == nullptr)
         return nullptr;

      if(pbrush == nullptr)
         return nullptr;

      synchronous_lock ml(synchronization());

      SelectObject(pbrush->get_os_data());

      on_select_object(pbrush);

      m_pbrush = pbrush;

      return m_pbrush;

   }



   ::write_text::font * graphics::SelectObject(::write_text::font * pfont)
   {

      if(get_handle1() == nullptr)
         return nullptr;

      if(pfont == nullptr)
         return nullptr;

      synchronous_lock ml(synchronization());

      SelectObject(pfont->get_os_data());

      on_select_object(pfont);

      m_pfont = pfont;

      return m_pfont;

   }



   int graphics::SelectObject(::draw2d::region* pregion)
   {

      int nRetVal = GDI_ERROR;

      if(get_handle1() == nullptr)
         return nRetVal;

      if(pregion == nullptr)
         return nRetVal;

      synchronous_lock ml(synchronization());

      SelectObject(pregion->get_os_data());

      on_select_object(pregion);

      return nRetVal;

   }


   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {

      // return dynamic_cast < ::draw2d::palette * > (::draw2d_gdi::object::from_handle(get_application(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground))) != false;

      throw ::interface_only();

      return nullptr;

   }



   ::color::color graphics::SetBkColor(::color::color crColor)
   {
      ::color::color crRetVal = CLR_INVALID;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         crRetVal = ::SetBkColor(get_handle1(), crColor);
      if(get_handle2() != nullptr)
         crRetVal = ::SetBkColor(get_handle2(), crColor);
      return crRetVal;
   }

   int graphics::SetBkMode(int nBkMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetBkMode(get_handle1(), nBkMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetBkMode(get_handle2(), nBkMode);
      return nRetVal;
   }

   int graphics::SetPolyFillMode(int nPolyFillMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
      return nRetVal;
   }

   int graphics::SetROP2(int nDrawMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      return nRetVal;
   }

   int graphics::SetStretchBltMode(int nStretchMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;
   }

   ::color::color graphics::SetTextColor(::color::color crColor)
   {
      ::color::color crRetVal = CLR_INVALID;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         crRetVal = ::SetTextColor(get_handle1(), crColor);
      if(get_handle2() != nullptr)
         crRetVal = ::SetTextColor(get_handle2(), crColor);
      return crRetVal;
   }

   int graphics::SetGraphicsMode(int iMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
      {
         nRetVal = ::SetGraphicsMode(get_handle1(), iMode) != false;

      }


      if(get_handle2() != nullptr)
      {
         nRetVal = ::SetGraphicsMode(get_handle2(), iMode) != false;

      }


      return nRetVal;
   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {
      bool nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
      {
         nRetVal = ::SetWorldTransform(get_handle1(), pXform) != false;

      }


      if(get_handle2() != nullptr)
      {
         nRetVal = ::SetWorldTransform(get_handle2(), pXform) != false;

      }


      return nRetVal;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   {
      bool nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
      {
         nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != false;

      }


      if(get_handle2() != nullptr)
      {
         nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != false;

      }


      return nRetVal;
   }

   int graphics::SetMapMode(int nMapMode)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetMapMode(get_handle1(), nMapMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetMapMode(get_handle2(), nMapMode);
      return nRetVal;
   }

   point_i32 graphics::SetViewportOrg(int x, int y)
   {
      ::point_i32 point;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::SetViewportOrgEx(get_handle1(), x, y, &point);
      if(get_handle2() != nullptr)
         ::SetViewportOrgEx(get_handle2(), x, y, &point);
      return point;
   }

   point_i32 graphics::OffsetViewportOrg(int nWidth, int nHeight)
   {
      ::point_i32 point;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::OffsetViewportOrgEx(get_handle1(), nWidth, nHeight, &point);
      if(get_handle2() != nullptr)
         ::OffsetViewportOrgEx(get_handle2(), nWidth, nHeight, &point);
      return point;
   }

   size_i32 graphics::SetViewportExt(int x, int y)
   {
      size_i32 size(0, 0);
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::SetViewportExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != nullptr)
         ::SetViewportExtEx(get_handle2(), x, y, &size);
      return size;
   }

   size_i32 graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {
      size_i32 size(0, 0);
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::ScaleViewportExtEx(get_handle1(), xNum * 10.0, xDenom * 10.0, yNum * 10.0, yDenom * 10.0, &size);
      if(get_handle2() != nullptr)
         ::ScaleViewportExtEx(get_handle2(), xNum * 10.0, xDenom * 10.0, yNum * 10.0, yDenom * 10.0, &size);
      return size;
   }

   point_i32 graphics::SetWindowOrg(int x, int y)
   {
      ::point_i32 point;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::SetWindowOrgEx(get_handle1(), x, y, &point);
      if(get_handle2() != nullptr)
         ::SetWindowOrgEx(get_handle2(), x, y, &point);
      return point;
   }

   point_i32 graphics::offset_window_org(int nWidth, int nHeight)
   {
      ::point_i32 point;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
      if(get_handle2() != nullptr)
         ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
      return point;
   }

   size_i32 graphics::set_window_ext(int x, int y)
   {
      size_i32 size(0, 0);
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::SetWindowExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != nullptr)
         ::SetWindowExtEx(get_handle2(), x, y, &size);
      return size;
   }

   size_i32 graphics::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
   {
      size_i32 size(0, 0);
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
      if(get_handle2() != nullptr)
         ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
      return size;
   }

   
   int graphics::get_clip_box(RECT * prectangle)
   {
      
      return ::get_clip_box(get_handle1(), prectangle);

   }


   int graphics::SelectClipRgn(::draw2d::region* pRgn)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
      if(get_handle2() != nullptr)
         nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
      return nRetVal;
   }

   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != nullptr)
         nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
   }

   int graphics::ExcludeClipRect(const ::rectangle_i32 & rectangle)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), rectangle.left, rectangle.top,
                                     rectangle.right, rectangle.bottom);
      if(get_handle2() != nullptr)
         nRetVal = ::ExcludeClipRect(get_handle2(), rectangle.left, rectangle.top,
                                     rectangle.right, rectangle.bottom);
      return nRetVal;
   }

   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != nullptr)
         nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
   }

   int graphics::IntersectClipRect(const ::rectangle_i32 & rectangle)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
      if(get_handle2() != nullptr)
         nRetVal = ::IntersectClipRect(get_handle2(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
      return nRetVal;
   }

   int graphics::OffsetClipRgn(int x, int y)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
      if(get_handle2() != nullptr)
         nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
      return nRetVal;
   }


   int graphics::OffsetClipRgn(const ::size_i32 & size)
   {
      int nRetVal = ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), size.cx(), size.cy());
      if(get_handle2() != nullptr)
         nRetVal = ::OffsetClipRgn(get_handle2(), size.cx(), size.cy());
      return nRetVal;
   }


   bool graphics::move_to(const ::point_i32 & pointParam)
   {

      ::point_i32 point(pointParam);

      if (get_handle1() != nullptr && get_handle1() != get_handle2())
      {

         ::MoveToEx(get_handle1(), point.x(), point.y(), &point);

      }

      if (get_handle2() != nullptr)
      {

         ::MoveToEx(get_handle2(), point.x(), point.y(), &point);

      }

      return true;

   }


   bool graphics::line_to(const ::point_i32 & point)
   {

      ::rectangle_i32 rectangle;

      rectangle.top_left() = current_position();

      rectangle.bottom_right() = point;

      ::rectangle_i32 rectangleBound(rectangle);

      __sort(rectangleBound.left, rectangleBound.right);

      __sort(rectangleBound.top, rectangleBound.bottom);

      internal_stroke_path(&::draw2d_gdi::graphics::internal_set_path_line, &rectangle, rectangleBound, m_ppen);

      ::MoveToEx(m_hdc, rectangle.right, rectangle.bottom, nullptr);

      return true;

   }



   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UINT nRetVal = GDI_ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         ::SetTextAlign(get_handle1(), nFlags);
      if(get_handle2() != nullptr)
         nRetVal = ::SetTextAlign(get_handle2(), nFlags);
      return nRetVal;
   }

   int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   {
      int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
      if(get_handle2() != nullptr)
         nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
      return nRetVal;
   }

   int graphics::SetTextCharacterExtra(int nCharExtra)
   {
      ASSERT(get_handle1() != nullptr);
      int nRetVal = 0x8000000;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
      if(get_handle2() != nullptr)
         nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
      return nRetVal;
   }

   u32 graphics::SetMapperFlags(u32 dwFlag)
   {
      ASSERT(get_handle1() != nullptr);
      u32 dwRetVal = GDI_ERROR;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
      if(get_handle2() != nullptr)
         dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
      return dwRetVal;
   }

   typedef u32 (CALLBACK* WINDOWS_DEFINITION_GDIGETLAYOUTPROC)(HDC);
   typedef u32 (CALLBACK* WINDOWS_DEFINITION_GDISETLAYOUTPROC)(HDC, u32);

   
   u32 graphics::GetLayout()
   {
      
      return ::GetLayout(get_handle1());

   }


   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      
      return ::SetLayout(get_handle1(), dwSetLayout);

   }

   /*
   void window::ScreenToClient(RECT * prectangle)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::ScreenToClient(get_handle1(), (LPPOINT)rectangle_i32);
   ::ScreenToClient(get_handle1(), ((LPPOINT)rectangle_i32)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(rectangle) != false;

   }



   void window::ClientToScreen(RECT * prectangle)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::ClientToScreen(get_handle1(), (LPPOINT)rectangle_i32);
   ::ClientToScreen(get_handle1(), ((LPPOINT)rectangle_i32)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(rectangle) != false;

   }

   */


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      ASSERT(get_handle1() != nullptr);

      bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;

      if (get_handle1() != get_handle2())
      {

         ::point_i32 point;

         VERIFY(::GetCurrentPositionEx(get_handle1(), &point));

         VERIFY(::MoveToEx(get_handle2(), point.x(), point.y(), nullptr));

      }

      return bResult;

   }


   int graphics::SetArcDirection(int nArcDirection)
   {
      ASSERT(get_handle1() != nullptr);
      int nResult = 0;
      if (get_handle1() != get_handle2())
         nResult = ::SetArcDirection(get_handle1(), nArcDirection);
      if (get_handle2() != nullptr)
         nResult = ::SetArcDirection(get_handle2(), nArcDirection);
      return nResult;
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, (int) nCount) != false;

      if (get_handle1() != get_handle2())
      {

         ::point_i32 point;

         VERIFY(::GetCurrentPositionEx(get_handle1(), &point));

         VERIFY(::MoveToEx(get_handle2(), point.x(), point.y(), nullptr));


      }


      return bResult;

   }


   bool graphics::polyline_to(const POINT* lpPoints, count nCount)
   {

      ASSERT(get_handle1() != nullptr);

      bool bResult = ::polyline_to(get_handle1(), lpPoints, (int) nCount) != false;

      if (get_handle1() != get_handle2())
      {

         ::point_i32 point;

         VERIFY(::GetCurrentPositionEx(get_handle1(), &point));

         VERIFY(::MoveToEx(get_handle2(), point.x(), point.y(), nullptr));

      }

      return bResult;

   }

   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      ASSERT(get_handle1() != nullptr);
      bool bResult = false;
      if (get_handle1() != get_handle2())
         bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != false;
      if (get_handle2() != nullptr)
         bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != false;
      return bResult;
   }

   bool graphics::poly_bezier_to(const POINT* lpPoints, strsize nCount)
   {

      ASSERT(get_handle1() != nullptr);

      bool bResult = ::poly_bezier_to(get_handle1(), lpPoints, (int) nCount) != false;

      if (get_handle1() != get_handle2())
      {
         ::point_i32 point;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
         VERIFY(::MoveToEx(get_handle2(), point.x(), point.y(), nullptr));

      }

      return bResult;

   }


   bool graphics::SelectClipPath(int nMode)
   {

      ASSERT(get_handle1() != nullptr);

      // output DC always holds the current path
      if (!::SelectClipPath(get_handle1(), nMode))
         return false;

      // transfer clipping region into the attribute DC
      bool bResult = true;
      if (get_handle1() != get_handle2())
      {
         HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
         if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
         {
            TRACE("Error: unable to transfer clip region in graphics::SelectClipPath!\n");
            bResult = false;
         }
         ::DeleteObject(hRgn);

      }


      return bResult;
   }

   int graphics::SelectClipRgn(::draw2d::region* pRgn, int nMode)
   {
      ASSERT(get_handle1() != nullptr);
      int nRetVal = ERROR;
      if (get_handle1() != get_handle2())
         nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
      if (get_handle2() != nullptr)
         nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
      return nRetVal;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   int CALLBACK ::windows_definition::EnumMetaFileProc(HDC hDC,
                                    HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles, LPARAM lParam)
   {
      ::draw2d::graphics_pointer & pgraphics = (::draw2d::graphics *)lParam;
      ASSERT_VALID(pgraphics);

      switch (pMetaRec->rdFunction)
      {
      // these records have effects different for each graphics derived class
      case META_SETMAPMODE:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetMapMode((int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWEXT:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->set_window_ext(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWORG:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetWindowOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTEXT:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetViewportExt(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTORG:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetViewportOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SCALEWINDOWEXT:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->scale_window_ext(
         (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SCALEVIEWPORTEXT:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->ScaleViewportExt(
         (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_OFFSETVIEWPORTORG:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->OffsetViewportOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SAVEDC:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SaveDC();
         break;
      case META_RESTOREDC:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->RestoreDC((int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETBKCOLOR:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetBkColor(*(UNALIGNED ::color::color*)&pMetaRec->rdParm[0]);
         break;
      case META_SETTEXTCOLOR:
         (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SetTextColor(*(UNALIGNED ::color::color*)&pMetaRec->rdParm[0]);
         break;

      // need to watch out for SelectObject(HFONT), for custom font mapping
      case META_SELECTOBJECT:
      {
         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
         UINT nObjType = GetObjectType(hObject);
         if (nObjType == 0)
         {
            // object type is unknown, determine if it is a font
            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
            HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1(), hStockFont);
            HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1(), hObject);
            if (hObjOld == hStockFont)
            {
               // got the stock object back, so must be selecting a font
               //(dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SelectObject(::draw2d_gdi::font::from_handle_dup(pgraphics->get_application(), (HFONT)hObject));
               break;  // don't play the default record
            }
            else
            {
               // didn't get the stock object back, so restore everything
               ::SelectObject((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1(), hFontOld);
               ::SelectObject((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle1(), hObjOld);

            }


            // and fall through to PlayMetaFileRecord...
         }
         else if (nObjType == OBJ_FONT)
         {
            // play back as graphics::SelectObject(::write_text::font*)
            //(dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->SelectObject(::draw2d_gdi::font::from_handle_dup(pgraphics->get_application(), (HFONT)hObject));
            break;  // don't play the default record
         }
      }
      // fall through...

      default:
         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
         break;
      }

      return 1;
   }

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      if (::GetDeviceCaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
      {
         // playing metafile in metafile, just use aura windows API
         return ::PlayMetaFile(get_handle1(), hMF) != false;

      }



      // for special playback, lParam == pgraphics
      return ::EnumMetaFile(get_handle1(), hMF, ::windows_definition::EnumMetaFileProc, (LPARAM)this) != false;

   }



   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize)
   {

      size_i32 sizeWinExt = GetWindowExt();
      size_i32 sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx()), abs(sizeWinExt.cx()));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy()), abs(sizeWinExt.cy()));

   }



   void graphics::DPtoLP(LPSIZE lpSize)
   {

      size_i32 sizeWinExt = GetWindowExt();
      size_i32 sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx()), abs(sizeVpExt.cx()));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy()), abs(sizeVpExt.cy()));

   }








   size_f64 graphics::get_text_extent(const ::string & lpszString, strsize nCount)
   {

      if(get_handle2() == nullptr)
         return size_i32(0, 0);

      ::size_i32 size;

      string str(lpszString, nCount);

      wstring wstr = utf8_to_unicode(str);

      if(!::GetTextExtentPoint32W(get_handle2(), wstr, (int)wstr.get_length(), &size))
      {

         return ::size_i32(0, 0);

      }


      return size;
   }


   size_f64 graphics::get_text_extent(const ::string & str)
   {

      if (get_handle2() == nullptr)
      {

         return nullptr;

      }

      ((graphics *) this)->select_font();

      ::size_i32 size;

      wstring wstr = utf8_to_unicode(str);

      if(!::GetTextExtentPoint32W(get_handle2(), wstr, (int)wstr.get_length(), &size))
      {
         
         return nullptr;

      }

      return size_f64(size);

   }


   size_i32 graphics::GetOutputTextExtent(const ::string & lpszString,strsize nCount)
   {
      ASSERT(get_handle1() != nullptr);
      ::size_i32 size;
      string str(lpszString, nCount);
      wstring wstr = utf8_to_unicode(str);
      VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int)wstr.get_length(), &size));
      return size;
   }
   size_i32 graphics::GetOutputTextExtent(const ::string & str)
   {
      ASSERT(get_handle1() != nullptr);
      ::size_i32 size;
      wstring wstr = utf8_to_unicode(str);
      VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int)wstr.get_length(), &size));
      return size;
   }

   bool graphics::select_path(::draw2d::path * ppath)
   {

      m_sppath = ppath;

      return m_sppath.is_set();

   }


   bool graphics::set(::draw2d::path * ppath)
   {

      if (ppath == nullptr)
      {

         return false;

      }

      begin_path();

      for(int i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         set(ppath->m_elementa(i));

      }

      end_path();

      return true;

   }


   bool graphics::set(::draw2d::path::matter & e)
   {

      switch(e.m_etype)
      {
      case ::draw2d::path::matter::type_arc:
         set(e.u.m_arc);
         break;
      case ::draw2d::path::matter::type_line:
         set(e.u.m_line);
         break;
      case ::draw2d::path::matter::type_move:
         set(e.u.m_move);
         break;
      case ::draw2d::path::matter::type_string:
         set(e.m_stringpath);
         break;
      case ::draw2d::path::matter::type_end:
      {

         if(e.u.m_end.m_bClose)
         {

            close_figure();

         }

      }
      break;
      default:
         throw "unexpected simple os graphics matter type";
      }

      return false;


   }


   bool graphics::set(::draw2d::path::string_path  & path)
   {

      wstring wstr(path.m_strText);

      ::SelectObject(m_hdc,path.m_pfont->get_os_data());

      ::SetBkMode(m_hdc, TRANSPARENT);

      if (!TextOutW(m_hdc, (int)path.m_x, (int)path.m_y, wstr, (int)wstr.length()))
      {

         return false;

      }

      return true;

   }


   bool graphics::set(::draw2d::path::line & line)
   {

      return ::LineTo(m_hdc, (i32) line.m_x, (i32) line.m_y) != false;

   }


   bool graphics::set(::draw2d::path::arc & arc)
   {

      ::rectangle_i32 rectangle;

      rectangle.left         = (LONG) (arc.m_xCenter - arc.m_dRadiusX);
      rectangle.right        = (LONG) (arc.m_xCenter + arc.m_dRadiusX);
      rectangle.top          = (LONG) (arc.m_yCenter - arc.m_dRadiusY);
      rectangle.bottom       = (LONG) (arc.m_yCenter + arc.m_dRadiusY);

      ::point_i32 point1;

      ::point_i32 point2;

      double e = arc.m_dRadiusY / arc.m_dRadiusX;

      double f1 = arc.m_dAngle1;

      double f2 = arc.m_dAngle2;

      point1.x()          = (LONG) (arc.m_xCenter + arc.m_dRadiusX * cos(f1));
      point1.y()          = (LONG) (arc.m_yCenter - arc.m_dRadiusY * sin(f1));
      point2.x()          = (LONG) (arc.m_xCenter + arc.m_dRadiusX * cos(f2));
      point2.y()          = (LONG) (arc.m_yCenter - arc.m_dRadiusY * sin(f2));

      return ::ArcTo(m_hdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, point1.x(), point1.y(), point2.x(), point2.y()) != false;

   }

   bool graphics::set(::draw2d::path::move & move)
   {

      ::MoveToEx(m_hdc, (i32) move.m_x, (i32) move.m_y, nullptr);

      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      if(!select_path(ppath))
         return false;

      return stroke_path();

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if(!select_path(ppath))
         return false;

      return fill_path();

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      if(!select_path(ppath))
         return false;

      return stroke_path(ppen);

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      if(!select_path(ppath))
         return false;

      return fill_path(pbrush);

   }


   void graphics::select_pen()
   {

      if(m_ppen.is_set() && m_ppen->get_os_data() != nullptr)
      {

         if(m_ppen->get_os_data() != GetCurrentObject(m_hdc, OBJ_PEN))
         {

            SelectObject(m_ppen);

         }

      }
      else
      {

         select_null_pen();

      }

   }

   void graphics::select_brush()
   {

      if(m_pbrush.is_set() && m_pbrush->get_os_data() != nullptr)
      {

         if(m_pbrush->get_os_data() != GetCurrentObject(m_hdc, OBJ_BRUSH))
         {

            SelectObject(m_pbrush);

         }

      }
      else
      {

         ::SelectObject(m_hdc, ::GetStockObject(NULL_BRUSH));

      }

   }


   void graphics::select_font()
   {

      if(m_pfont.is_set() && m_pfont->get_os_data() != nullptr)
      {

         if(m_pfont->get_os_data() != GetCurrentObject(m_hdc, OBJ_FONT))
         {

            SelectObject(m_pfont);

         }

      }

   }


   void graphics::select_null_pen()
   {

      ::SelectObject(m_hdc, ::GetStockObject(NULL_PEN));

   }

   void graphics::select_null_brush()
   {

      ::SelectObject(m_hdc, ::GetStockObject(NULL_BRUSH));

   }

   bool graphics::SelectFont(::write_text::font * pfont)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      return SelectObject(pfont) != nullptr;

   }

   bool graphics::flush()
   {

      return ::GdiFlush() != false;

   }

} // namespace draw2d_gdi





