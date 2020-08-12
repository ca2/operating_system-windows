#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS brush :
      virtual public ::draw2d::brush
   {
   public:


      Gdiplus::Brush * m_pbrush;


      brush();
      virtual ~brush();

#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;

#endif

      //virtual void * get_os_data() const;


      virtual bool create(::draw2d::graphics * pgraphics) override;
      virtual void destroy() override;


      //bool create_solid(COLORREF crColor);
      //bool CreateHatchBrush(i32 nIndex, COLORREF crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * pPackedDIB, UINT nUsage);

      //bool CreateSysColorBrush(i32 nIndex);



   };


} // namespace draw2d_gdiplus


