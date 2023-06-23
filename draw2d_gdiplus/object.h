#pragma once


#include "aura/graphics/draw2d/object.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS object :
      virtual public ::draw2d::object
   {
      public:


         object();
         ~object() override;

//#ifdef DEBUG
//         void assert_ok() const override;
//         void dump(dump_context & dumpcontext) const override;
//#endif


   };


} // namespace aura



