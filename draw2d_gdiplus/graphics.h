#pragma once


#include "aura/graphics/draw2d/graphics.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS graphics :
      virtual public ::draw2d::graphics
   {
   public:


      //__creatable_from_base(graphics, ::draw2d::graphics);


      //::Gdiplus::Matrix             m_matrix;
      ::Gdiplus::Graphics *         m_pgraphics;
      ::Gdiplus::GraphicsPath *     m_ppath;
      ::Gdiplus::GraphicsPath *     m_ppathPaint;
      HDC                           m_hdc;
      HDC                           m_hdcAttach;
      HDC                           m_hdcGraphics;


      graphics();
      ~graphics() override;


      virtual void close_graphics();

      Gdiplus::Graphics * g()
      {
         //if(m_pgraphics == nullptr)
         //{
         //   m_pgraphics = ::Gdiplus::Graphics::FromHDC(get_handle1());
         //}
         return m_pgraphics;
      }

//      ::user::interaction_impl * GetWindow() override;

      virtual void attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      virtual void * detach() override;

      //void attach_hdc(HDC hdc) override;   // attach/detach affects only the Output DC
      //virtual HDC detach_hdc() override;
      //void AttachPrinter(HDC hdc) override;
      //virtual HDC DetachPrinter() override;


      //bool IsPrinting() override;            // true if being used for printing


      // for bidi and mirrored localization
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;


      virtual void set(::draw2d::bitmap* pbitmap) override;

      HDC get_hdc();
      void release_hdc(HDC hdc);


      virtual double get_dpix() override;
      virtual double get_dpiy() override;

      // Constructors
      //bool CreateDC(const ::string & pszDriverName, const ::string & pszDeviceName,

      //              const scoped_string & strOutput, const void * lpInitData) override;

      //bool CreateIC(const ::string & pszDriverName, const ::string & pszDeviceName,

      //              const scoped_string & strOutput, const void * lpInitData) override;

      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      void DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual void RestoreDC(i32 nSavedDC) override;
      i32 GetDeviceCaps(i32 nIndex) override;
      virtual ::u32 SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::rectangle_f64 * rectdBounds, ::u32 flags);

      //bool ResetDC(const DEVMODE* pDevMode) override;


      // Drawing-Tool Functions
      point_f64 GetBrushOrg() override;
      point_f64 SetBrushOrg(double x, double y) override;
      point_f64 SetBrushOrg(const ::point_f64 & point) override;
      //i32 EnumObjects(i32 nObjectType, i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData) override;





      //::color::color GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      //i32 GetPolyFillMode() override;
      //i32 GetROP2() override;
      //i32 GetStretchBltMode() override;

      void _get(::draw2d::matrix & matrix) override;
      void _set(const ::draw2d::matrix & matrix) override;
      //bool append(const ::draw2d::matrix & matrix) override;
      //bool prepend(const ::draw2d::matrix & matrix) override;

      //i32 SetPolyFillMode(i32 nPolyFillMode) override;
      //i32 SetROP2(i32 nDrawMode) override;
      //bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;

      //bool GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust) override;

      //bool SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust) override;


//#if (_WIN32_WINNT >= 0x0500)
//
//      ::color::color GetDCBrushColor() override;
//      ::color::color SetDCBrushColor(const ::color::color & color) override;
//
//      ::color::color GetDCPenColor() override;
//      ::color::color SetDCPenColor(const ::color::color & color) override;
//
//#endif

      // Graphics mode
      //i32 SetGraphicsMode(i32 iMode) override;
      //i32 GetGraphicsMode() override;

      // World transform
      //bool SetWorldTransform(const XFORM* pXform) override;
      //bool ModifyWorldTransform(const XFORM* pXform,u32 iMode) override;
      //bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      //virtual i32 GetMapMode() override;
      //virtual point_i32 GetViewportOrg() override;
      //virtual i32 SetMapMode(i32 nMapMode) override;
      // Viewport Origin
      //virtual point_i32 SetViewportOrg(double x, double y) override;
      //virtual point_i32 SetViewportOrg(const ::point_i32 & point) override;
      //virtual point_i32 OffsetViewportOrg(i32 nWidth, i32 nHeight) override;

      // Viewport Extent
      size_f64 get_extents() override;
      size_f64 set_extents(double cx, double cy) override;
      size_f64 set_extents(const ::size_f64 & size) override;
      //virtual size_i32 ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom) override;

      // Window Origin
      point_f64 GetWindowOrg() override;
      point_f64 SetWindowOrg(double x, double y) override;
      point_f64 SetWindowOrg(const ::point_f64 & point) override;
      point_f64 offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      virtual size_f64 GetWindowExt() override;
      virtual size_f64 set_window_ext(double cx, double cy) override;
      virtual size_f64 set_window_ext(const ::size_f64 & size) override;
      virtual size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      //void DPtoLP(::point_f64 * pPoints,count nCount = 1) override;

      //void DPtoLP(::rectangle_f64 * prectangle) override;

      //void DPtoLP(::size_f64 * pSize) override;

      //void LPtoDP(::point_f64 * pPoints,count nCount = 1) override;

      //void LPtoDP(::rectangle_f64 * prectangle) override;

      //void LPtoDP(::size_f64 * pSize) override;


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      //void DPtoHIMETRIC(::size_f64 * pSize) override;

      //void LPtoHIMETRIC(::size_f64 * pSize) override;

      //void HIMETRICtoDP(::size_f64 * pSize) override;

      //void HIMETRICtoLP(::size_f64 * pSize) override;


      // Region Functions
      void fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush) override;
      void frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      void invert_region(::draw2d::region* pregion) override;
      void paint_region(::draw2d::region* pregion) override;

      // Clipping Functions
      i32 get_clip_box(::rectangle_f64 & rectangle) override;


      //void add_clipping_shapes(const shape_array<::draw2d::region>& shapea) override;
      void reset_clip() override;
      void _intersect_clip() override;
      void _add_clipping_shape(const ::rectangle & rectangle, ___shape < ::draw2d::region > & shaperegion) override;
      void _add_clipping_shape(const ::ellipse & ellipse, ___shape < ::draw2d::region > & shaperegion) override;
      void _add_clipping_shape(const ::polygon & polygon, ___shape < ::draw2d::region > & shaperegion) override;


      void intersect_clip(const ::rectangle& rectangle) override;


      //void PtVisible(double x, double y) override;
      //bool PtVisible(const ::point_i32 & point) override;
      //void RectVisible(const rectangle_i32 & prectangle) override;

      //i32 SelectClipRgn(::draw2d::region* pRgn) override;
      //i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //i32 ExcludeClipRect(const rectangle_i32 &  prectangle) override;



//      i32 ExcludeUpdateRgn(::user::primitive * pwindow) override;
      //i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //i32 IntersectClipRect(const rectangle_i32 &  prectangle) override;

      //i32 OffsetClipRgn(double x, double y) override;
      //i32 OffsetClipRgn(const ::size_i32 & size) override;
      //i32 SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      point_f64 current_position() override;
//      point_i32 move_to(double x, double y) override;
      //    point_i32 move_to(const ::point_i32 & point) override;
      using ::draw2d::graphics::line_to;
      virtual void line_to(double x, double y) override;
      //bool line_to(const ::point_f64& point) override;
      //  bool line_to(const ::point_i32 & point) override;
      virtual void polyline(const ::point_f64 * ppoint,count nCount) override;


      using ::draw2d::graphics::arc;
      //bool arc(i32 x1,i32 y1,i32 x2,i32 y2,i32 x3,i32 y3,i32 x4,i32 y4) override;
      void arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4) override;

      //bool arc(i32 x1,i32 y1,i32 x2,i32 y2, angle start, angle extends) override;
      void arc(double x1,double y1,double x2,double y2,angle start, angle extends) override;

      void angle_arc(double x,double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool arc_to(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      void arc_to(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      //i32 GetArcDirection() override;
      //i32 SetArcDirection(i32 nArcDirection) override;

      virtual void polydraw(const ::point_f64 * ppoint, const BYTE* lpTypes, ::count nCount) override;

      virtual void polyline_to(const ::point_f64 * ppoint,count nCount) override;

      virtual void poly_polyline(const ::point_f64 * ppoint, const int * lpPolyPoints, ::count nCount) override;


      virtual void poly_bezier(const ::point_f64 * ppoint, ::count nCount) override;

      virtual void poly_bezier_to(const ::point_f64 * ppoint, ::count nCount) override;



      void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::rectangle_f64 & rectangle) override;
      //bool draw(const ::point_i32 & point, ::draw2d::icon * picon, const ::size_i32 & size) override;
      //bool DrawIcon(double x, double y, ::draw2d::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, UINT nFlags,
        //             HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
        //             ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      //bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
        //         i32 x4, i32 y4) override;
      void Chord(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      void DrawFocusRect(const rectangle_f64 &  prectangle) override;


      //bool draw_ellipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //bool draw_ellipse(const rectangle_i32 &  prectangle) override;

      //bool fill_ellipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //bool fill_ellipse(const rectangle_i32 &  prectangle) override;

      virtual void clear_current_point() override;

      //bool draw_ellipse(double x1,double y1,double x2,double y2) override;
      void draw_ellipse(const ::rectangle_f64 & prectangle) override;

      //bool fill_ellipse(double x1,double y1,double x2,double y2) override;
      void fill_ellipse(const ::rectangle_f64 & prectangle) override;


      //bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      void Pie(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;


      //bool draw_polygon(const POINT * ppoints, count nCount) override;
      void draw_polygon(const ::point_f64 * ppoints, count nCount) override;
      //bool fill_polygon(const POINT * ppoints, count nCount) override;
      void fill_polygon(const ::point_f64 * ppoints, count nCount) override;
      using ::draw2d::graphics::rectangle;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;

      virtual void rectangle(const ::rectangle_f64 & rectangle) override;
      virtual void draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen) override;
      virtual void fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush) override;

      void round_rectangle(const ::rectangle_f64 & rectangle, double dRadius) override;


      using image_drawer::_draw_raw;
      void _draw_raw(const ::image_drawing & imagedrawing) override;
      
      
      //void _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64()) override;


      //// Bitmap Functions
      //bool PatBlt(double x, double y, i32 nWidth, i32 nHeight, u32 dwRop) override;
      //bool BitBltRaw(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //               i32 xSrc, i32 ySrc, u32 dwRop) override;
      //bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop) override;


      //bool StretchBltRaw(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop) override;

      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::point_f64 & point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::point_f64 & point, const ::color::color & color) override;
      ::color::color blend_pixel(const ::point_f64 & point, const ::color::color & color) override;
      //bool FloodFill(double x, double y, const ::color::color & color) override;
      //bool ExtFloodFill(double x, double y, const ::color::color & color, UINT nFillType) override;
      //bool MaskBlt(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //             i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
      //             u32 dwRop) override;
      //bool PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,

      //            i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask) override;
      //void SetPixelV(double x, double y, const ::color::color & color) override;
      //void SetPixelV(const ::point_f64 & point, const ::color::color & color) override;
      //bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
      //                  void * pMesh, ULONG nMeshElements, u32 dwMode) override;
      //bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
      //                    ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
      //                    UINT clrTransparent) override;

      //void _alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual void TextOutRaw(double x, double y, const ::scoped_string & scopedstr);
      //void ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & pszString,strsize nCount, LPINT lpDxWidths) override;

      //void ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & str, LPINT lpDxWidths) override;

      //virtual size_f64 TabbedTextOut(double x, double y, const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;

      //virtual size_f64 TabbedTextOut(double x, double y, const ::string & str,count nTabPositions, LPINT pnTabStopPositions, i32 nTabOrigin) override;


      //using ::draw2d::graphics::draw;
      //void draw(const ::point_i32 & point, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_i32 & rectangleSource) override;

      void _001DrawText(const ::string & str, rectangle_f64 & rectangleParam, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false) override;

      //void draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      //void draw_text_ex(const ::string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;


      //void draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      void draw_text_ex(const ::string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual ::count get_character_extent(double_array & daLeft, double_array& daRight, const ::string & str, strsize iStart = 0, strsize iEnd = -1) override;

      //virtual size_f64 get_text_extent(const scoped_string & strString, strsize iIndex) override;

      virtual size_f64 GetTextBegin(const scoped_string & scopedstr, strsize iIndex) override;

      //virtual size_f64 get_text_extent(const ::string & pszString, strsize nCount) override;

      //size_f64 get_text_extent(const block & block) override;

      //void get_text_extent(size_f64 & size, const scoped_string & strString, strsize nCount, strsize iIndex) override;

      size_f64 get_text_extent(const scoped_string & strString, strsize iIndex) override;

      size_f64 get_text_extent(const scoped_string & strString) override;
      //virtual size_f64 GetOutputTextExtent(const scoped_string & strString, strsize nCount) override;

      //virtual size_f64 GetOutputTextExtent(const ::string & str) override;
      ////virtual size_f64 GetTabbedTextExtent(const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      ////virtual size_f64 GetTabbedTextExtent(const ::string & str,count nTabPositions, LPINT pnTabStopPositions) override;

      //virtual size_f64 GetOutputTabbedTextExtent(const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      //virtual size_f64 GetOutputTabbedTextExtent(const ::string & str,count nTabPositions, LPINT pnTabStopPositions) override;

      //void GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, i32 nWidth, i32 nHeight) override;

      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      //virtual i32 GetTextFace(count nCount, LPTSTR pszFacename) override;

      //virtual i32 GetTextFace(string & rString) override;
      virtual void get_text_metrics(::write_text::text_metric * pMetrics) override;

      void get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
      //virtual i32 GetTextCharacterExtra() override;
      //virtual i32 SetTextCharacterExtra(i32 nCharExtra) override;

//      virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS pResults, u32 dwFlags) override;
//
//      virtual u32 GetCharacterPlacement(const ::string & pString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
//
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT pnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
//
//      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE pSize) override;
//
//
//#endif



      // Advanced Drawing
      //bool DrawEdge(const ::rectangle_i32 & rectangle,UINT nEdge,UINT nFlags) override;

      //bool DrawFrameControl(const ::rectangle_i32 & rectangle,UINT nType,UINT nState) override;


//      // Scrolling Functions
//      bool ScrollDC(i32 dx, i32 dy, const rectangle_i32 &  pRectScroll, const rectangle_i32 &  lpRectClip,
//
//                    ::draw2d::region* pRgnUpdate, RECT * pRectUpdate) override;
//
//
//      // font Functions
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      u32 SetMapperFlags(u32 dwFlag) override;
//      size_i32 GetAspectRatioFilter() override;
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC pabc) override;
//
//      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID pData, u32 cbData) override;
//
//      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR pkrnpair) override;
//
//      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW potm) override;
//
//      u32 GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm,
//
//                               u32 cbBuffer, LPVOID pBuffer, const MAT2* lpmat2) override;
//
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
//                            LPABCFLOAT pABCF) override;
//
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
//                        float* pFloatBuffer) override;
//
//
//      u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC pabc) override;
//
//      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT pBuffer) override;
//
//
//#endif
//
//      virtual i32 Escape(i32 nEscape, i32 nCount, const ::string & pszInData, LPVOID lpOutData) override;
//
//      i32 Escape(i32 nEscape, i32 nInputSize,  const scoped_string & strInputData,i32 nOutputSize, char * pszOutputData) override;
//
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const ::string & pszInputData) override;


      // Escape helpers
      //i32 StartDoc(const ::string & pszDocName) override;  // old Win3.0 version

      //i32 StartDoc(LPDOCINFOW pDocInfo) override;

      i32 StartPage() override;
      i32 EndPage() override;
      //i32 SetAbortProc(bool (CALLBACK* pfn)(HDC, i32)) override;

      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //bool PlayMetaFile(HMETAFILE hMF) override;
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const rectangle_f64 &  pBounds) override;

      void AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

      void abort_path() override;
      void begin_path() override;
      void close_figure() override;
      void end_path() override;
      void fill_path() override;
      void flatten_path() override;
      void stroke_and_fill_path() override;
      void stroke_path() override;
      void widen_path() override;

      void draw(::draw2d::path * ppath) override;
      void draw(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      void fill(::draw2d::path * ppath) override;
      void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;


      void intersect_clip(::draw2d::path * ppath) override;
      void set_clip(::draw2d::path * ppath) override;


      float GetMiterLimit() override;
      void SetMiterLimit(float fMiterLimit) override;
      //i32 GetPath(::point_f64 * ppoint, byte * lpTypes,count nCount) override;

      void SelectClipPath(i32 nMode) override;

      // Misc helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::particle * pparticle);
      //void DrawDragRect(const rectangle_i32 &  prectangle, const ::size_i32 & size,

      //                  const rectangle_i32 &  pRectLast, const ::size_i32 & sizeLast,

      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      //void fill_rectangle(const ::rectangle_i32 & rectangle, const ::color::color & color) override;

      virtual void fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color) override;

      //virtual void draw_inset_3d_rectangle(const ::rectangle_i32 & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;

      //void draw_rectangle(const ::rectangle_i32& rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);
      //void draw_rectangle(const rectangle_f64& rectangle_f64, const ::color::color& color, const ::e_border & eborder = e_border_all);
//
//#ifdef DEBUG
//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;
//#endif

//      HGDIOBJ set(HGDIOBJ) override;      // do not use for regions

      void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      void set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode) override;

      void set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;

      void set_compositing_quality(::draw2d::enum_compositing_quality ecompositingquality) override;

      void set_text_rendering_hint(::write_text::enum_rendering etextrendering) override;

      //virtual void * get_os_data() const override;
      //virtual void * get_os_data_ex(int i) const override;
      //virtual void release_os_data_ex(int i, void *point_i32) override;
      virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      void attach(void * pdata) override;


      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      void blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle) override;


      //void set_fill_mode(::draw2d::enum_fill_mode efillmode) overrid;
      //::draw2d::enum_fill_mode get_fill_mode() override;


      void flush() override;
      void sync_flush() override;

      //void draw_line(double x1, double y1, double x2, double y2) override;
      void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;

      //void draw_line(const ::point_f64 & point1, const ::point_f64 & point2, ::draw2d::pen * ppen) override;


      //virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      void prefer_mapped_image_on_mix() override;

      //bool TextOutAlphaBlend(double x, double y, const block & block) override;

      //void BitBltAlphaBlend(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop) override;

      virtual i32 meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles);


   };


} // namespace draw2d_gdiplus



