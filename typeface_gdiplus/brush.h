#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace typeface_gdiplus
{


   class CLASS_DECL_TYPEFACE_GDIPLUS brush : 
      virtual public ::draw2d::brush
   {
   public:


      brush();
      virtual ~brush();


      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace typeface_gdiplus


