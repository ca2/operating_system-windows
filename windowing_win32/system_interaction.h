#pragma once


namespace windowing_win32
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_WINDOWING_WIN32 system_interaction :
      virtual public ::user::interaction
   {
   public:


      system_interaction();
      virtual ~system_interaction();


      virtual void install_message_routing(::channel * pchannel) override;

      DECL_GEN_SIGNAL(_001OnMessage);
      DECL_GEN_SIGNAL(_001OnDestroy);


      virtual bool DestroyWindow() override;

      virtual bool is_system_message_window() override;


   };


} // namespace windowing_win32



