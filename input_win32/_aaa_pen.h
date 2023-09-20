#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS pen :
      virtual public ::draw2d_gdiplus::object,
      virtual public ::draw2d::pen
   {
   public:


      Gdiplus::PenAlignment m_egdiplusalign;

      ::Gdiplus::Pen *  m_ppen;

      pen();
      virtual ~pen();


#ifdef DEBUG

      void dump(dump_context & dumpcontext) const override;

#endif

      /*virtual void construct(i32 nPenStyle, double nWidth, ::color::color crColor);
      virtual void construct(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* pStyle = nullptr);

      bool CreatePen(i32 nPenStyle, double nWidth, ::color::color crColor);
      bool CreatePen(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* pStyle = nullptr);*/



      virtual bool create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      virtual void destroy() override;



   };


} // namespace draw2d_gdiplus


