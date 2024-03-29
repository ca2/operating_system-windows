#pragma once

namespace production
{

   class CLASS_DECL_CA2_PRODUCTION frame : 
      public simple_frame_window
   {
   public:
	   frame(::particle * pparticle);
   public:
	   virtual ~frame();
   #ifdef DEBUG
	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;
   #endif

      void install_message_routing(::channel * pchannel);

      DECLARE_MESSAGE_HANDLER(_001OnCreate);
   };

} // namespace production
