#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS brush :
      virtual public ::draw2d::brush
   {
   public:


      //__creatable_from_base(brush, ::draw2d::brush);


      Gdiplus::Brush * m_pbrush;


      brush();
      ~brush() override;

//#ifdef DEBUG
//
//      void dump(dump_context & dumpcontext) const override;
//
//#endif

      //virtual void * get_os_data() const;


      virtual void create(::draw2d::graphics * pgraphics, char iCreate) override;
      void destroy() override;
      void destroy_os_data() override;

      //bool create_solid(::color::color crColor);
      //bool CreateHatchBrush(int nIndex, ::color::color crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * pPackedDIB, UINT nUsage);

      //bool CreateSysColorBrush(int nIndex);



   };


} // namespace draw2d_gdiplus


