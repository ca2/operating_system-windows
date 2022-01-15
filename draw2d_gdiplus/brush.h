#pragma once


#include "aura/graphics/draw2d/brush.h"


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

      void dump(dump_context & dumpcontext) const override;

#endif

      //virtual void * get_os_data() const;


      virtual void create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      void destroy() override;
      void destroy_os_data() override;

      //bool create_solid(::color::color crColor);
      //bool CreateHatchBrush(i32 nIndex, ::color::color crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * pPackedDIB, UINT nUsage);

      //bool CreateSysColorBrush(i32 nIndex);



   };


} // namespace draw2d_gdiplus


