#pragma once

namespace draw2d_gdi
{

   class region :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::region
   {
   public:


      region(::layered * pobjectContext);
      virtual ~region();


      operator HRGN() const;


      bool create_rect(int x1, int y1, int x2, int y2);
      bool create_rect(const ::rectangle_i32 & rectangle);
      bool create_oval(int x1, int y1, int x2, int y2);
      bool create_oval(const ::rectangle_i32 & rectangle);
      bool create_polygon(LPPOINT lpPoints, i32 nCount, ::draw2d::e_fill_mode efillmode);
      bool create_poly_polygon(LPPOINT lpPoints, LPINT lpPolyCounts, i32 nCount, ::draw2d::e_fill_mode efillmode);
      bool CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
      bool CreateFromPath(::draw2d::graphics_pointer & pgraphics);
      bool CreateFromData(const XFORM* lpXForm, int nCount,
                          const RGNDATA* pRgnData);

      // Operations
      void SetRectRgn(int x1, int y1, int x2, int y2);
      void SetRectRgn(const ::rectangle_i32 & rectangle);
      int CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode);
      int CopyRgn(const ::draw2d::region* pRgnSrc);
      bool EqualRgn(const ::draw2d::region* pRgn) const;
      int OffsetRgn(int x, int y);
      int OffsetRgn(const ::point_i32 & point);
      int GetRgnBox(RECT * prectangle) const;
      bool contains(int x, int y) const;
      bool contains(const ::point_i32 & point) const;
      bool RectInRegion(const ::rectangle_i32 & rectangle) const;
      int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;


      virtual bool create();

      virtual bool destroy();


   };


} // namespace draw2d_gdi




