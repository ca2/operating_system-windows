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

      ::context_object::dump(dumpcontext);

   }


   void object::assert_valid() const
   {
      
      ::context_object::assert_valid();

   }


#endif


} // namespace draw2d_gdiplus



