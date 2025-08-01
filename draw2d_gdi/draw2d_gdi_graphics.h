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
      virtual void * get_os_data_ex(int i) const override;
      virtual HDC get_handle() const;


      ::image::image_pointer pimage_work(const ::int_size & size, bool bReset);
      image fill_image_work(::color::color clr, const ::int_size & size, bool bReset);

      bool internal_fill_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::int_rectangle & rectangleParam, ::draw2d::brush * pbrush);
      bool internal_stroke_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::int_rectangle & rectangleParam, ::draw2d::pen * ppen);
      bool internal_fill_and_stroke_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam, const ::int_rectangle & rectangleParam,::draw2d::brush * pbrush,::draw2d::pen * ppen);

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
      unsigned int GetLayout() override;
      unsigned int SetLayout(unsigned int dwLayout) override;

      void set_original_object(int iType);

      // Constructors
      bool CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      bool CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics_pointer & pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual int SaveDC() override;
      virtual bool RestoreDC(int nSavedDC) override;
      int GetDeviceCaps(int nIndex) override;
      UINT SetBoundsRect(const ::int_rectangle & rectangleBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectangleBounds, UINT flags) override;
      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      int_point GetBrushOrg() override;
      int_point SetBrushOrg(int x, int y) override;
      int_point SetBrushOrg(const ::int_point & point) override;
      int EnumObjects(int nObjectType,
                      int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      //virtual ::draw2d::object* SelectStockObject(int nIndex) override;
      virtual ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
      virtual ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
      virtual ::write_text::font* SelectObject(::write_text::font* pFont) override;
      virtual ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap) override;
      virtual int SelectObject(::draw2d::region* pRgn) override;       // special return for regions

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
      int GetBkMode();
      int GetPolyFillMode() override;
      int GetROP2() override;
      int GetStretchBltMode() override;
      ::color::color GetTextColor();

      virtual ::color::color SetBkColor(::color::color crColor);
      int SetBkMode(int nBkMode);
      int SetPolyFillMode(int nPolyFillMode) override;
      int SetROP2(int nDrawMode) override;
      int SetStretchBltMode(int nStretchMode) override;
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
      int SetGraphicsMode(int iMode) override;
      int GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,unsigned int iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual int GetMapMode() override;
      virtual int_point GetViewportOrg() override;
      virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      virtual int_point SetViewportOrg(int x, int y) override;
      virtual int_point SetViewportOrg(const ::int_point & point) override;
      virtual int_point OffsetViewportOrg(int nWidth, int nHeight) override;

      // Viewport Extent
      virtual ::int_size GetViewportExt() override;
      virtual ::int_size SetViewportExt(int cx, int cy) override;
      virtual ::int_size SetViewportExt(const ::int_size & size) override;
      virtual ::int_size ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      ::int_point GetWindowOrg() override;
      ::int_point SetWindowOrg(int x, int y) override;
      ::int_point SetWindowOrg(const ::int_point & point) override;
      ::int_point offset_window_org(int nWidth, int nHeight) override;

      // Window extent
      ::int_size GetWindowExt() override;
      virtual ::int_size set_window_ext(int cx, int cy) override;
      ::int_size set_window_ext(const ::int_size & size) override;
      virtual ::int_size scale_window_ext(int xNum, int xDenom, int yNum, int yDenom) override;

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
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual int get_clip_box(RECT * prectangle) override;
      virtual bool PtVisible(int x, int y) override;
      bool PtVisible(const ::int_point & point) override;
      virtual bool RectVisible(const ::int_rectangle & rectangle) override;
      int SelectClipRgn(::draw2d::region* pRgn) override;
      int ExcludeClipRect(int x1, int y1, int x2, int y2) override;
      int ExcludeClipRect(const ::int_rectangle & rectangle) override;
      int ExcludeUpdateRgn(::user::primitive * pwindow);
      int IntersectClipRect(int x1, int y1, int x2, int y2) override;
      int IntersectClipRect(const ::int_rectangle & rectangle) override;
      int OffsetClipRgn(int x, int y) override;
      int OffsetClipRgn(const ::int_size & size) override;
      int SelectClipRgn(::draw2d::region* pRgn, int nMode) override;

      // Line-Output Functions
      double_point current_position() override;
      using ::draw2d::graphics::move_to;
      bool move_to(const ::int_point & lppt) override;
      using ::draw2d::graphics::line_to;
      bool line_to(const ::int_point & lppt) override;
      bool Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Arc(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd) override;
      bool polyline(const POINT* lpPoints,count nCount) override;

      bool AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle) override;
      bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool ArcTo(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd) override;
      int GetArcDirection() override;
      int SetArcDirection(int nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount) override;
      bool polyline_to(const POINT* lpPoints,count nCount) override;
      bool poly_polyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount) override;

      bool poly_bezier(const POINT* lpPoints,count nCount) override;
      bool poly_bezier_to(const POINT* lpPoints,count nCount) override;



      // Simple Drawing Functions
      bool fill_rectangle(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void frame_rectangle(const ::int_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::int_rectangle & rectangle) override;
      bool DrawIcon(int x, int y, ::image::icon * picon) override;
      bool DrawIcon(const ::int_point & point, ::image::icon * picon) override;
      bool DrawIcon(int x, int y, ::image::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, const ::scoped_string & scopedstrText, UINT nFlags,
      //               bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, const ::scoped_string & scopedstrText, UINT nFlags,
      //               bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      virtual bool draw_rectangle(const ::int_rectangle & rectangle, ::draw2d::pen * ppen) override;

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Chord(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd) override;
      void DrawFocusRect(const ::int_rectangle & rectangle) override;

      bool ellipse(const ::double_rectangle & rectangle) override;
      bool draw_ellipse(const ::double_rectangle & rectangle) override;
      bool fill_ellipse(const ::double_rectangle & rectangle) override;

      bool int_rectangle(const ::int_rectangle & rectangle) override;
      bool draw_rectangle(const ::int_rectangle & rectangle) override;
      bool fill_rectangle(const ::int_rectangle & rectangle) override;

      bool int_polygon(const POINT * ppoint, ::collection::count nCount) override;
      bool draw_polygon(const POINT * ppoint,count nCount) override;
      bool fill_polygon(const POINT * ppoint,count nCount) override;

      bool poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool draw_poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool fill_poly_polygon(const POINT * ppoint, const INT * piPolyCount, ::collection::count nCount) override;

      bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Pie(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd) override;

      bool round_rectangle(const ::int_rectangle & rectangle, const ::int_point & lppt) override;

      // Bitmap Functions
      bool PatBlt(int x, int y, int nWidth, int nHeight, unsigned int dwRop) override;
      bool draw(const ::int_rectangle & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::int_point & lppt, unsigned int dwRop) override;
      bool StretchBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                      int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int dwRop) override;
      ::color::color GetPixel(int x, int y) override;
      ::color::color GetPixel(const ::int_point & point) override;
      ::color::color SetPixel(int x, int y, ::color::color crColor) override;
      ::color::color SetPixel(const ::int_point & point, ::color::color crColor) override;
      bool FloodFill(int x, int y, ::color::color crColor) override;
      bool ExtFloodFill(int x, int y, ::color::color crColor, UINT nFillType) override;
      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
                   unsigned int dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask) override;
      bool SetPixelV(int x, int y, ::color::color crColor) override;
      bool SetPixelV(const ::int_point & point, ::color::color crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, unsigned int dwMode) override;
      bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                          UINT clrTransparent) override;
      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/
      bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
                       ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                       double dOpacity) override;

      virtual bool get_text_extent(double_size & size, const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex) override;

      // Text Functions
      virtual bool text_out(double x, double y, const ::scoped_string & scopedstrString, character_count nCount) override;
      virtual bool text_out(int x, int y, const ::scoped_string & scopedstr) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::int_rectangle & rectangle, const ::scoped_string & scopedstrString, ::collection::count nCount, INT * lpDxWidths) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::int_rectangle & rectangle, const ::scoped_string & scopedstr, INT * lpDxWidths) override;
      virtual ::int_size TabbedTextOut(int x, int y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions, int nTabOrigin) override;
      virtual ::int_size TabbedTextOut(int x, int y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions, int nTabOrigin) override;

      virtual bool draw_text(const ::scoped_string & scopedstrString,character_count nCount,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const ::scoped_string & scopedstr,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual bool draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;
      virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual double_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount) override;
      virtual double_size get_text_extent(const ::scoped_string & scopedstr) override;
      virtual ::int_size GetOutputTextExtent(const ::scoped_string & scopedstrString,character_count nCount) override;
      virtual ::int_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      virtual ::int_size GetTabbedTextExtent(const ::scoped_string & scopedstrString,character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::int_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::int_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString,character_count nCount, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::int_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, INT * lpnTabStopPositions) override;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight) override;
      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      virtual int GetTextFace(count nCount, LPTSTR lpszFacename) override;
      virtual int GetTextFace(string & rString) override;

      virtual bool get_text_metrics(::write_text::text_metric * lpMetrics) override;
      virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics) override;

      virtual int SetTextJustification(int nBreakExtra, int nBreakCount) override;
      virtual int GetTextCharacterExtra() override;
      virtual int SetTextCharacterExtra(int nCharExtra) override;

      virtual unsigned int GetCharacterPlacement(const ::string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;
      virtual unsigned int GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, INT * lpnFit, INT * alpDx, __out_opt LPSIZE lpSize) override;
      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE lpSize) override;

#endif



      // Advanced Drawing
      bool DrawEdge(RECT * prectangle, UINT nEdge, UINT nFlags);
      bool DrawFrameControl(RECT * prectangle, UINT nType, UINT nState);

      // Scrolling Functions
      bool ScrollDC(int dx, int dy, const ::int_rectangle & lpRectScroll, const ::int_rectangle & lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      unsigned int SetMapperFlags(unsigned int dwFlag) override;
      ::int_size GetAspectRatioFilter() override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
      unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData, unsigned int cbData) override;
      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) override;
      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
      unsigned int GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm, unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
                            LPABCFLOAT lpABCF) override;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;

      unsigned int GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, INT * lpBuffer) override;

#endif

      // Printer/Device Escape Functions
      virtual int Escape(int nEscape, int nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData) override;
      virtual int Escape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData, int nOutputSize, char * lpszOutputData) override;
      virtual int DrawEscape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData) override;

      // Escape helpers
      virtual int StartDoc(const ::scoped_string & scopedstrDocName) override;  // old Win3.0 version
      virtual int StartDoc(LPDOCINFOW lpDocInfo) override;
      virtual int StartPage() override;
      virtual int EndPage() override;
      virtual int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int)) override;
      virtual int AbortDoc() override;
      virtual int EndDoc() override;

      // MetaFile Functions
      virtual bool PlayMetaFile(HMETAFILE hMF) override;
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::int_rectangle & lpBounds) override;
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
      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, ::collection::count nCount) override;
      bool SelectClipPath(int nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::particle * pparticle);
      //void DrawDragRect(const ::int_rectangle & rectangle, const ::int_size & size,
      //                  const ::int_rectangle & rectangleLast, const ::int_size & sizeLast, ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      using ::draw2d::graphics::fill_rectangle;
      void fill_rectangle(const ::int_rectangle & rectangle, ::color::color color32) override;

      using ::draw2d::graphics::draw_inset_3d_rectangle;
      void draw_inset_3d_rectangle(const ::int_rectangle & rectangle, ::color::color crTopLeft, ::color::color crBottomRight, const ::e_border & eborder = e_border_all) override;

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



