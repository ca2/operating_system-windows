#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI font :
      virtual public ::draw2d_gdi::object,
      virtual public ::write_text::font
   {
   public:


      font(::particle * pparticle);
      virtual ~font();


      operator HFONT() const;
      virtual bool GetLogFont(LOGFONTW* pLogFont) override;


      virtual void construct(const ::write_text::font & pfontParam);


      virtual bool CreateFontIndirect(const LOGFONTW* lpLogFont);
      virtual bool CreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, const ::string & lpszFacename);
      virtual bool CreatePointFont(int nPointSize, const ::string & lpszFaceName, const ::draw2d::graphics_pointer & pgraphics = nullptr);
      virtual bool CreatePointFontIndirect(const LOGFONTW* lpLogFont, const ::draw2d::graphics_pointer & pgraphics = nullptr);


      void dump(dump_context & dumpcontext) const override;


      virtual bool create();


   };


} // namespace draw2d_gdi





