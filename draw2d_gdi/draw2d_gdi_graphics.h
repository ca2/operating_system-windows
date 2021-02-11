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


      graphics(::layered * pobjectContext);
      virtual ~graphics();


      bool attach_hdc(HDC hdc) override;
      HDC detach_hdc() override;

      operator HDC() const;
      HDC get_handle1() const; // Always returns the Output DC
      HDC get_handle2() const; // Always returns the Output DC
      virtual void * get_os_data() const override;
      virtual void * get_os_data_ex(int i) const override;
      virtual HDC get_handle() const;


      ::image_pointer pimage_work(const ::size_i32 & size, bool bReset);
      image fill_image_work(COLORREF clr, const ::size_i32 & size, bool bReset);

      bool internal_fill_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::rectangle_i32 & rectParam, ::draw2d::brush * pbrush);
      bool internal_stroke_path(void (::draw2d_gdi::graphics::* pfnInternalSetPath)(void *), void * pparam, const ::rectangle_i32 & rectParam, ::draw2d::pen * ppen);
      bool internal_fill_and_stroke_path(void(::draw2d_gdi::graphics::* pfnInternalSetPath)(void *),void * pparam, const ::rectangle_i32 & rectParam,::draw2d::brush * pbrush,::draw2d::pen * ppen);

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
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;

      void set_original_object(int iType);

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics_pointer & pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual int SaveDC() override;
      virtual bool RestoreDC(int nSavedDC) override;
      int GetDeviceCaps(int nIndex) override;
      UINT SetBoundsRect(const ::rectangle_i32 & rectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectBounds, UINT flags) override;
      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point_i32 GetBrushOrg() override;
      point_i32 SetBrushOrg(int x, int y) override;
      point_i32 SetBrushOrg(const ::point_i32 & point) override;
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

      virtual void on_select_object(::draw2d::object * pobjectParam);

      bool SelectFont(::write_text::font * pfont) override;



      virtual void select_pen();
      virtual void select_brush();
      virtual void select_font();
      virtual void select_null_pen();
      virtual void select_null_brush();


      // color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette() override;
      void UpdateColors() override;

      // Drawing-Attribute Functions
      COLORREF GetBkColor();
      int GetBkMode();
      int GetPolyFillMode() override;
      int GetROP2() override;
      int GetStretchBltMode() override;
      COLORREF GetTextColor();

      virtual COLORREF SetBkColor(COLORREF crColor);
      int SetBkMode(int nBkMode);
      int SetPolyFillMode(int nPolyFillMode) override;
      int SetROP2(int nDrawMode) override;
      int SetStretchBltMode(int nStretchMode) override;
      virtual COLORREF SetTextColor(COLORREF crColor);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

#if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() override;
      COLORREF SetDCBrushColor(COLORREF crColor) override;

      COLORREF GetDCPenColor() override;
      COLORREF SetDCPenColor(COLORREF crColor) override;

#endif

      // Graphics mode
      int SetGraphicsMode(int iMode) override;
      int GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,u32 iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual int GetMapMode() override;
      virtual point_i32 GetViewportOrg() override;
      virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      virtual point_i32 SetViewportOrg(int x, int y) override;
      virtual point_i32 SetViewportOrg(const ::point_i32 & point) override;
      virtual point_i32 OffsetViewportOrg(int nWidth, int nHeight) override;

      // Viewport Extent
      virtual ::size_i32 GetViewportExt() override;
      virtual ::size_i32 SetViewportExt(int cx, int cy) override;
      virtual ::size_i32 SetViewportExt(const ::size_i32 & size) override;
      virtual ::size_i32 ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      ::point_i32 GetWindowOrg() override;
      ::point_i32 SetWindowOrg(int x, int y) override;
      ::point_i32 SetWindowOrg(const ::point_i32 & point) override;
      ::point_i32 offset_window_org(int nWidth, int nHeight) override;

      // Window extent
      ::size_i32 GetWindowExt() override;
      virtual ::size_i32 set_window_ext(int cx, int cy) override;
      ::size_i32 set_window_ext(const ::size_i32 & size) override;
      virtual ::size_i32 scale_window_ext(int xNum, int xDenom, int yNum, int yDenom) override;

      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints, count nCount = 1) override;
      void DPtoLP(RECT * prectangle) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, count nCount = 1) override;
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
      bool PtVisible(const ::point_i32 & point) override;
      virtual bool RectVisible(const ::rectangle_i32 & rectangle) override;
      int SelectClipRgn(::draw2d::region* pRgn) override;
      int ExcludeClipRect(int x1, int y1, int x2, int y2) override;
      int ExcludeClipRect(const ::rectangle_i32 & rectangle) override;
      int ExcludeUpdateRgn(::user::primitive * pwindow);
      int IntersectClipRect(int x1, int y1, int x2, int y2) override;
      int IntersectClipRect(const ::rectangle_i32 & rectangle) override;
      int OffsetClipRgn(int x, int y) override;
      int OffsetClipRgn(const ::size_i32 & size) override;
      int SelectClipRgn(::draw2d::region* pRgn, int nMode) override;

      // Line-Output Functions
      point_f64 current_position() override;
      using ::draw2d::graphics::move_to;
      bool move_to(const ::point_i32 & lppt) override;
      using ::draw2d::graphics::line_to;
      bool line_to(const ::point_i32 & lppt) override;
      bool Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Arc(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      bool polyline(const POINT* lpPoints,count nCount) override;

      bool AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle) override;
      bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool ArcTo(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      int GetArcDirection() override;
      int SetArcDirection(int nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount) override;
      bool polyline_to(const POINT* lpPoints,count nCount) override;
      bool poly_polyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount) override;

      bool poly_bezier(const POINT* lpPoints,count nCount) override;
      bool poly_bezier_to(const POINT* lpPoints,count nCount) override;



      // Simple Drawing Functions
      bool fill_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::brush* pBrush) override;
      void frame_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::rectangle_i32 & rectangle) override;
      bool DrawIcon(int x, int y, ::draw2d::icon * picon) override;
      bool DrawIcon(const ::point_i32 & point, ::draw2d::icon * picon) override;
      bool DrawIcon(int x, int y, ::draw2d::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, UINT nFlags,
      //               bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, UINT nFlags,
      //               bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      virtual bool draw_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::pen * ppen) override;

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Chord(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      void DrawFocusRect(const ::rectangle_i32 & rectangle) override;

      bool ellipse(const ::rectangle_f64 & rectangle) override;
      bool draw_ellipse(const ::rectangle_f64 & rectangle) override;
      bool fill_ellipse(const ::rectangle_f64 & rectangle) override;

      bool rectangle_i32(const ::rectangle_i32 & rectangle) override;
      bool draw_rectangle(const ::rectangle_i32 & rectangle) override;
      bool fill_rectangle(const ::rectangle_i32 & rectangle) override;

      bool polygon_i32(const POINT * ppoint, count nCount) override;
      bool draw_polygon(const POINT * ppoint,count nCount) override;
      bool fill_polygon(const POINT * ppoint,count nCount) override;

      bool poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool draw_poly_polygon(const POINT * ppoint, const INT * piPolyCount,count nCount) override;
      bool fill_poly_polygon(const POINT * ppoint, const INT * piPolyCount, count nCount) override;

      bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Pie(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;

      bool round_rectangle(const ::rectangle_i32 & rectangle, const ::point_i32 & lppt) override;

      // Bitmap Functions
      bool PatBlt(int x, int y, int nWidth, int nHeight, u32 dwRop) override;
      bool draw(const ::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::point_i32 & lppt, u32 dwRop) override;
      bool StretchBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                      int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, u32 dwRop) override;
      COLORREF GetPixel(int x, int y) override;
      COLORREF GetPixel(const ::point_i32 & point) override;
      COLORREF SetPixel(int x, int y, COLORREF crColor) override;
      COLORREF SetPixel(const ::point_i32 & point, COLORREF crColor) override;
      bool FloodFill(int x, int y, COLORREF crColor) override;
      bool ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType) override;
      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
                   u32 dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask) override;
      bool SetPixelV(int x, int y, COLORREF crColor) override;
      bool SetPixelV(const ::point_i32 & point, COLORREF crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, u32 dwMode) override;
      bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                          UINT clrTransparent) override;
      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/
      bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
                       ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                       double dOpacity) override;

      virtual bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex) override;

      // Text Functions
      virtual bool text_out(double x, double y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(int x, int y, const string & str) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::rectangle_i32 & rectangle, const char * lpszString, count nCount, INT * lpDxWidths) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::rectangle_i32 & rectangle, const string & str, INT * lpDxWidths) override;
      virtual ::size_i32 TabbedTextOut(int x, int y, const char * lpszString, strsize nCount, count nTabPositions, INT * lpnTabStopPositions, i32 nTabOrigin) override;
      virtual ::size_i32 TabbedTextOut(int x, int y, const string & str, count nTabPositions, INT * lpnTabStopPositions, i32 nTabOrigin) override;

      virtual bool draw_text(const char * lpszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual bool draw_text_ex(const char * lpszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;
      virtual bool draw_text_ex(const string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual size_f64 GetTextExtent(const char * lpszString, strsize nCount) override;
      virtual size_f64 GetTextExtent(const string & str) override;
      virtual ::size_i32 GetOutputTextExtent(const char * lpszString,strsize nCount) override;
      virtual ::size_i32 GetOutputTextExtent(const string & str) override;
      virtual ::size_i32 GetTabbedTextExtent(const char * lpszString,strsize nCount, count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::size_i32 GetTabbedTextExtent(const string & str, count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::size_i32 GetOutputTabbedTextExtent(const char * lpszString,strsize nCount, count nTabPositions, INT * lpnTabStopPositions) override;
      virtual ::size_i32 GetOutputTabbedTextExtent(const string & str, count nTabPositions, INT * lpnTabStopPositions) override;
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

      virtual u32 GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, INT * lpnFit, INT * alpDx, __out_opt LPSIZE lpSize) override;
      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE lpSize) override;

#endif



      // Advanced Drawing
      bool DrawEdge(RECT * prectangle, UINT nEdge, UINT nFlags);
      bool DrawFrameControl(RECT * prectangle, UINT nType, UINT nState);

      // Scrolling Functions
      bool ScrollDC(int dx, int dy, const ::rectangle_i32 & lpRectScroll, const ::rectangle_i32 & lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, INT * lpBuffer) override;
      u32 SetMapperFlags(u32 dwFlag) override;
      ::size_i32 GetAspectRatioFilter() override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) override;
      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
      u32 GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm, u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
                            LPABCFLOAT lpABCF) override;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;

      u32 GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, INT * lpBuffer) override;

#endif

      // Printer/Device Escape Functions
      virtual int Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData) override;
      virtual int Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData) override;
      virtual int DrawEscape(int nEscape, int nInputSize, const char * lpszInputData) override;

      // Escape helpers
      virtual int StartDoc(const char * lpszDocName) override;  // old Win3.0 version
      virtual int StartDoc(LPDOCINFOW lpDocInfo) override;
      virtual int StartPage() override;
      virtual int EndPage() override;
      virtual int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int)) override;
      virtual int AbortDoc() override;
      virtual int EndDoc() override;

      // MetaFile Functions
      virtual bool PlayMetaFile(HMETAFILE hMF) override;
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_i32 & lpBounds) override;
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
      int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, count nCount) override;
      bool SelectClipPath(int nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::layered * pobjectContext);
      //void DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_i32 & size,
      //                  const ::rectangle_i32 & rectLast, const ::size_i32 & sizeLast, ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      using ::draw2d::graphics::fill_rectangle;
      void fill_rectangle(const ::rectangle_i32 & rectangle, COLORREF cr) override;

      using ::draw2d::graphics::draw3d_rect;
      void draw3d_rect(const ::rectangle_i32 & rectangle, COLORREF crTopLeft, COLORREF crBottomRight, const ::e_border & eborder = e_border_all) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


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



