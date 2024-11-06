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

      /*virtual void construct(int nPenStyle, double nWidth, ::color::color crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* pStyle = nullptr);

      bool CreatePen(int nPenStyle, double nWidth, ::color::color crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* pStyle = nullptr);*/



      virtual bool create(::draw2d::graphics * pgraphics, char iCreate) override;
      virtual void destroy() override;



   };


} // namespace draw2d_gdiplus


