#include "framework.h"


namespace production
{


   frame::frame(::particle * pparticle) :
      ::object(pobject),
      simple_frame_window(pobject)
   {

   }

   frame::~frame()
   {
   }


   #ifdef DEBUG
   void frame::assert_ok() const
   {
	   simple_frame_window::assert_ok();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }


   #endif //DEBUG




   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &frame::_001OnCreate);
   }

   void frame::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }


} // namespace production



