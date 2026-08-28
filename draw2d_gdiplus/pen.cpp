#include "platform.h"
#include "pen.h"
#include "brush.h"


//#undef ___new


namespace draw2d_gdiplus
{


   pen::pen()
   {

      //m_egdiplusalign = (Gdiplus::PenAlignment) -1;
      m_pgdipluspen = nullptr;

   }


   pen::~pen()
   {
     
      destroy();

   }



//#ifdef DEBUG
//
//   void pen::dump(dump_context & dumpcontext) const
//   {
//      ::draw2d::object::dump(dumpcontext);
//
//      /*      if (get_handle() == nullptr)
//               return;
//
//            if (!::windows_definition::Data.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
//            {
//               // not a valid object
//               dumpcontext << "has ILLEGAL HPEN!";
//               return;
//            }
//
//            LOGPEN i32_point;
//
//            VERIFY(GetObject(sizeof(point), &lp));
//
//            dumpcontext << "lgpn.lopnStyle = " << point.lopnStyle;
//
//            dumpcontext << "\nlgpn.lopnWidth.x (width) = " << point.lopnWidth.x;
//
//            dumpcontext << "\nlgpn.lopnColor = " << (void *)(uptr)point.lopnColor;
//
//
//            dumpcontext << "\n";*/
//   }
//
//#endif



   // IMPLEMENT_DYNAMIC(resource_exception, ::exception::base)
   //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

   // IMPLEMENT_DYNAMIC(user_exception, ::exception::base)
   //user_exception _simpleUserException(false, __IDS_USER_EXCEPTION);

   // IMPLEMENT_DYNCREATE(::draw2d::graphics_pointer, object)
   // IMPLEMENT_DYNAMIC(CClientDC, ::draw2d::graphics_pointer)
   // IMPLEMENT_DYNAMIC(CWindowDC, ::draw2d::graphics_pointer)
   // IMPLEMENT_DYNAMIC(CPaintDC, ::draw2d::graphics_pointer)
   // IMPLEMENT_DYNCREATE(::draw2d::object, object)

   // IMPLEMENT_DYNAMIC(pen, ::draw2d::object)
   // IMPLEMENT_DYNAMIC(::draw2d::brush, ::draw2d::object)
   // IMPLEMENT_DYNAMIC(::write_text::font, ::draw2d::object)
   // IMPLEMENT_DYNAMIC(::draw2d::bitmap, ::draw2d::object)
   // IMPLEMENT_DYNAMIC(::draw2d::palette, ::draw2d::object)
   // IMPLEMENT_DYNAMIC(::draw2d::region, ::draw2d::object)

   /////////////////////////////////////////////////////////////////////////////
   // Standard exception processing


   /*void __get_gray_bitmap(::aura::application * papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, ::color::color crBackground)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      ::color::color color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->create_compatible_graphics(nullptr) &&
         graphicsMask->create_compatible_graphics(nullptr))
      {
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm);
   //         pDest->delete_object();
         if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, nullptr) &&
            bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
         {
            pOldMem = graphicsMem->set(const_cast<::draw2d::bitmap *>(&rSrc));
            pOldMask = graphicsMask->set(bmpMask);

            ASSERT(pOldMem && pOldMask);
            if(!pOldMem || !pOldMask)
               return;

            // Make the upper left corner pixel the "transparent" pixel
            color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
            // Make white pixels transparent too
            graphicsMem->SetBkColor(rgb(255, 255, 255));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

            if(graphicsMem->set(pDest))
            {
               graphicsMem->fill_rectangle(0, 0, bm.bmWidth, bm.bmHeight, crBackground);

               graphicsMem->SetBkColor(rgb(255, 255, 255));

               spbr = graphicsMem->set(pbrushHighLight);
               graphicsMem->BitBlt(1, 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->set(pbrushShadow);
               graphicsMem->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->set(spbr);

               graphicsMem->SetBkColor(color32);
            }
            graphicsMask->set(pOldMask);
            graphicsMem->set(pOldMem);
         }
      }
   }

   void __draw_gray_bitmap(::aura::application * papp, ::draw2d::graphics * pdraw2dgraphics, ::i32 x, ::i32 y, const ::draw2d::bitmap &rSrc, ::color::color crBackground)
   {
      ASSERT(pdraw2dgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pdraw2dgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      ::color::color color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->create_compatible_graphics(pdraw2dgraphics) &&
         graphicsMask->create_compatible_graphics(pdraw2dgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm) &&
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
      {
         pOldMem = graphicsMem->set(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->set(bmpMask);

         ASSERT(pOldMem && pOldMask);
         if(!pOldMem || !pOldMask)
            return;

         color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
         graphicsMem->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

         pdraw2dgraphics->fill_rectangle(x, y, bm.bmWidth, bm.bmHeight, crBackground);

         pdraw2dgraphics->SetBkColor(rgb(255, 255, 255));

         spbr = pdraw2dgraphics->set(pbrushHighLight);
         pdraw2dgraphics->BitBlt(x + 1, y + 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pdraw2dgraphics->set(pbrushShadow);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pdraw2dgraphics->set(spbr);

         pdraw2dgraphics->SetBkColor(color32);
         graphicsMask->set(pOldMask);
      }
   }

   void __get_dithered_bitmap(::aura::application * papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, const ::color::color & color1, const ::color::color & color2)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask, graphicsDest;
      ::color::color color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->create_compatible_graphics(nullptr) &&
         graphicsMask->create_compatible_graphics(nullptr) &&
         graphicsDest->create_compatible_graphics(nullptr))
      {
         if(const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm))
         {
            //pDest->delete_object();
            if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, nullptr))
            {
               // create checker brush
               bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
               pbrushChecker.CreatePatternBrush(bmpMask);
               //bmpMask->delete_object();

               // Mask
               bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

               pOldSrc = graphicsSrc->set(const_cast<::draw2d::bitmap *>(&rSrc));
               pOldMask = graphicsMask->set(bmpMask);

               ASSERT(pOldSrc && pOldMask);
               if(!pOldSrc || !pOldMask)
                  return;

               // Make the upper left corner pixel of the source a "transparent" color
               color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
               // Make white pixels of the source "transparent" too
               graphicsSrc->SetBkColor(rgb(255, 255, 255));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
               graphicsSrc->SetBkColor(color32);

               // Checker the background with white and crBackground
               pDest = graphicsDest->set(pDest);
               ASSERT(pDest);
               if(pDest)
               {
                  color1 = graphicsDest->SetTextColor(color1);
                  color2 = graphicsDest->SetBkColor(color2);
                  graphicsDest->fill_rectangle(i32_rectangle(0, 0, bm.bmWidth, bm.bmHeight), &pbrushChecker);
                  graphicsDest->SetTextColor(color1);
                  graphicsDest->SetBkColor(color2);

                  // Blt it
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
               }
               graphicsDest->set(pDest);
               graphicsMask->set(pOldMask);
               graphicsSrc->set(pOldSrc);
            }
         }
      }
   }

   void __draw_dithered_bitmap(::aura::application * papp, ::draw2d::graphics * pdraw2dgraphics, ::i32 x, ::i32 y, const ::draw2d::bitmap &rSrc, const ::color::color & color1, const ::color::color & color2)
   {
      ASSERT(pdraw2dgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pdraw2dgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask;
      ::color::color color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->create_compatible_graphics(pdraw2dgraphics) &&
         graphicsMask->create_compatible_graphics(pdraw2dgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm))
      {
         // create checker brush
         bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
         pbrushChecker.CreatePatternBrush(bmpMask);
         //bmpMask->delete_object();

         // Mask
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

         pOldSrc = graphicsSrc->set(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->set(bmpMask);

         ASSERT(pOldSrc && pOldMask);
         if(!pOldSrc || !pOldMask)
            return;

         // Make the upper left corner pixel of the source a "transparent" color
         color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
         // Make white pixels of the source "transparent" too
         graphicsSrc->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
         graphicsSrc->SetBkColor(color32);

         // Checker the background with white and crBackground
         color1 = pdraw2dgraphics->SetTextColor(color1);
         color2 = pdraw2dgraphics->SetBkColor(color2);
         pdraw2dgraphics->fill_rectangle(i32_rectangle(x, y, x + bm.bmWidth, y + bm.bmHeight), &pbrushChecker);
         pdraw2dgraphics->SetTextColor(color1);
         pdraw2dgraphics->SetBkColor(color2);

         // Blt it
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);

         graphicsMask->set(pOldMask);
         graphicsSrc->set(pOldSrc);
      }
   }

   */


   void pen::update(::draw2d::graphics * pdraw2dgraphics)
   {

      if (m_epen == ::draw2d::e_pen_brush)
      {

         ::cast <::draw2d_gdiplus::brush> pdraw2dbrush = m_pdraw2dbrush;

         m_pgdipluspen = ::as_pointer(new Gdiplus::Pen(pdraw2dbrush->m_pgdiplusbrush, (Gdiplus::REAL) m_dWidth));

      }
      else
      {

         m_pgdipluspen = ::as_pointer(new Gdiplus::Pen(gdiplus_color(m_color), (Gdiplus::REAL) m_dWidth));

      }

      switch(m_elinejoin)
      {
      case ::draw2d::e_line_join_miter:
         m_pgdipluspen->SetLineJoin(Gdiplus::LineJoinMiter);
         break;
      case ::draw2d::e_line_join_bevel:
         m_pgdipluspen->SetLineJoin(Gdiplus::LineJoinBevel);
         break;
      case ::draw2d::e_line_join_round:
         m_pgdipluspen->SetLineJoin(Gdiplus::LineJoinRound);
         break;
      case ::draw2d::e_line_join_miter_clipped:
         m_pgdipluspen->SetLineJoin(Gdiplus::LineJoinMiterClipped);
         break;
      }

      switch(m_elinecapBeg)
      {
      case ::draw2d::e_line_cap_flat:
         m_pgdipluspen->SetStartCap(Gdiplus::LineCapFlat);
         break;
      case ::draw2d::e_line_cap_round:
         m_pgdipluspen->SetStartCap(Gdiplus::LineCapRound);
         break;
      case ::draw2d::e_line_cap_square:
         m_pgdipluspen->SetStartCap(Gdiplus::LineCapSquare);
         break;
      }

      switch(m_elinecapEnd)
      {
      case ::draw2d::e_line_cap_flat:
         m_pgdipluspen->SetEndCap(Gdiplus::LineCapFlat);
         break;
      case ::draw2d::e_line_cap_round:
         m_pgdipluspen->SetEndCap(Gdiplus::LineCapRound);
         break;
      case ::draw2d::e_line_cap_square:
         m_pgdipluspen->SetEndCap(Gdiplus::LineCapSquare);
         break;
      }

      if(m_epen == ::draw2d::e_pen_dot)
      {

         Gdiplus::REAL dashVals[4];

         dashVals[0] = 1;
         dashVals[1] = 2;

         // Create a Pen object.

         // Set the dash pattern for the custom dashed line.
         m_pgdipluspen->SetDashPattern(dashVals,2);

      }
      else if (m_epen == ::draw2d::e_pen_dash)
      {

         Gdiplus::REAL dashVals[4];

         dashVals[0] = 10;
         dashVals[1] = 10;

         // Create a Pen object.

         // Set the dash pattern for the custom dashed line.
         m_pgdipluspen->SetDashPattern(dashVals, 2);
         //m_pgdipluspen->SetDashStyle(Gdiplus::DashStyleDash
         //                                 );

      }

      if (m_epenalign == ::draw2d::e_pen_align_inset)
      {

         m_pgdipluspen->SetAlignment(Gdiplus::PenAlignmentInset);

      }
      else if (m_epenalign == ::draw2d::e_pen_align_center)
      {

         m_pgdipluspen->SetAlignment(Gdiplus::PenAlignmentCenter);

      }

      //m_osdata[0] = m_pgdipluspen;

      //return ::is_set(m_pgdipluspen);

   }


   void pen::clear_node_data()
   {

      m_pgdipluspen.destroy();

   }


} // namespace draw2d_gdiplus
