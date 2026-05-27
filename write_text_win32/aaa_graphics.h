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

//      ::windowing::window * GetWindow() override;

      virtual bool attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      virtual void * detach() override;

      virtual bool attach_hdc(HDC hdc) override;   // attach/detach affects only the Output DC
      virtual HDC detach_hdc() override;
      virtual bool AttachPrinter(HDC hdc) override;
      virtual HDC DetachPrinter() override;


      bool IsPrinting() override;            // true if being used for printing


      // for bidi and mirrored localization
      ::u32 GetLayout() override;
      ::u32 SetLayout(::u32 dwLayout) override;


      virtual void set(::draw2d::bitmap* pbitmap) override;

      HDC get_hdc();
      void release_hdc(HDC hdc);


      virtual ::f64 get_dpix() override;
      virtual ::f64 get_dpiy() override;

      // Constructors
      bool CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName,

                    const scoped_string & strOutput, const void * lpInitData) override;

      bool CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName,

                    const scoped_string & strOutput, const void * lpInitData) override;

      bool create_compatible_graphics(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual ::i32 SaveDC() override;
      virtual bool RestoreDC(::i32 nSavedDC) override;
      ::i32 GetDeviceCaps(::i32 nIndex) override;
      virtual ::u32 SetBoundsRect(const ::f64_rectangle & rectangleBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::f64_rectangle * rectdBounds, ::u32 flags);

      bool ResetDC(const DEVMODE* pDevMode) override;


      // Drawing-Tool Functions
      ::f64_point GetBrushOrg() override;
      ::f64_point SetBrushOrg(::f64 x, ::f64 y) override;
      ::f64_point SetBrushOrg(const ::f64_point & point) override;
      //::i32 EnumObjects(::i32 nObjectType, ::i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData) override;





      //::color::color GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      ::i32 GetPolyFillMode() override;
      ::i32 GetROP2() override;
      ::i32 GetStretchBltMode() override;

      bool _get(::geometry2d::matrix & matrix) override;
      bool _set(const ::geometry2d::matrix & matrix) override;
      //bool append(const ::geometry2d::matrix & matrix) override;
      //bool prepend(const ::geometry2d::matrix & matrix) override;

      ::i32 SetPolyFillMode(::i32 nPolyFillMode) override;
      ::i32 SetROP2(::i32 nDrawMode) override;
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
      ::i32 SetGraphicsMode(::i32 iMode) override;
      ::i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,::u32 iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual ::i32 GetMapMode() override;
      //virtual i32_point GetViewportOrg() override;
      virtual ::i32 SetMapMode(::i32 nMapMode) override;
      // Viewport Origin
      //virtual i32_point SetViewportOrg(::f64 x, ::f64 y) override;
      //virtual i32_point SetViewportOrg(const ::i32_point & point) override;
      //virtual i32_point OffsetViewportOrg(::i32 nWidth, ::i32 nHeight) override;

      // Viewport Extent
      virtual ::f64_size GetViewportExt() override;
      virtual ::f64_size SetViewportExt(::f64 cx, ::f64 cy) override;
      virtual ::f64_size SetViewportExt(const ::f64_size & size) override;
      //virtual i32_size ScaleViewportExt(::i32 xNum, ::i32 xDenom, ::i32 yNum, ::i32 yDenom) override;

      // Window Origin
      ::f64_point GetWindowOrg() override;
      ::f64_point SetWindowOrg(::f64 x, ::f64 y) override;
      ::f64_point SetWindowOrg(const ::f64_point & point) override;
      ::f64_point offset_window_org(::f64 nWidth, ::f64 nHeight) override;

      // Window extent
      virtual ::f64_size GetWindowExt() override;
      virtual ::f64_size set_window_ext(::f64 cx, ::f64 cy) override;
      virtual ::f64_size set_window_ext(const ::f64_size & size) override;
      virtual ::f64_size scale_window_ext(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom) override;

      // Coordinate Functions
      void DPtoLP(::f64_point * pPoints,count nCount = 1) override;

      void DPtoLP(::f64_rectangle * prectangle) override;

      void DPtoLP(::f64_size * pSize) override;

      void LPtoDP(::f64_point * pPoints,count nCount = 1) override;

      void LPtoDP(::f64_rectangle * prectangle) override;

      void LPtoDP(::f64_size * pSize) override;


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::f64_size * pSize) override;

      void LPtoHIMETRIC(::f64_size * pSize) override;

      void HIMETRICtoDP(::f64_size * pSize) override;

      void HIMETRICtoLP(::f64_size * pSize) override;


      // Region Functions
      bool fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush) override;
      bool frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, ::f64 nWidth, ::f64 nHeight) override;
      bool invert_region(::draw2d::region* pregion) override;
      bool paint_region(::draw2d::region* pregion) override;

      // Clipping Functions
      virtual ::i32 get_clip_box(::f64_rectangle * prectangle) override;


      virtual void add_shapes(const shape_array& shapea);
      virtual void reset_clip();
      virtual void intersect_clip(const ::i32_rectangle& rectangle);
      virtual void intersect_clip(const ::f64_rectangle& rectangle);
      virtual void intersect_clip(const ::oval& oval);
      virtual void intersect_clip(const ::ovald& oval);
      virtual void intersect_clip(const ::i32_polygon& i32_polygon);
      virtual void intersect_clip(const ::f64_polygon& i32_polygon);

      //virtual bool PtVisible(::f64 x, ::f64 y) override;
      //bool PtVisible(const ::i32_point & point) override;
      //virtual bool RectVisible(const i32_rectangle & prectangle) override;

      //::i32 SelectClipRgn(::draw2d::region* pRgn) override;
      //::i32 ExcludeClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      //::i32 ExcludeClipRect(const i32_rectangle &  prectangle) override;



//      ::i32 ExcludeUpdateRgn(::user::prototype * pwindow) override;
      //::i32 IntersectClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      //::i32 IntersectClipRect(const i32_rectangle &  prectangle) override;

      //::i32 OffsetClipRgn(::f64 x, ::f64 y) override;
      //::i32 OffsetClipRgn(const ::i32_size & size) override;
      //::i32 SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      ::f64_point current_position() override;
//      i32_point move_to(::f64 x, ::f64 y) override;
      //    i32_point move_to(const ::i32_point & point) override;
      using ::draw2d::graphics::line_to;
      virtual bool line_to(::f64 x, ::f64 y) override;
      //bool line_to(const ::f64_point& point) override;
      //  bool line_to(const ::i32_point & point) override;
      virtual bool polyline(const ::f64_point * ppoint,count nCount) override;


      using ::draw2d::graphics::Arc;
      //bool Arc(::i32 x1,::i32 y1,::i32 x2,::i32 y2,::i32 x3,::i32 y3,::i32 x4,::i32 y4) override;
      bool Arc(::f64 x1,::f64 y1,::f64 x2,::f64 y2,::f64 x3,::f64 y3,::f64 x4,::f64 y4) override;

      //bool Arc(::i32 x1,::i32 y1,::i32 x2,::i32 y2, angle start, angle extends) override;
      bool Arc(::f64 x1,::f64 y1,::f64 x2,::f64 y2,angle start, angle extends) override;

      bool AngleArc(::f64 x,::f64 y, ::f64 nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool ArcTo(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool ArcTo(const ::f64_rectangle &  prectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;

      //::i32 GetArcDirection() override;
      //::i32 SetArcDirection(::i32 nArcDirection) override;

      virtual bool polydraw(const ::f64_point * ppoint, const BYTE* lpTypes, ::collection::count nCount) override;

      virtual bool polyline_to(const ::f64_point * ppoint,count nCount) override;

      virtual bool poly_polyline(const ::f64_point * ppoint, const ::i32 * lpPolyPoints, ::collection::count nCount) override;


      virtual bool poly_bezier(const ::f64_point * ppoint, ::collection::count nCount) override;

      virtual bool poly_bezier_to(const ::f64_point * ppoint, ::collection::count nCount) override;



      bool frame_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      bool invert_rectangle(const ::f64_rectangle & rectangle) override;
      //bool draw(const ::i32_point & point, ::image::icon * picon, const ::i32_size & size) override;
      //bool DrawIcon(::f64 x, ::f64 y, ::image::icon * picon, ::i32 cx, ::i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HBITMAP hBitmap, UINT nFlags,
        //             HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
        //             ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & scopedstrText, UINT nFlags,

      //               bool bPrefixText = true, ::i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & scopedstrText, UINT nFlags,

      //               bool bPrefixText = true, ::i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      //bool Chord(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3,
        //         ::i32 x4, ::i32 y4) override;
      bool Chord(const ::f64_rectangle &  prectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;

      void DrawFocusRect(const ::f64_rectangle &  prectangle) override;


      //bool draw_ellipse(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      //bool draw_ellipse(const i32_rectangle &  prectangle) override;

      //bool fill_ellipse(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      //bool fill_ellipse(const i32_rectangle &  prectangle) override;

      virtual void clear_current_point() override;

      //bool draw_ellipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2) override;
      bool draw_ellipse(const ::f64_rectangle & prectangle) override;

      //bool fill_ellipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2) override;
      bool fill_ellipse(const ::f64_rectangle & prectangle) override;


      //bool Pie(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool Pie(const ::f64_rectangle &  prectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;


      //bool draw_polygon(const POINT * ppoints, ::collection::count nCount) override;
      bool draw_polygon(const ::f64_point * ppoints, ::collection::count nCount) override;
      //bool fill_polygon(const POINT * ppoints, ::collection::count nCount) override;
      bool fill_polygon(const ::f64_point * ppoints, ::collection::count nCount) override;
      using ::draw2d::graphics::i32_rectangle;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;

      virtual bool i32_rectangle(const ::f64_rectangle & rectangle) override;
      virtual bool draw_rectangle(const ::f64_rectangle & rectangle, ::draw2d::pen * ppen) override;
      virtual bool fill_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush * pbrush) override;

      virtual bool round_rectangle(const ::f64_rectangle & rectangle, ::f64 dRadius) override;


      using image_drawer::_draw_raw;
      virtual bool _draw_raw(const ::image::image_drawing & imagedrawing) override;
      
      
      //virtual bool _stretch_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource = ::f64_rectangle()) override;


      //// Bitmap Functions
      //bool PatBlt(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::u32 dwRop) override;
      //bool BitBltRaw(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //               ::i32 xSrc, ::i32 ySrc, ::u32 dwRop) override;
      //bool StretchBltRaw(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight, ::u32 dwRop) override;


      //bool StretchBltRaw(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight, ::u32 dwRop) override;

      ::color::color GetPixel(::f64 x, ::f64 y) override;
      ::color::color GetPixel(const ::f64_point & point) override;
      ::color::color SetPixel(::f64 x, ::f64 y, const ::color::color & color) override;
      ::color::color SetPixel(const ::f64_point & point, const ::color::color & color) override;
      ::color::color blend_pixel(const ::f64_point & point, const ::color::color & color) override;
      //bool FloodFill(::f64 x, ::f64 y, const ::color::color & color) override;
      //bool ExtFloodFill(::f64 x, ::f64 y, const ::color::color & color, UINT nFillType) override;
      //bool MaskBlt(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //             ::i32 xSrc, ::i32 ySrc, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask,
      //             ::u32 dwRop) override;
      //bool PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc,

      //            ::i32 nWidth, ::i32 nHeight, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask) override;
      bool SetPixelV(::f64 x, ::f64 y, const ::color::color & color) override;
      bool SetPixelV(const ::f64_point & point, const ::color::color & color) override;
      //bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
      //                  void * pMesh, ULONG nMeshElements, ::u32 dwMode) override;
      //bool TransparentBlt(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
      //                    ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
      //                    UINT clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource, ::f64 dOpacity) override;

      /*bool alpha_blend(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual bool TextOutRaw(::f64 x, ::f64 y, const block & block);
      virtual bool ExtTextOut(::f64 x, ::f64 y, UINT nOptions, const ::f64_rectangle &  prectangle, const ::scoped_string & scopedstrString,character_count nCount, LPINT lpDxWidths) override;

      virtual bool ExtTextOut(::f64 x, ::f64 y, UINT nOptions, const ::f64_rectangle &  prectangle, const ::scoped_string & scopedstr, LPINT lpDxWidths) override;

      virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions, ::i32 nTabOrigin) override;

      virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions, ::i32 nTabOrigin) override;


      //using ::draw2d::graphics::draw;
      //virtual bool draw(const ::i32_point & point, ::draw2d::graphics * pgraphicsSrc, const ::i32_rectangle & rectangleSource) override;

      virtual bool _001DrawText(const ::scoped_string & scopedstr, ::f64_rectangle & rectangleParam, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false) override;

      //virtual bool draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      //virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;


      //virtual bool draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual ::collection::count get_character_extent(::f64_array & daLeft, ::f64_array& daRight, const ::scoped_string & scopedstr, character_count iStart = 0, character_count iEnd = -1) override;

      virtual ::f64_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex) override;

      virtual ::f64_size GetTextBegin(const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex) override;

      //virtual ::f64_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount) override;

      virtual ::f64_size get_text_extent(const ::scoped_string & scopedstr) override;
      virtual bool get_text_extent(::f64_size & size, const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex) override;

      virtual bool get_text_extent(::f64_size & size, const ::scoped_string & scopedstrString, character_count nCount) override;

      virtual bool get_text_extent(::f64_size & size, const ::scoped_string & scopedstr) override;
      virtual ::f64_size GetOutputTextExtent(const ::scoped_string & scopedstrString, character_count nCount) override;

      virtual ::f64_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      virtual ::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual ::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions) override;

      virtual ::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual ::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions) override;

      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, ::i32), LPARAM lpData, ::i32 nCount, ::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight) override;

      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      //virtual ::i32 GetTextFace(count nCount, LPTSTR pszFacename) override;

      virtual ::i32 GetTextFace(string & rString) override;
      virtual bool get_text_metrics(::write_text::text_metric * pMetrics) override;

      virtual bool get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual ::i32 SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount) override;
      //virtual ::i32 GetTextCharacterExtra() override;
      //virtual ::i32 SetTextCharacterExtra(::i32 nCharExtra) override;

//      virtual ::u32 GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS pResults, ::u32 dwFlags) override;
//
//      virtual ::u32 GetCharacterPlacement(const ::string & pString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) override;
//
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, ::i32 cgi, ::i32 nMaxExtent, LPINT pnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
//
//      bool GetTextExtentPointI(LPWORD pgiIn, ::i32 cgi, __out_opt LPSIZE pSize) override;
//
//
//#endif



      // Advanced Drawing
      //bool DrawEdge(const ::i32_rectangle & rectangle,UINT nEdge,UINT nFlags) override;

      //bool DrawFrameControl(const ::i32_rectangle & rectangle,UINT nType,UINT nState) override;


//      // Scrolling Functions
//      bool ScrollDC(::i32 dx, ::i32 dy, const i32_rectangle &  pRectScroll, const i32_rectangle &  lpRectClip,
//
//                    ::draw2d::region* pRgnUpdate, RECT * pRectUpdate) override;
//
//
//      // font Functions
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      ::u32 SetMapperFlags(::u32 dwFlag) override;
//      i32_size GetAspectRatioFilter() override;
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC pabc) override;
//
//      ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID pData, ::u32 cbData) override;
//
//      ::i32 GetKerningPairs(::i32 nPairs, LPKERNINGPAIR pkrnpair) override;
//
//      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW potm) override;
//
//      ::u32 GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm,
//
//                               ::u32 cbBuffer, LPVOID pBuffer, const MAT2* lpmat2) override;
//
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
//                            LPABCFLOAT pABCF) override;
//
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
//                        ::f32* pFloatBuffer) override;
//
//
//      ::u32 GetFontLanguageInfo() override;
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
//      virtual ::i32 Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData) override;
//
//      ::i32 Escape(::i32 nEscape, ::i32 nInputSize,  const scoped_string & strInputData,::i32 nOutputSize, ::i8 * pszOutputData) override;
//
//      ::i32 DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData) override;


      // Escape helpers
      ::i32 StartDoc(const ::scoped_string & scopedstrDocName) override;  // old Win3.0 version

      ::i32 StartDoc(LPDOCINFOW pDocInfo) override;

      ::i32 StartPage() override;
      ::i32 EndPage() override;
      //::i32 SetAbortProc(bool (CALLBACK* pfn)(HDC, ::i32)) override;

      ::i32 AbortDoc() override;
      ::i32 EndDoc() override;

      // MetaFile Functions
      bool PlayMetaFile(HMETAFILE hMF) override;
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::f64_rectangle &  pBounds) override;

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


      ::f32 GetMiterLimit() override;
      bool SetMiterLimit(::f32 fMiterLimit) override;
      ::i32 GetPath(::f64_point * ppoint, ::u8 * lpTypes,count nCount) override;

      virtual bool SelectClipPath(::i32 nMode) override;

      // Misc helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::particle * pparticle);
      //void DrawDragRect(const i32_rectangle &  prectangle, const ::i32_size & size,

      //                  const i32_rectangle &  pRectLast, const ::i32_size & sizeLast,

      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      //void fill_rectangle(const ::i32_rectangle & rectangle, const ::color::color & color) override;

      virtual bool fill_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color) override;

      //virtual void draw_inset_3d_rectangle(const ::i32_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;
      virtual bool draw_inset_3d_rectangle(const ::f64_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;

      //virtual bool draw_rectangle(const ::i32_rectangle& rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);
      virtual bool draw_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);

#ifdef DEBUG
      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;
#endif

//      HGDIOBJ set(HGDIOBJ) override;      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      virtual bool set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode) override;

      virtual bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;

      virtual bool set_compositing_quality(::draw2d::enum_compositing_quality ecompositingquality) override;

      virtual bool set_text_rendering_hint(::write_text::enum_rendering etextrendering) override;

      //virtual void * get_os_data() const override;
      //virtual void * get_os_data_ex(::i32 i) const override;
      //virtual void release_os_data_ex(::i32 i, void *i32_point) override;
      virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata) override;


      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, ::f64 dRadius, const ::f64_rectangle & rectangle) override;


      virtual bool flush() override;
      virtual bool sync_flush() override;

      //virtual bool draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      virtual bool draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen) override;

      //virtual bool draw_line(const ::f64_point & point1, const ::f64_point & point2, ::draw2d::pen * ppen) override;


      virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      virtual bool prefer_mapped_image_on_mix() override;

      virtual bool TextOutAlphaBlend(::f64 x, ::f64 y, const block & block) override;

      //virtual bool BitBltAlphaBlend(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::u32 dwRop) override;

      virtual ::i32 meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, ::i32 nHandles);


   };


} // namespace draw2d_gdiplus



