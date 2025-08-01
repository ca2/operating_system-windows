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
      unsigned int GetLayout() override;
      unsigned int SetLayout(unsigned int dwLayout) override;


      virtual void set(::draw2d::bitmap* pbitmap) override;

      HDC get_hdc();
      void release_hdc(HDC hdc);


      virtual double get_dpix() override;
      virtual double get_dpiy() override;

      // Constructors
      bool CreateDC(const ::string & pszDriverName, const ::string & pszDeviceName,

                    const scoped_string & strOutput, const void * lpInitData) override;

      bool CreateIC(const ::string & pszDriverName, const ::string & pszDeviceName,

                    const scoped_string & strOutput, const void * lpInitData) override;

      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual int SaveDC() override;
      virtual bool RestoreDC(int nSavedDC) override;
      int GetDeviceCaps(int nIndex) override;
      virtual unsigned int SetBoundsRect(const ::double_rectangle & rectangleBounds, unsigned int flags);
      virtual unsigned int GetBoundsRect(::double_rectangle * rectdBounds, unsigned int flags);

      bool ResetDC(const DEVMODE* pDevMode) override;


      // Drawing-Tool Functions
      double_point GetBrushOrg() override;
      double_point SetBrushOrg(double x, double y) override;
      double_point SetBrushOrg(const ::double_point & point) override;
      //int EnumObjects(int nObjectType, int (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData) override;





      //::color::color GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      int GetPolyFillMode() override;
      int GetROP2() override;
      int GetStretchBltMode() override;

      bool _get(::geometry2d::matrix & matrix) override;
      bool _set(const ::geometry2d::matrix & matrix) override;
      //bool append(const ::geometry2d::matrix & matrix) override;
      //bool prepend(const ::geometry2d::matrix & matrix) override;

      int SetPolyFillMode(int nPolyFillMode) override;
      int SetROP2(int nDrawMode) override;
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
      int SetGraphicsMode(int iMode) override;
      int GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,unsigned int iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual int GetMapMode() override;
      //virtual int_point GetViewportOrg() override;
      virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      //virtual int_point SetViewportOrg(double x, double y) override;
      //virtual int_point SetViewportOrg(const ::int_point & point) override;
      //virtual int_point OffsetViewportOrg(int nWidth, int nHeight) override;

      // Viewport Extent
      virtual double_size GetViewportExt() override;
      virtual double_size SetViewportExt(double cx, double cy) override;
      virtual double_size SetViewportExt(const ::double_size & size) override;
      //virtual int_size ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom) override;

      // Window Origin
      double_point GetWindowOrg() override;
      double_point SetWindowOrg(double x, double y) override;
      double_point SetWindowOrg(const ::double_point & point) override;
      double_point offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      virtual double_size GetWindowExt() override;
      virtual double_size set_window_ext(double cx, double cy) override;
      virtual double_size set_window_ext(const ::double_size & size) override;
      virtual double_size scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      void DPtoLP(::double_point * pPoints,count nCount = 1) override;

      void DPtoLP(::double_rectangle * prectangle) override;

      void DPtoLP(::double_size * pSize) override;

      void LPtoDP(::double_point * pPoints,count nCount = 1) override;

      void LPtoDP(::double_rectangle * prectangle) override;

      void LPtoDP(::double_size * pSize) override;


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::double_size * pSize) override;

      void LPtoHIMETRIC(::double_size * pSize) override;

      void HIMETRICtoDP(::double_size * pSize) override;

      void HIMETRICtoLP(::double_size * pSize) override;


      // Region Functions
      bool fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush) override;
      bool frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      bool invert_region(::draw2d::region* pregion) override;
      bool paint_region(::draw2d::region* pregion) override;

      // Clipping Functions
      virtual int get_clip_box(::double_rectangle * prectangle) override;


      virtual void add_shapes(const shape_array& shapea);
      virtual void reset_clip();
      virtual void intersect_clip(const ::int_rectangle& rectangle);
      virtual void intersect_clip(const ::double_rectangle& rectangle);
      virtual void intersect_clip(const ::oval& oval);
      virtual void intersect_clip(const ::ovald& oval);
      virtual void intersect_clip(const ::int_polygon& int_polygon);
      virtual void intersect_clip(const ::double_polygon& int_polygon);

      //virtual bool PtVisible(double x, double y) override;
      //bool PtVisible(const ::int_point & point) override;
      //virtual bool RectVisible(const int_rectangle & prectangle) override;

      //int SelectClipRgn(::draw2d::region* pRgn) override;
      //int ExcludeClipRect(int x1, int y1, int x2, int y2) override;
      //int ExcludeClipRect(const int_rectangle &  prectangle) override;



//      int ExcludeUpdateRgn(::user::primitive * pwindow) override;
      //int IntersectClipRect(int x1, int y1, int x2, int y2) override;
      //int IntersectClipRect(const int_rectangle &  prectangle) override;

      //int OffsetClipRgn(double x, double y) override;
      //int OffsetClipRgn(const ::int_size & size) override;
      //int SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      double_point current_position() override;
//      int_point move_to(double x, double y) override;
      //    int_point move_to(const ::int_point & point) override;
      using ::draw2d::graphics::line_to;
      virtual bool line_to(double x, double y) override;
      //bool line_to(const ::double_point& point) override;
      //  bool line_to(const ::int_point & point) override;
      virtual bool polyline(const ::double_point * ppoint,count nCount) override;


      using ::draw2d::graphics::Arc;
      //bool Arc(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) override;
      bool Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4) override;

      //bool Arc(int x1,int y1,int x2,int y2, angle start, angle extends) override;
      bool Arc(double x1,double y1,double x2,double y2,angle start, angle extends) override;

      bool AngleArc(double x,double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool ArcTo(const double_rectangle &  prectangle, const double_point & pointStart, const double_point & pointEnd) override;

      //int GetArcDirection() override;
      //int SetArcDirection(int nArcDirection) override;

      virtual bool polydraw(const ::double_point * ppoint, const BYTE* lpTypes, ::collection::count nCount) override;

      virtual bool polyline_to(const ::double_point * ppoint,count nCount) override;

      virtual bool poly_polyline(const ::double_point * ppoint, const int * lpPolyPoints, ::collection::count nCount) override;


      virtual bool poly_bezier(const ::double_point * ppoint, ::collection::count nCount) override;

      virtual bool poly_bezier_to(const ::double_point * ppoint, ::collection::count nCount) override;



      bool frame_rectangle(const ::double_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      bool invert_rectangle(const ::double_rectangle & rectangle) override;
      //bool draw(const ::int_point & point, ::image::icon * picon, const ::int_size & size) override;
      //bool DrawIcon(double x, double y, ::image::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, UINT nFlags,
        //             HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
        //             ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      //bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
        //         int x4, int y4) override;
      bool Chord(const double_rectangle &  prectangle, const double_point & pointStart, const double_point & pointEnd) override;

      void DrawFocusRect(const double_rectangle &  prectangle) override;


      //bool draw_ellipse(int x1, int y1, int x2, int y2) override;
      //bool draw_ellipse(const int_rectangle &  prectangle) override;

      //bool fill_ellipse(int x1, int y1, int x2, int y2) override;
      //bool fill_ellipse(const int_rectangle &  prectangle) override;

      virtual void clear_current_point() override;

      //bool draw_ellipse(double x1,double y1,double x2,double y2) override;
      bool draw_ellipse(const ::double_rectangle & prectangle) override;

      //bool fill_ellipse(double x1,double y1,double x2,double y2) override;
      bool fill_ellipse(const ::double_rectangle & prectangle) override;


      //bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Pie(const double_rectangle &  prectangle, const double_point & pointStart, const double_point & pointEnd) override;


      //bool draw_polygon(const POINT * ppoints, ::collection::count nCount) override;
      bool draw_polygon(const ::double_point * ppoints, ::collection::count nCount) override;
      //bool fill_polygon(const POINT * ppoints, ::collection::count nCount) override;
      bool fill_polygon(const ::double_point * ppoints, ::collection::count nCount) override;
      using ::draw2d::graphics::int_rectangle;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;

      virtual bool int_rectangle(const ::double_rectangle & rectangle) override;
      virtual bool draw_rectangle(const ::double_rectangle & rectangle, ::draw2d::pen * ppen) override;
      virtual bool fill_rectangle(const ::double_rectangle & rectangle, ::draw2d::brush * pbrush) override;

      virtual bool round_rectangle(const ::double_rectangle & rectangle, double dRadius) override;


      using image_drawer::_draw_raw;
      virtual bool _draw_raw(const ::image::image_drawing & imagedrawing) override;
      
      
      //virtual bool _stretch_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource = ::double_rectangle()) override;


      //// Bitmap Functions
      //bool PatBlt(double x, double y, int nWidth, int nHeight, unsigned int dwRop) override;
      //bool BitBltRaw(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //               int xSrc, int ySrc, unsigned int dwRop) override;
      //bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int dwRop) override;


      //bool StretchBltRaw(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int dwRop) override;

      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::double_point & point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::double_point & point, const ::color::color & color) override;
      ::color::color blend_pixel(const ::double_point & point, const ::color::color & color) override;
      //bool FloodFill(double x, double y, const ::color::color & color) override;
      //bool ExtFloodFill(double x, double y, const ::color::color & color, UINT nFillType) override;
      //bool MaskBlt(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //             int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
      //             unsigned int dwRop) override;
      //bool PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,

      //            int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask) override;
      bool SetPixelV(double x, double y, const ::color::color & color) override;
      bool SetPixelV(const ::double_point & point, const ::color::color & color) override;
      //bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
      //                  void * pMesh, ULONG nMeshElements, unsigned int dwMode) override;
      //bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
      //                    ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
      //                    UINT clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual bool TextOutRaw(double x, double y, const block & block);
      virtual bool ExtTextOut(double x, double y, UINT nOptions, const double_rectangle &  prectangle, const ::string & pszString,character_count nCount, LPINT lpDxWidths) override;

      virtual bool ExtTextOut(double x, double y, UINT nOptions, const double_rectangle &  prectangle, const ::scoped_string & scopedstr, LPINT lpDxWidths) override;

      virtual double_size TabbedTextOut(double x, double y, const ::string & pszString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin) override;

      virtual double_size TabbedTextOut(double x, double y, const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions, int nTabOrigin) override;


      //using ::draw2d::graphics::draw;
      //virtual bool draw(const ::int_point & point, ::draw2d::graphics * pgraphicsSrc, const ::int_rectangle & rectangleSource) override;

      virtual bool _001DrawText(const ::scoped_string & scopedstr, double_rectangle & rectangleParam, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false) override;

      //virtual bool draw_text_ex(const ::string & pszString,character_count nCount,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      //virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;


      //virtual bool draw_text_ex(const ::string & pszString,character_count nCount,const ::double_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      virtual bool draw_text_ex(const ::scoped_string & scopedstr,const ::double_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual ::collection::count get_character_extent(::double_array & daLeft, ::double_array& daRight, const ::scoped_string & scopedstr, character_count iStart = 0, character_count iEnd = -1) override;

      virtual double_size get_text_extent(const ::string & pszString, character_count nCount, character_count iIndex) override;

      virtual double_size GetTextBegin(const ::string & pszString, character_count nCount, character_count iIndex) override;

      //virtual double_size get_text_extent(const ::string & pszString, character_count nCount) override;

      virtual double_size get_text_extent(const ::scoped_string & scopedstr) override;
      virtual bool get_text_extent(double_size & size, const ::string & pszString, character_count nCount, character_count iIndex) override;

      virtual bool get_text_extent(double_size & size, const ::string & pszString, character_count nCount) override;

      virtual bool get_text_extent(double_size & size, const ::scoped_string & scopedstr) override;
      virtual double_size GetOutputTextExtent(const ::string & pszString, character_count nCount) override;

      virtual double_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      virtual double_size GetTabbedTextExtent(const ::string & pszString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual double_size GetTabbedTextExtent(const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions) override;

      virtual double_size GetOutputTabbedTextExtent(const ::string & pszString, character_count nCount,count nTabPositions, LPINT lpnTabStopPositions) override;

      virtual double_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr,count nTabPositions, LPINT pnTabStopPositions) override;

      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, double x, double y, int nWidth, int nHeight) override;

      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      //virtual int GetTextFace(count nCount, LPTSTR pszFacename) override;

      virtual int GetTextFace(string & rString) override;
      virtual bool get_text_metrics(::write_text::text_metric * pMetrics) override;

      virtual bool get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount) override;
      //virtual int GetTextCharacterExtra() override;
      //virtual int SetTextCharacterExtra(int nCharExtra) override;

//      virtual unsigned int GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS pResults, unsigned int dwFlags) override;
//
//      virtual unsigned int GetCharacterPlacement(const ::string & pString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;
//
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT pnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
//
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE pSize) override;
//
//
//#endif



      // Advanced Drawing
      //bool DrawEdge(const ::int_rectangle & rectangle,UINT nEdge,UINT nFlags) override;

      //bool DrawFrameControl(const ::int_rectangle & rectangle,UINT nType,UINT nState) override;


//      // Scrolling Functions
//      bool ScrollDC(int dx, int dy, const int_rectangle &  pRectScroll, const int_rectangle &  lpRectClip,
//
//                    ::draw2d::region* pRgnUpdate, RECT * pRectUpdate) override;
//
//
//      // font Functions
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer) override;
//
//      unsigned int SetMapperFlags(unsigned int dwFlag) override;
//      int_size GetAspectRatioFilter() override;
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC pabc) override;
//
//      unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID pData, unsigned int cbData) override;
//
//      int GetKerningPairs(int nPairs, LPKERNINGPAIR pkrnpair) override;
//
//      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW potm) override;
//
//      unsigned int GetGlyphOutline(UINT nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm,
//
//                               unsigned int cbBuffer, LPVOID pBuffer, const MAT2* lpmat2) override;
//
//
//      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
//                            LPABCFLOAT pABCF) override;
//
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
//                        float* pFloatBuffer) override;
//
//
//      unsigned int GetFontLanguageInfo() override;
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
//      virtual int Escape(int nEscape, int nCount, const ::string & pszInData, LPVOID lpOutData) override;
//
//      int Escape(int nEscape, int nInputSize,  const scoped_string & strInputData,int nOutputSize, char * pszOutputData) override;
//
//      int DrawEscape(int nEscape, int nInputSize, const ::string & pszInputData) override;


      // Escape helpers
      int StartDoc(const ::string & pszDocName) override;  // old Win3.0 version

      int StartDoc(LPDOCINFOW pDocInfo) override;

      int StartPage() override;
      int EndPage() override;
      //int SetAbortProc(bool (CALLBACK* pfn)(HDC, int)) override;

      int AbortDoc() override;
      int EndDoc() override;

      // MetaFile Functions
      bool PlayMetaFile(HMETAFILE hMF) override;
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const double_rectangle &  pBounds) override;

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
      int GetPath(::double_point * ppoint, unsigned char * lpTypes,count nCount) override;

      virtual bool SelectClipPath(int nMode) override;

      // Misc helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::particle * pparticle);
      //void DrawDragRect(const int_rectangle &  prectangle, const ::int_size & size,

      //                  const int_rectangle &  pRectLast, const ::int_size & sizeLast,

      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      //void fill_rectangle(const ::int_rectangle & rectangle, const ::color::color & color) override;

      virtual bool fill_rectangle(const ::double_rectangle & rectangle, const ::color::color & color) override;

      //virtual void draw_inset_3d_rectangle(const ::int_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;
      virtual bool draw_inset_3d_rectangle(const ::double_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all) override;

      //virtual bool draw_rectangle(const ::int_rectangle& rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);
      virtual bool draw_rectangle(const double_rectangle& double_rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);

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
      //virtual void * get_os_data_ex(int i) const override;
      //virtual void release_os_data_ex(int i, void *int_point) override;
      virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata) override;


      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::double_rectangle & rectangle) override;


      virtual bool flush() override;
      virtual bool sync_flush() override;

      //virtual bool draw_line(double x1, double y1, double x2, double y2) override;
      virtual bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;

      //virtual bool draw_line(const ::double_point & point1, const ::double_point & point2, ::draw2d::pen * ppen) override;


      virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      virtual bool prefer_mapped_image_on_mix() override;

      virtual bool TextOutAlphaBlend(double x, double y, const block & block) override;

      //virtual bool BitBltAlphaBlend(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, unsigned int dwRop) override;

      virtual int meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles);


   };


} // namespace draw2d_gdiplus



