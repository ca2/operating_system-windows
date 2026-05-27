#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI pen :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::pen
   {
   public:


      bool        m_bProcess;


      pen(::particle * pparticle);
      virtual ~pen();

      operator HPEN() const;
      ::i32 GetLogPen(LOGPEN* pLogPen);
      ::i32 GetExtLogPen(EXTLOGPEN* pLogPen);


      virtual void construct(::i32 nPenStyle, ::i32 nWidth, ::color::color crColor);
      virtual void construct(::i32 nPenStyle, ::i32 nWidth, const LOGBRUSH* pLogBrush, ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(::i32 nPenStyle, ::i32 nWidth, ::color::color crColor);
      bool CreatePen(::i32 nPenStyle, ::i32 nWidth, const LOGBRUSH* pLogBrush,
                     ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePenIndirect(LPLOGPEN lpLogPen);


      void dump(dump_context & dumpcontext) const override;


      virtual bool create();

   };


} // namespace draw2d_gdi



