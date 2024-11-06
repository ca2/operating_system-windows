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

//      ::windowing::window * GetWindow() override;

      virtual void attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      virtual void * detach() override;

      //void attach_hdc(HDC hdc) override;   // attach/detach affects only the Output DC
      //virtual HDC detach_hdc() override;
      //void AttachPrinter(HDC hdc) override;
      //virtual HDC DetachPrinter() override;


      //bool IsPrinting() override;            // true if being used for printing


      // for bidi and mirrored localization
      unsigned int GetLayout() override;
      unsigned int SetLayout(unsigned int dwLayout) override;


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
      int save_graphics_context() override;
      void restore_graphics_context(int nSavedContext) override;
      int GetDeviceCaps(int nIndex) override;
      virtual unsigned int SetBoundsRect(const ::rectangle_f64 & rectangleBounds, unsigned int flags);
      virtual unsigned int GetBoundsRect(::rectangle_f64 * rectdBounds, unsigned int flags);

      //bool ResetDC(const DEVMODE* pDevMode) override;


      // Drawing-Tool Functions
      point_f64 GetBrushOrg() override;
      point_f64 SetBrushOrg(double x, double y) override;
      point_f64 SetBrushOrg(const ::point_f64 & point) override;
      //int EnumObjects(int nObjectType, int (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData) override;





      //::color::color GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      //int GetPolyFillMode() override;
      //int GetROP2() override;
      //int GetStretchBltMode() override;

      void _get(::geometry2d::matrix & matrix) override;
      void _set(const ::geometry2d::matrix & matrix) override;
      //bool append(const ::geometry2d::matrix & matrix) override;
      //bool prepend(const ::geometry2d::matrix & matrix) override;

      //int SetPolyFillMode(int nPolyFillMode) override;
      //int SetROP2(int nDrawMode) override;
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
      //int SetGraphicsMode(int iMode) override;
      //int GetGraphicsMode() override;

      // World transform
      //bool SetWorldTransform(const XFORM* pXform) override;
      //bool ModifyWorldTransform(const XFORM* pXform,unsigned int iMode) override;
      //bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      //virtual int GetMapMode() override;
      //virtual point_i32 GetViewportOrg() override;
      //virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      //virtual point_i32 SetViewportOrg(double x, double y) override;
      //virtual point_i32 SetViewportOrg(const ::point_i32 & point) override;
      //virtual point_i32 OffsetViewportOrg(int nWidth, int nHeight) override;

      // Viewport Extent
      size_f64 get_extents() override;
      size_f64 set_extents(double cx, double cy) override;
      size_f64 set_extents(const ::size_f64 & size) override;
      //virtual size_i32 ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom) override;

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
      int get_clip_box(::rectangle_f64 & rectangle) override;


      //void add_clipping_shapes(const shape_array<::draw2d::region>& shapea) override;
      void reset_clip() override;
      void _intersect_clip() override;
      void _add_shape(const ::rectangle_f64 & rectangle) override;
      void _add_shape(const ::ellipse_f64 & ellipse) override;
      void _add_shape(const ::polygon_f64 & polygon) override;


      virtual void intersect_clip(const ::draw2d::clip_group & clipgroup);
      virtual void _add_clip_item(::draw2d::clip_item * pclipitem);



      virtual void _add_clip_item(Gdiplus::GraphicsPath * ppath, ::draw2d::clip_item * pclipitem);
      virtual void _add_shape(Gdiplus::GraphicsPath * ppath, const ::rectangle_f64 & rectangle);
      virtual void _add_shape(Gdiplus::GraphicsPath * ppath, const ::ellipse_f64 & ellipse);
      virtual void _add_shape(Gdiplus::GraphicsPath * ppath, const ::polygon_f64 & polygon);


      void intersect_clip(const ::rectangle_f64 & rectangle) override;
      void intersect_clip(const ::ellipse_f64 & rectangle) override;
      void intersect_clip(const ::polygon_f64 & rectangle) override;

      virtual void set_clipping(::draw2d::region* pregion);

      //void PtVisible(double x, double y) override;
      //bool PtVisible(const ::point_i32 & point) override;
      //void RectVisible(const rectangle_i32 & prectangle) override;

      //int SelectClipRgn(::draw2d::region* pRgn) override;
      //int ExcludeClipRect(int x1, int y1, int x2, int y2) override;
      //int ExcludeClipRect(const rectangle_i32 &  prectangle) override;



//      int ExcludeUpdateRgn(::user::primitive * pwindow) override;
      //int IntersectClipRect(int x1, int y1, int x2, int y2) override;
      //int IntersectClipRect(const rectangle_i32 &  prectangle) override;

      //int OffsetClipRgn(double x, double y) override;
      //int OffsetClipRgn(const ::size_i32 & size) override;
      //int SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      point_f64 current_position() override;
//      point_i32 move_to(double x, double y) override;
      //    point_i32 move_to(const ::point_i32 & point) override;
      using ::draw2d::graphics::line_to;
      virtual void line_to(double x, double y) override;
      //bool line_to(const ::point_f64& point) override;
      //  bool line_to(const ::point_i32 & point) override;
      virtual void polyline(const ::point_f64 * ppoint, ::collection::count nCount) override;


      using ::draw2d::graphics::arc;
      //bool arc(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) override;
      void arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4) override;

      //bool arc(int x1,int y1,int x2,int y2, angle start, angle extends) override;
      void arc(double x1,double y1,double x2,double y2, ::angle_f64 start, ::angle_f64 extends) override;

      void angle_arc(double x,double y, double nRadius, ::angle_f64 fStartAngle, ::angle_f64 fSweepAngle) override;
      //bool arc_to(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      void arc_to(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      //int GetArcDirection() override;
      //int SetArcDirection(int nArcDirection) override;

      virtual void polydraw(const ::point_f64 * ppoint, const BYTE* lpTypes, ::collection::count nCount) override;

      virtual void polyline_to(const ::point_f64 * ppoint, ::collection::count nCount) override;

      virtual void poly_polyline(const ::point_f64 * ppoint, const int * lpPolyPoints, ::collection::count nCount) override;


      virtual void poly_bezier(const ::point_f64 * ppoint, ::collection::count nCount) override;

      virtual void poly_bezier_to(const ::point_f64 * ppoint, ::collection::count nCount) override;



      void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::rectangle_f64 & rectangle) override;
      //bool draw(const ::point_i32 & point, ::image::icon * picon, const ::size_i32 & size) override;
      //bool DrawIcon(double x, double y, ::image::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, UINT nFlags,
        //             HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
        //             ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, UINT nFlags,
      //               ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & pszText, UINT nFlags,

      //               bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC pDrawProc,

      //               LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      //bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
        //         int x4, int y4) override;
      void Chord(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;

      void DrawFocusRect(const rectangle_f64 &  prectangle) override;


      //bool draw_ellipse(int x1, int y1, int x2, int y2) override;
      //bool draw_ellipse(const rectangle_i32 &  prectangle) override;

      //bool fill_ellipse(int x1, int y1, int x2, int y2) override;
      //bool fill_ellipse(const rectangle_i32 &  prectangle) override;

      virtual void clear_current_point() override;

      //bool draw_ellipse(double x1,double y1,double x2,double y2) override;
      void draw_ellipse(const ::rectangle_f64 & prectangle) override;

      //bool fill_ellipse(double x1,double y1,double x2,double y2) override;
      void fill_ellipse(const ::rectangle_f64 & prectangle) override;


      //bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      void Pie(const rectangle_f64 &  prectangle, const point_f64 & pointStart, const point_f64 & pointEnd) override;


      //bool draw_polygon(const POINT * ppoints, ::collection::count nCount) override;
      void draw_polygon(const ::point_f64 * ppoints, ::collection::count nCount) override;
      //bool fill_polygon(const POINT * ppoints, ::collection::count nCount) override;
      void fill_polygon(const ::point_f64 * ppoints, ::collection::count nCount) override;
      using ::draw2d::graphics::rectangle;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;

      virtual void rectangle(const ::rectangle_f64 & rectangle) override;
      virtual void draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen) override;
      virtual void fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush) override;

      void round_rectangle(const ::rectangle_f64 & rectangle, double dRadius) override;


      using image_drawer::_draw_raw;
      void _draw_raw(const ::image::image_drawing & imagedrawing) override;
      
      
      //void _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64()) override;


      //// Bitmap Functions
      //bool PatBlt(double x, double y, int nWidth, int nHeight, unsigned int dwRop) override;
      //bool BitBltRaw(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //               int xSrc, int ySrc, unsigned int dwRop) override;
      //bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int dwRop) override;


      //bool StretchBltRaw(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                   int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, unsigned int dwRop) override;

      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::point_f64 & point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::point_f64 & point, const ::color::color & color) override;
      ::color::color blend_pixel(const ::point_f64 & point, const ::color::color & color) override;
      //bool FloodFill(double x, double y, const ::color::color & color) override;
      //bool ExtFloodFill(double x, double y, const ::color::color & color, UINT nFillType) override;
      //bool MaskBlt(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //             int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
      //             unsigned int dwRop) override;
      //bool PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,

      //            int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask) override;
      //void SetPixelV(double x, double y, const ::color::color & color) override;
      //void SetPixelV(const ::point_f64 & point, const ::color::color & color) override;
      //bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
      //                  void * pMesh, ULONG nMeshElements, unsigned int dwMode) override;
      //bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
      //                    ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
      //                    UINT clrTransparent) override;

      //void _alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual void TextOutRaw(double x, double y, const ::scoped_string & scopedstr);
      //void ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & pszString,strsize nCount, LPINT lpDxWidths) override;

      //void ExtTextOut(double x, double y, UINT nOptions, const rectangle_f64 &  prectangle, const ::string & str, LPINT lpDxWidths) override;

      //virtual size_f64 TabbedTextOut(double x, double y, const ::string & pszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin) override;

      //virtual size_f64 TabbedTextOut(double x, double y, const ::string & str,count nTabPositions, LPINT pnTabStopPositions, int nTabOrigin) override;


      //using ::draw2d::graphics::draw;
      //void draw(const ::point_i32 & point, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_i32 & rectangleSource) override;

      void _001DrawText(const ::string & str, rectangle_f64 & rectangleParam, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false) override;

      //void draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      //void draw_text_ex(const ::string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;


      //void draw_text_ex(const ::string & pszString,strsize nCount,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams) override;

      void draw_text_ex(const ::string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual ::collection::count get_character_extent(::f64_array & daLeft, ::f64_array& daRight, const ::string & str, strsize iStart = 0, strsize iEnd = -1) override;

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

      //void GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, double x, double y, int nWidth, int nHeight) override;

      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      //virtual int GetTextFace(count nCount, LPTSTR pszFacename) override;

      //virtual int GetTextFace(string & rString) override;
      virtual void get_text_metrics(::write_text::text_metric * pMetrics) override;

      void get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount) override;
      //virtual int GetTextCharacterExtra() override;
      //virtual int SetTextCharacterExtra(int nCharExtra) override;

//      virtual unsigned int GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS pResults, unsigned int dwFlags) override;
//
//      virtual unsigned int GetCharacterPlacement(const ::string & pString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;
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
      //bool DrawEdge(const ::rectangle_i32 & rectangle,UINT nEdge,UINT nFlags) override;

      //bool DrawFrameControl(const ::rectangle_i32 & rectangle,UINT nType,UINT nState) override;


//      // Scrolling Functions
//      bool ScrollDC(int dx, int dy, const rectangle_i32 &  pRectScroll, const rectangle_i32 &  lpRectClip,
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
//      size_i32 GetAspectRatioFilter() override;
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
      //int StartDoc(const ::string & pszDocName) override;  // old Win3.0 version

      //int StartDoc(LPDOCINFOW pDocInfo) override;

      int StartPage() override;
      int EndPage() override;
      //int SetAbortProc(bool (CALLBACK* pfn)(HDC, int)) override;

      int AbortDoc() override;
      int EndDoc() override;

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
      //int GetPath(::point_f64 * ppoint, unsigned char * lpTypes,count nCount) override;

      void SelectClipPath(int nMode) override;

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

      //using ::draw2d::graphics::get_os_data;
      virtual Gdiplus::Region * defer_update_os_data(::pointer < ::geometry2d::region > & pregion);


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

      //void BitBltAlphaBlend(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, unsigned int dwRop) override;

      virtual int meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles);


      void _gdiplus_draw_text(::draw2d::path * ppathParam, const string & str, rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfontParam, double dFontWidth, ::draw2d::brush * pbrushParam = nullptr, bool bMeasure = false);


   };


} // namespace draw2d_gdiplus



