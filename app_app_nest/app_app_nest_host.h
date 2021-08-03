#pragma once



namespace ca2plugin_container
{

   class application;


   class host : 
      public ::hotplugin::host
   {
   public:

   
      oswindow                                  m_oswindowMessage;
      oswindow                                  m_oswindow;
      bool                                      m_bStream;

      string                                    m_vssPluginName;
      string                                    m_vssPluginDescription;

      ::ca2plugin_container::application *      m_pcontainerapp;


      host(__pointer(::ca2plugin_container::application) papp);
      virtual ~host();

      virtual oswindow get_host_window();
      virtual bool is_ok();
      virtual void post_message(u32 emessage, wparam wparam, lparam lparam);
      

      bool init();
      void shut();

      // host
      virtual bool open_link(const ::string & strLink,const ::string & strTarget);
      virtual bool reload_plugin();


      virtual void install_message_routing(::channel * pchannel);

      void start_plugin();

      bool plugin_finalize();



      void message_handler(::user::message * pusermessage);


      virtual void * get_context_system();
      virtual void set_system(void * pvoidPluginSystem);

      virtual void on_receive(::aura::ipc::rx * prx, i32 message, void * pdata, i32 len);
      virtual bool set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags);

      virtual void start_ca2();

      virtual void restart_aura_ipc();

      virtual void _001OnTimer(::timer * ptimer);

      void _001Print(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace ca2plugin_container



