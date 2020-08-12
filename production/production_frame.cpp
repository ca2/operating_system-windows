#include "framework.h"


namespace production
{


   frame::frame(::object * pobject) :
      ::object(pobject),
      simple_frame_window(pobject)
   {

   }

   frame::~frame()
   {
   }


   #ifdef DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }


   #endif //DEBUG




   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &frame::_001OnCreate);
   }

   void frame::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }


} // namespace production



