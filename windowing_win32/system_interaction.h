#pragma once


namespace windowing_win32
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_WINDOWING_WIN32 system_interaction :
      virtual public ::user::interaction
   {
   public:




      system_interaction();
      ~system_interaction() override;


      void install_message_routing(::channel * pchannel) override;


      //DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnMessage);
      DECLARE_MESSAGE_HANDLER(_001OnDeviceChange);
      

      virtual void start_destroying_window() override;

      virtual bool is_system_message_window() override;

      //void initialize_windows_devices();


   };


} // namespace windowing_win32



