#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS font :
      virtual public ::write_text::font
   {
   public:


      font();
      virtual ~font();

#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;

#endif

      virtual bool create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      ::e_status destroy() override;


      Gdiplus::Font * get_gdiplus_font() { return (Gdiplus::Font *) m_osdata[0]; }
      void set_gdiplus_font(Gdiplus::Font * pfont) { m_osdata[0] = pfont; }


      virtual enum_character_set calculate_character_set(::draw2d::graphics * pgraphics);


   };


} // namespace draw2d_gdiplus



