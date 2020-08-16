#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS font :
      virtual public ::draw2d::font
   {
   public:


      Gdiplus::Font *   m_pfont;


      font();
      virtual ~font();

#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;

#endif

      virtual bool create(::draw2d::graphics * pgraphics, ::index iCreate) override;
      virtual void destroy() override;

      virtual bool GetLogFont(LOGFONTW * pfontw) override;

      virtual e_char_set calc_char_set(::draw2d::graphics * pgraphics);


   };


} // namespace draw2d_gdiplus



