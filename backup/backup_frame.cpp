#include "framework.h"


namespace backup
{


   frame::frame(::layered * pobjectContext) :
      ::object(pobject),
      production::frame(pobject)
   {

   }


   frame::~frame()
   {

   }


} // namespace backup


