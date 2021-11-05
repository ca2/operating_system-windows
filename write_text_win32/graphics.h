#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS graphics :
      virtual public ::draw2d::graphics
   {
   public:


      ::Gdiplus::Matrix *           m_pm;
      ::Gdiplus::Graphics *         m_pgraphics;
      ::Gdiplus::GraphicsPath *     m_ppath;
      ::Gdiplus::GraphicsPath *     m_ppathPaint;
      HDC                           m_hdc;
      HDC                           m_hdcAttach;
      HDC                           m_hdcGraphics;


      graphics();
      virtual ~graphics();


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

      virtual bool attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      virtual void * detach() override;

      virtual bool attach_hdc(HDC hdc) override;   // attach/detach affects only the Output DC
      virtual HDC detach_hdc() override;
      virtual bool AttachPrinter(HDC hdc) override;
      virtual HDC DetachPrinter() override;


      bool IsPrinting() override;            // true if being used for printing


      // for bidi and mirrored localization
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;


      virtual ::e_status set(::draw2d::bitmap* pbitmap) override;

      HDC get_hdc();
      void release_hdc(HDC hdc);


      virtual double get_dpix() override;
      virtual double get_dpiy() override;

      // Constructors
      bool CreateDC(const ::string & pszDriverName, const ::string & pszDeviceName,

                    const char * pszOutput, const void * lpInitData) override;

      bool CreateIC(const ::string & pszDriverName, const ::string & pszDeviceName,

                    const char * pszOutput, const void * lpInitData) override;

      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual bool RestoreDC(i32 nSavedDC) override;
      i32 GetDeviceCaps(i32 nIndex) override;
      virtual ::u32 SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::rectangle_f64 * rectdBounds, ::u32 flags);

      bool ResetDC(const DEVMODE* pDevMode) override;


      // Drawing-Tool Functions
      point_f64 GetBrushOrg() override;
      point_f64 SetBrushOrg(double x, double y) override;
      point_f64 SetBrushOrg(const ::point_f64 & point) override;
      //i32 EnumObjects(i32 nObjectType, i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData) override;





      //::color::color GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      i32 GetPolyFillMode() override;
      i32 GetROP2() override;
      i32 GetStretchBltMode() override;

      bool _get(::draw2d::matrix & matrix) override;
      bool _set(const ::draw2d::matrix & matrix) override;
      //bool append(const ::draw2d::matrix & matrix) override;
      //bool prepend(const ::draw2d::matrix & matrix) override;

      i32 SetPolyFillMode(i32 nPolyFillMode) override;
      i32 SetROP2(i32 nDrawMode) override;
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
      i32 SetGraphicsMode(i32 iMode) override;
      i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,u32 iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual i32 GetMapMode() override;
      //virtual point_i32 GetViewportOrg() override;
      virtual i32 SetMapMode(i32 nMapMode) override;
      // Viewport Origin
      //virtual point_i32 SetViewportOrg(double x, double y) override;
      //virtual point_i32 SetViewportOrg(const ::point_i32 & point) override;
      //virtual point_i32 OffsetViewportOrg(i32 nWidth, i32 nHeight) override;

      // Viewport Extent
      virtual size_f64 GetViewportExt() override;
      virtual size_f64 SetViewportExt(double cx, double cy) override;
      virtual size_f64 SetViewportExt(const ::size_f64 & size) override;
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
      void DPtoLP(::point_f64 * pPoints,count nCount = 1) override;

      void DPtoLP(::rectangle_f64 * prectangle) override;

      void DPtoLP(::size_f64 * pSize) override;

      void LPtoDP(::point_f64 * pPoints,count nCount = 1) override;

      void LPtoDP(::rectangle_f64 * prectangle) override;

      void LPtoDP(::size_f64 * pSize) override;


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::size_f64 * pSize) override;

      void LPtoHIMETRIC(::size_f64 * pSize) override;

      void HIMETRICtoDP(::size_f64 * pSize) override;

      void HIMETRICtoLP(::size_f64 * pSize) override;


      // Region Functions
      bool fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush) override;
      bool frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      bool invert_region(::draw2d::region* pregion) override;
      bool paint_region(::draw2d::region* pregion) override;

      // Clipping Functions
      virtual i32 get_clip_box(::rectangle_f64 * prectangle) override;


      virtual ::e_status add_shapes(const shape_array& shapea);
      virtual ::e_status reset_clip();
      virtual ::e_status intersect_clip(const ::rectangle_i32& rectangle);
      virtual ::e_status intersect_clip(const ::rectangle_f64& rectangle);
      virtual ::e_status intersect_clip(const ::oval& oval);
      virtual ::e_status intersect_clip(const ::ovald& oval);
      virtual ::e_status intersect_clip(const ::polygon_i32& polygon_i32);
      virtual ::e_status intersect_clip(const ::polygon_f64& polygon_i32);

      //virtual bool PtVisible(double x, double y) override;
      //bool PtVisible(const ::point_i32 & point) override;
      //virtual bool RectVisible(const rectangle_i32 & prectangle) override;

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
      virtual bool line_to(double x, double y) override;
      //bool line_to(const ::point_f64& point) override;
      //  bool line_to(const ::point_i32 & point) override;
      virtual bool polyline(const ::point_f64 * ppoint,count nCount) override;


      using ::draw2d::graphics::Arc;
      //bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,i32 x3,i32 y3,i32 x4,i32 y4) override;
      bool Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4) override;

      //bool Arc(i32 x1,i32 y1,i32 x2,i32 y2, angle start, angle extends) override;
      bool Arc(double x1,double y1,double x2,double y2,angle start, angle extends) override;

      bool AngleArc(double x,double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool ArcTo(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      //i32 GetArcDirection() override;
      //i32 SetArcDirection(i32 nArcDirection) override;

      virtual bool polydraw(const ::point_f64 * ppoint, const BYTE* lpTypes, ::count nCount) override;

      virtual bool polyline_to(const ::point_f64 * ppoint,count nCount) override;

      virtual bool poly_polyline(const ::point_f64 * ppoint, const int * lpPolyPoints, ::count nCount) override;


      virtual bool poly_bezier(const ::point_f64 * ppoint, ::count nCount) override;

      virtual bool poly_bezier_to(const ::point_f64 * ppoint, ::count nCount) override;



      bool frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;
      bool invert_rectangle(const ::rectangle_f64 & rectangle) override;
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
      bool Chord(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      void DrawFocusRect(const rectangle_f64 &  prectangle) override;


      //bool draw_ellipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //bool draw_ellipse(const rectangle_i32 &  prectangle) override;

      //bool fill_ellipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //bool fill_ellipse(const rectangle_i32 &  prectangle) override;

      virtual ::e_status clear_current_point() override;

      //bool draw_ellipse(double x1,double y1,double x2,double y2) override;
      bool draw_ellipse(const ::rectangle_f64 & prectangle) override;

      //bool fill_ellipse(double x1,double y1,double x2,double y2) override;
      bool fill_ellipse(const ::rectangle_f64 & prectangle) override;


      //bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool Pie(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;


      //bool draw_polygon(const POINT * ppoints, count nCount) override;
      bool draw_polygon(const POINT_F64 * ppoints, count nCount) override;
      //bool fill_polygon(const POINT * ppoints, count nCount) override;
      bool fill_polygon(const POINT_F64 * ppoints, count nCount) override;
      using ::draw2d::graphics::rectangle_i32;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;

      virtual bool rectangle_i32(const ::rectangle_f64 & rectangle) override;
      virtual bool draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen) override;
      virtual bool fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush) override;

      virtual bool round_rectangle(const ::rectangle_f64 & rectangle, double dRadius) override;


      using image_drawer::_draw_raw;
      virtual bool _draw_raw(const ::image_drawing & imagedrawing) override;
      
      
      //virtual bool _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64()) override;


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
      bool SetPixelV(double x, double y, const ::color::color & color) override;
      bool SetPixelV(const ::point_f64 & point, const ::color::color & color) override;
      //bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
      //                  void * pMesh, ULONG nMeshElements, u32 dwMode) override;
      //bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
      //                    ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
      //                    UINT clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual bool TextOutRaw(double x, double y, const block & block);
      virtual bool ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & pszString,strsize nCount, LPINT lpDxWidths) override;

      virtual bool ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & str, LPINT lpDxWidths) override;

      virtual size_f64 TabbedTextOut(double x, double y, const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;

      virtual size_f64 TabbedTextOut(double x, double y, const ::string & str,count nTabPositions, LPINT pnTabStopPositions, i32 nTabOrigin) override;


      //using ::draw2d::graphics::draw;
      //virtual bool draw(const ::point_i32 & point, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_i32 & rectangleSource) override;

      virtual bool _001DrawText(const ::string & str, rectangle_f64 & rectangleParam, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false) override;

      //virtual bool draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      //virtual bool draw_text_ex(const ::string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;


      //virtual bool draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual bool draw_text_ex(const ::string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual ::count get_character_extent(double_array & daLeft, double_array& daRight, const ::string & str, strsize iStart = 0, strsize iEnd = -1) override;

      virtual size_f64 get_text_extent(const ::string & pszString, strsize nCount, strsize iIndex) override;

      virtual size_f64 GetTextBegin(const ::string & pszString, strsize nCount, strsize iIndex) override;

      //virtual size_f64 get_text_extent(const ::string & pszString, strsize nCount) override;

      virtual size_f64 get_text_extent(const ::string & str) override;
      virtual bool get_text_extent(size_f64 & size, const ::string & pszString, strsize nCount, strsize iIndex) override;

      virtual bool get_text_extent(size_f64 & size, const ::string & pszString, strsize nCount) override;

      virtual bool get_text_extent(size_f64 & size, const ::string & str) override;
      virtual size_f64 GetOutputTextExtent(const ::string & pszString, strsize nCount) override;

      virtual size_f64 GetOutputTextExtent(const ::string & str) override;
      virtual size_f64 GetTabbedTextExtent(const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual size_f64 GetTabbedTextExtent(const ::string & str,count nTabPositions, LPINT pnTabStopPositions) override;

      virtual size_f64 GetOutputTabbedTextExtent(const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual size_f64 GetOutputTabbedTextExtent(const ::string & str,count nTabPositions, LPINT pnTabStopPositions) override;

      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, i32 nWidth, i32 nHeight) override;

      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      //virtual i32 GetTextFace(count nCount, LPTSTR pszFacename) override;

      virtual i32 GetTextFace(string & rString) override;
      virtual bool get_text_metrics(::write_text::text_metric * pMetrics) override;

      virtual bool get_output_text_metrics(::write_text::text_metric * pMetrics) override;

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
//      i32 Escape(i32 nEscape, i32 nInputSize,  const char * pszInputData,i32 nOutputSize, char * pszOutputData) override;
//
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const ::string & pszInputData) override;


      // Escape helpers
      i32 StartDoc(const ::string & pszDocName) override;  // old Win3.0 version

      i32 StartDoc(LPDOCINFOW pDocInfo) override;

      i32 StartPage() override;
      i32 EndPage() override;
      //i32 SetAbortProc(bool (CALLBACK* pfn)(HDC, i32)) override;

      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      bool PlayMetaFile(HMETAFILE hMF) override;
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const rectangle_f64 &  pBounds) override;

      bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

      bool abort_path() override;
      bool begin_path() override;
      bool close_figure() override;
      bool end_path() override;
      bool fill_path() override;
      bool flatten_path() override;
      bool stroke_and_fill_path() override;
      bool stroke_path() override;
      bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;


      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      i32 GetPath(::point_f64 * ppoint, byte * lpTypes,count nCount) override;

      virtual bool SelectClipPath(i32 nMode) override;

      // Misc helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::object * pobject);
      //void DrawDragRect(const rectangle_i32 &  prectangle, const ::size_i32 & size,

      //                  const rectangle_i32 &  pRectLast, const ::size_i32 & sizeLast,

      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      //void fill_rectangle(const ::rectangle_i32 & rectangle, const ::color::color & color) override;

      virtual bool fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color) override;

      //virtual void draw_inset_3d_rectangle(const ::rectangle_i32 & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;
      virtual bool draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;

      //virtual bool draw_rectangle(const ::rectangle_i32& rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);
      virtual bool draw_rectangle(const rectangle_f64& rectangle_f64, const ::color::color& color, const ::e_border & eborder = e_border_all);

#ifdef DEBUG
      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;
#endif

//      HGDIOBJ set(HGDIOBJ) override;      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      virtual bool set_smooth_mode(::draw2d::e_smooth_mode esmoothmode) override;

      virtual bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;

      virtual bool set_compositing_quality(::draw2d::e_compositing_quality ecompositingquality) override;

      virtual bool set_text_rendering_hint(::write_text::enum_rendering etextrendering) override;

      //virtual void * get_os_data() const override;
      //virtual void * get_os_data_ex(int i) const override;
      //virtual void release_os_data_ex(int i, void *point_i32) override;
      virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata) override;


      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle) override;


      virtual bool flush() override;
      virtual bool sync_flush() override;

      //virtual bool draw_line(double x1, double y1, double x2, double y2) override;
      virtual bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;

      //virtual bool draw_line(const ::point_f64 & point1, const ::point_f64 & point2, ::draw2d::pen * ppen) override;


      virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      virtual bool prefer_mapped_image_on_mix() override;

      virtual bool TextOutAlphaBlend(double x, double y, const block & block) override;

      //virtual bool BitBltAlphaBlend(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop) override;

      virtual i32 meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles);


   };


} // namespace draw2d_gdiplus



