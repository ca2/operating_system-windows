#pragma once

namespace draw2d_gdi
{

   class region :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::region
   {
   public:


      region(::particle * pparticle);
      virtual ~region();


      operator HRGN() const;


      bool create_rect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      bool create_rect(const ::i32_rectangle & rectangle);
      bool create_oval(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      bool create_oval(const ::i32_rectangle & rectangle);
      bool create_polygon(LPPOINT lpPoints, ::i32 nCount, ::draw2d::e_fill_mode efillmode);
      bool create_poly_polygon(LPPOINT lpPoints, LPINT lpPolyCounts, ::i32 nCount, ::draw2d::e_fill_mode efillmode);
      bool CreateRoundRectRgn(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3);
      bool CreateFromPath(::draw2d::graphics_pointer & pgraphics);
      bool CreateFromData(const XFORM* lpXForm, ::i32 nCount,
                          const RGNDATA* pRgnData);

      
      void SetRectRgn(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      void SetRectRgn(const ::i32_rectangle & rectangle);
      ::i32 CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, ::i32 nCombineMode);
      ::i32 CopyRgn(const ::draw2d::region* pRgnSrc);
      bool EqualRgn(const ::draw2d::region* pRgn) const;
      ::i32 OffsetRgn(::i32 x, ::i32 y);
      ::i32 OffsetRgn(const ::i32_point & point);
      ::i32 GetRgnBox(RECT * prectangle) const;
      bool contains(::i32 x, ::i32 y) const;
      bool contains(const ::i32_point & point) const;
      bool RectInRegion(const ::i32_rectangle & rectangle) const;
      ::i32 GetRegionData(LPRGNDATA lpRgnData, ::i32 nCount) const;


      virtual bool create();

      virtual bool destroy();


   };


} // namespace draw2d_gdi




