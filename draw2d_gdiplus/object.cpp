#include "framework.h"


namespace draw2d_gdiplus
{


   object::object()
   {
   

   }


   object::~object()
   {
   

   }


#ifdef DEBUG


   void object::dump(dump_context & dumpcontext) const
   {

      ::matter::dump(dumpcontext);

   }


   void object::assert_valid() const
   {
      
      ::matter::assert_valid();

   }


#endif


} // namespace draw2d_gdiplus



