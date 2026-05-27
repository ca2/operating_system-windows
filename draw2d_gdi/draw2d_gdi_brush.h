#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI brush :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::brush
   {
   public:

      bool m_bProcess;

      // Constructors
      brush(::particle * pparticle);
      virtual ~brush();


      operator HBRUSH() const;
      ::i32 GetLogBrush(LOGBRUSH* pLogBrush);


      virtual void construct(::color::color crColor);                // CreateSolidBrush
      virtual void construct(::i32 nIndex, ::color::color crColor);    // CreateHatchBrush
      virtual void construct(::draw2d::bitmap * pbitmap);                // CreatePatternBrush


      bool CreateSolid(::color::color crColor);
      bool CreateHatchBrush(::i32 nIndex, ::color::color crColor);
      bool CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      bool CreateSysColorBrush(::i32 nIndex);


      void dump(dump_context & dumpcontext) const override;


      virtual bool create();

   };


} // namespace draw2d_gdi




