#pragma once


namespace draw2d_gdi
{


   class object;


   class CLASS_DECL_DRAW2D_GDI graphics :
      virtual public ::draw2d::graphics
   {
   public:


      enum e_data
      {
         data_graphics,
         data_bitmap,
         data_pen,
         data_brush,
         data_font,
         data_palette,
         data_region,
      };


      class draw_item
      {
      public:

         const POINT * lpPoints;
         const INT * lpPolyCounts;
         count nCount;

      };


      HDC                                                m_hdc;

      ::draw2d::path_pointer                                  m_sppath;

      HBITMAP                                            m_hbitmapOriginal;
      HPEN                                               m_hpenOriginal;
      HBRUSH                                             m_hbrushOriginal;
      HFONT                                              m_hfontOriginal;
      HRGN                                               m_hrgnOriginal;

      address_array < ::draw2d_gdi::object * >           m_ptraObject;


      graphics(::particle * pparticle);
      virtual ~graphics();


      bool attach_hdc(HDC hdc) override;
      HDC detach_hdc() override;

      operator HDC() const;
      HDC get_handle1() const; // Always returns the Output DC
      HDC get_handle2() const; // Always returns the Output DC
      virtual void * get_os_data() const override;
      virtual void * get_os_data_ex(::i32 i) const override;
      virtual HDC get_handle() const;


      ::image::image_pointer pimage_work(const ::i32_size & size, bool bReset);
      image fill_image_work(::color::color clr, const ::i32_size & size, bool bReset);

      bool internal_fill_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::i32_rectangle & rectangleParam, ::draw2d::brush * pbrush);
      bool internal_stroke_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::i32_rectangle & rectangleParam, ::draw2d::pen * ppen);
      bool internal_fill_and_stroke_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam, const ::i32_rectangle & rectangleParam,::draw2d::brush * pbrush,::draw2d::pen * ppen);

      void internal_set_path(void * pparam);
      void internal_set_path_ellipse(void * pparam);
      void internal_set_path_rectangle(void * pparam);
      void internal_set_path_line(void * pparam);
      void internal_set_path_polygon(void * pparam);
      void internal_set_path_poly_polygon(void * pparam);

      bool IsPrinting() override;            // true if being used for printing

      ::draw2d::pen *      get_current_pen() override;
      ::draw2d::brush *    get_current_brush() override;
      ::draw2d::palette *  get_current_palette() override;
      ::write_text::font *     get_current_font() override;
      ::draw2d::bitmap *   get_current_bitmap() override;

      // for bidi and mirrored localization
      ::u32 GetLayout() override;
      ::u32 SetLayout(::u32 dwLayout) override;

      void set_original_object(::i32 iType);

      // Constructors
      bool CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      bool CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      bool create_compatible_graphics(::draw2d::graphics_pointer & pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual ::i32 SaveDC() override;
      virtual bool RestoreDC(::i32 nSavedDC) override;
      ::i32 GetDeviceCaps(::i32 nIndex) override;
      UINT SetBoundsRect(const ::i32_rectangle & rectangleBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectangleBounds, UINT flags) override;
      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      i32_point GetBrushOrg() override;
      i32_point SetBrushOrg(::i32 x, ::i32 y) override;
      i32_point SetBrushOrg(const ::i32_point & point) override;
      ::i32 EnumObjects(::i32 nObjectType,
                      ::i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      //virtual ::draw2d::object* SelectStockObject(::i32 nIndex) override;
      virtual ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
      virtual ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
      virtual ::write_text::font* SelectObject(::write_text::font* pFont) override;
      virtual ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap) override;
      virtual ::i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions

      virtual void on_select_object(::draw2d::particle * pparticleParam);

      bool SelectFont(::write_text::font * pfont) override;



      virtual void select_pen();
      virtual void select_brush();
      virtual void select_font();
      virtual void select_null_pen();
      virtual void select_null_brush();


      // color and color Palette Functions
      ::color::color GetNearestColor(::color::color crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette() override;
      void UpdateColors() override;

      // Drawing-Attribute Functions
      ::color::color GetBkColor();
      ::i32 GetBkMode();
      ::i32 GetPolyFillMode() override;
      ::i32 GetROP2() override;
      ::i32 GetStretchBltMode() override;
      ::color::color GetTextColor();

      virtual ::color::color SetBkColor(::color::color crColor);
      ::i32 SetBkMode(::i32 nBkMode);
      ::i32 SetPolyFillMode(::i32 nPolyFillMode) override;
      ::i32 SetROP2(::i32 nDrawMode) override;
      ::i32 SetStretchBltMode(::i32 nStretchMode) override;
      virtual ::color::color SetTextColor(::color::color crColor);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

#if (_WIN32_WINNT >= 0x0500)

      ::color::color GetDCBrushColor() override;
      ::color::color SetDCBrushColor(::color::color crColor) override;

      ::color::color GetDCPenColor() override;
      ::color::color SetDCPenColor(::color::color crColor) override;

#endif

      // Graphics mode
      ::i32 SetGraphicsMode(::i32 iMode) override;
      ::i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,::u32 iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual ::i32 GetMapMode() override;
      virtual i32_point GetViewportOrg() override;
      virtual ::i32 SetMapMode(::i32 nMapMode) override;
      // Viewport Origin
      virtual i32_point SetViewportOrg(::i32 x, ::i32 y) override;
      virtual i32_point SetViewportOrg(const ::i32_point & point) override;
      virtual i32_point OffsetViewportOrg(::i32 nWidth, ::i32 nHeight) override;

      // Viewport Extent
      virtual ::i32_size GetViewportExt() override;
      virtual ::i32_size SetViewportExt(::i32 cx, ::i32 cy) override;
      virtual ::i32_size SetViewportExt(const ::i32_size & size) override;
      virtual ::i32_size ScaleViewportExt(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom) override;

      // Window Origin
      ::i32_point GetWindowOrg() override;
      ::i32_point SetWindowOrg(::i32 x, ::i32 y) override;
      ::i32_point SetWindowOrg(const ::i32_point & point) override;
      ::i32_point offset_window_org(::i32 nWidth, ::i32 nHeight) override;

      // Window extent
      ::i32_size GetWindowExt() override;
      virtual ::i32_size set_window_ext(::i32 cx, ::i32 cy) override;
      ::i32_size set_window_ext(const ::i32_size & size) override;
      virtual ::i32_size scale_window_ext(::i32 xNum, ::i32 xDenom, ::i32 yNum, ::i32 yDenom) override;

      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints, ::collection::count nCount = 1) override;
      void DPtoLP(RECT * prectangle) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, ::collection::count nCount = 1) override;
      void LPtoDP(RECT * prectangle) override;
      void LPtoDP(LPSIZE lpSize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) override;
      void LPtoHIMETRIC(LPSIZE lpSize) override;
      void HIMETRICtoDP(LPSIZE lpSize) override;
      void HIMETRICtoLP(LPSIZE lpSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, ::i32 nWidth, ::i32 nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual ::i32 get_clip_box(RECT * prectangle) override;
      virtual bool PtVisible(::i32 x, ::i32 y) override;
      bool PtVisible(const ::i32_point & point) override;
      virtual bool RectVisible(const ::i32_rectangle & rectangle) override;
      ::i32 SelectClipRgn(::draw2d::region* pRgn) override;
      ::i32 ExcludeClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      ::i32 ExcludeClipRect(const ::i32_rectangle & rectangle) override;
      ::i32 ExcludeUpdateRgn(::user::prototype * pwindow);
      ::i32 IntersectClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      ::i32 IntersectClipRect(const ::i32_rectangle & rectangle) override;
      ::i32 OffsetClipRgn(::i32 x, ::i32 y) override;
      ::i32 OffsetClipRgn(const ::i32_size & size) override;
      ::i32 SelectClipRgn(::draw2d::region* pRgn, ::i32 nMode) override;

      // Line-Output Functions
      ::f64_point current_position() override;
      using ::draw2d::graphics::move_to;
      bool move_to(const ::i32_point & lppt) override;
      using ::draw2d::graphics::line_to;
      bool line_to(const ::i32_point & lppt) override;
      bool Arc(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool Arc(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd) override;
      bool polyline(const POINT* lpPoints,count nCount) override;

      bool AngleArc(::i32 x, ::i32 y, ::i32 nRadius, ::f32 fStartAngle, ::f32 fSweepAngle) override;
      bool ArcTo(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool ArcTo(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd) override;
      ::i32 GetArcDirection() override;
      ::i32 SetArcDirection(::i32 nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount) override;
      bool polyline_to(const POINT* lpPoints,count nCount) override;
      bool poly_polyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount) override;

      bool poly_bezier(const POINT* lpPoints,count nCount) override;
      bool poly_bezier_to(const POINT* lpPoints,count nCount) override;



      // Simple Drawing Functions
      bool fill_rectangle(const ::i32_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void frame_rectangle(const ::i32_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::i32_rectangle & rectangle) override;
      bool DrawIcon(::i32 x, ::i32 y, ::image::icon * picon) override;
      bool DrawIcon(const ::i32_point & point, ::image::icon * picon) override;
      bool DrawIcon(::i32 x, ::i32 y, ::image::icon * picon, ::i32 cx, ::i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HBITMAP hBitmap, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & scopedstrText, UINT nFlags,
      //               bool bPrefixText = true, ::i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & scopedstrText, UINT nFlags,
      //               bool bPrefixText = true, ::i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      virtual bool draw_rectangle(const ::i32_rectangle & rectangle, ::draw2d::pen * ppen) override;

      // Ellipse and Polygon Functions
      bool Chord(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool Chord(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd) override;
      void DrawFocusRect(const ::i32_rectangle & rectangle) override;

      bool ellipse(const ::f64_rectangle & rectangle) override;
      bool draw_ellipse(const ::f64_rectangle & rectangle) override;
      bool fill_ellipse(const ::f64_rectangle & rectangle) override;

      bool i32_rectangle(const ::i32_rectangle & rectangle) override;
      bool draw_rectangle(const ::i32_rectangle & rectangle) override;
      bool fill_rectangle(const ::i32_rectangle & rectangle) override;

      bool i32_polygon(const POINT * ppoint, ::collection::count nCount) override;
      bool draw_polygon(const POINT * ppoint,count nCount) override;
      bool fill_polygon(const POINT * ppoint,count nCount) override;

      bool poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool draw_poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool fill_poly_polygon(const POINT * ppoint, const INT * piPolyCount, ::collection::count nCount) override;

      bool Pie(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      bool Pie(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd) override;

      bool round_rectangle(const ::i32_rectangle & rectangle, const ::i32_point & lppt) override;

      // Bitmap Functions
      bool PatBlt(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight, ::u32 dwRop) override;
      bool draw(const ::i32_rectangle & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::i32_point & lppt, ::u32 dwRop) override;
      bool StretchBlt(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight, ::draw2d::graphics * pgraphicsSrc,
                      ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight, ::u32 dwRop) override;
      ::color::color GetPixel(::i32 x, ::i32 y) override;
      ::color::color GetPixel(const ::i32_point & point) override;
      ::color::color SetPixel(::i32 x, ::i32 y, ::color::color crColor) override;
      ::color::color SetPixel(const ::i32_point & point, ::color::color crColor) override;
      bool FloodFill(::i32 x, ::i32 y, ::color::color crColor) override;
      bool ExtFloodFill(::i32 x, ::i32 y, ::color::color crColor, UINT nFillType) override;
      bool MaskBlt(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                   ::i32 xSrc, ::i32 ySrc, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask,
                   ::u32 dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc,
                  ::i32 nWidth, ::i32 nHeight, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask) override;
      bool SetPixelV(::i32 x, ::i32 y, ::color::color crColor) override;
      bool SetPixelV(const ::i32_point & point, ::color::color crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, ::u32 dwMode) override;
      bool TransparentBlt(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
                          UINT clrTransparent) override;
      /*bool alpha_blend(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
        BLENDFUNCTION blend) override;*/
      bool alpha_blend(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
                       ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
                       ::f64 dOpacity) override;

      virtual bool get_text_extent(::f64_size & size, const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex) override;

      // Text Functions
      virtual bool text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount) override;
      virtual bool text_out(::i32 x, ::i32 y, const ::scoped_string & scopedstr) override;
      virtual bool ExtTextOut(::i32 x, ::i32 y, UINT nOptions, const ::i32_rectangle & rectangle, const ::scoped_string & scopedstrString, ::collection::count nCount, INT * lpDxWidths) override;
      virtual bool ExtTextOut(::i32 x, ::i32 y, UINT nOptions, const ::i32_rectangle & rectangle, const ::scoped_string & scopedstr, INT * lpDxWidths) override;
      virtual ::i32_size TabbedTextOut(::i32 x, ::i32 y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions, ::i32 nTabOrigin) override;
      virtual ::i32_size TabbedTextOut(::i32 x, ::i32 y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions, ::i32 nTabOrigin) override;

      virtual bool draw_text(const ::scoped_string & scopedstrString,character_count nCount,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const ::scoped_string & scopedstr,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual bool draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;
      virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual ::f64_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount) override;
      virtual ::f64_size get_text_extent(const ::scoped_string & scopedstr) override;
      virtual ::i32_size GetOutputTextExtent(const ::scoped_string & scopedstrString,character_count nCount) override;
      virtual ::i32_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      virtual ::i32_size GetTabbedTextExtent(const ::scoped_string & scopedstrString,character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::i32_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::i32_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString,character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::i32_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, ::i32), LPARAM lpData, ::i32 nCount, ::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight) override;
      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      virtual ::i32 GetTextFace(count nCount, LPTSTR lpszFacename) override;
      virtual ::i32 GetTextFace(string & rString) override;

      virtual bool get_text_metrics(::write_text::text_metric * lpMetrics) override;
      virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics) override;

      virtual ::i32 SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount) override;
      virtual ::i32 GetTextCharacterExtra() override;
      virtual ::i32 SetTextCharacterExtra(::i32 nCharExtra) override;

      virtual ::u32 GetCharacterPlacement(const ::string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) override;
      virtual ::u32 GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, ::i32 cgi, ::i32 nMaxExtent, INT * lpnFit, INT * alpDx, __out_opt LPSIZE lpSize) override;
      bool GetTextExtentPointI(LPWORD pgiIn, ::i32 cgi, __out_opt LPSIZE lpSize) override;

#endif



      // Advanced Drawing
      bool DrawEdge(RECT * prectangle, UINT nEdge, UINT nFlags);
      bool DrawFrameControl(RECT * prectangle, UINT nType, UINT nState);

      // Scrolling Functions
      bool ScrollDC(::i32 dx, ::i32 dy, const ::i32_rectangle & lpRectScroll, const ::i32_rectangle & lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      ::u32 SetMapperFlags(::u32 dwFlag) override;
      ::i32_size GetAspectRatioFilter() override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
      ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID lpData, ::u32 cbData) override;
      ::i32 GetKerningPairs(::i32 nPairs, LPKERNINGPAIR lpkrnpair) override;
      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
      ::u32 GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm, ::u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
                            LPABCFLOAT lpABCF) override;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        ::f32* lpFloatBuffer) override;

      ::u32 GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, INT * lpBuffer) override;

#endif

      // Printer/Device Escape Functions
      virtual ::i32 Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData) override;
      virtual ::i32 Escape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData, ::i32 nOutputSize, ::i8 * lpszOutputData) override;
      virtual ::i32 DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData) override;

      // Escape helpers
      virtual ::i32 StartDoc(const ::scoped_string & scopedstrDocName) override;  // old Win3.0 version
      virtual ::i32 StartDoc(LPDOCINFOW lpDocInfo) override;
      virtual ::i32 StartPage() override;
      virtual ::i32 EndPage() override;
      virtual ::i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, ::i32)) override;
      virtual ::i32 AbortDoc() override;
      virtual ::i32 EndDoc() override;

      // MetaFile Functions
      virtual bool PlayMetaFile(HMETAFILE hMF) override;
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::i32_rectangle & lpBounds) override;
      virtual bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

      // Path Functions
      bool abort_path() override;
      bool begin_path() override;
      bool close_figure() override;
      bool end_path() override;
      bool flatten_path() override;
      bool fill_path() override;
      bool stroke_and_fill_path() override;
      bool stroke_path() override;
      bool fill_path(::draw2d::brush * pbrush);
      bool stroke_and_fill_path(::draw2d::brush * pbrush,::draw2d::pen * ppen);
      bool stroke_path(::draw2d::pen * ppen);
      bool widen_path() override;
      ::f32 GetMiterLimit() override;
      bool SetMiterLimit(::f32 fMiterLimit) override;
      ::i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes, ::collection::count nCount) override;
      bool SelectClipPath(::i32 nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::particle * pparticle);
      //void DrawDragRect(const ::i32_rectangle & rectangle, const ::i32_size & size,
      //                  const ::i32_rectangle & rectangleLast, const ::i32_size & sizeLast, ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      using ::draw2d::graphics::fill_rectangle;
      void fill_rectangle(const ::i32_rectangle & rectangle, ::color::color color32) override;

      using ::draw2d::graphics::draw_inset_3d_rectangle;
      void draw_inset_3d_rectangle(const ::i32_rectangle & rectangle, ::color::color crTopLeft, ::color::color crBottomRight, const ::e_border & eborder = e_border_all) override;

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions


      bool set(::draw2d::path * ppath);
      bool set(::draw2d::path::matter & pmatter);
      bool set(::draw2d::path::line & pline);
      bool set(::draw2d::path::arc & parc);
      bool set(::draw2d::path::move & pmove);
      bool set(::draw2d::path::string_path & stringpath);
      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;
      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath,::draw2d::brush * pbrush) override;

      bool select_path(::draw2d::path * ppath);


      virtual bool flush() override;

   };


} // namespace draw2d_gdi



