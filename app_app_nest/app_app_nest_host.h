#pragma once



namespace ca2plugin_container
{

   class application;


   class host : 
      public ::hotplugin::host
   {
   public:

   
      oswindow                                  m_oswindowMessage;
      oswindow                                  m_pacmewindowingwindow;
      bool                                      m_bStream;

      string                                    m_vssPluginName;
      string                                    m_vssPluginDescription;

      ::ca2plugin_container::application *      m_pcontainerapp;


      host(::pointer<::ca2plugin_container::application>papp);
      virtual ~host();

      virtual oswindow get_host_window();
      virtual bool is_ok();
      virtual void post_message(unsigned int emessage, wparam wparam, lparam lparam);
      

      bool init();
      void shut();

      // host
      virtual bool open_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrTarget);
      virtual bool reload_plugin();


      void install_message_routing(::channel * pchannel) override;

      void start_plugin();

      bool plugin_finalize();



      void message_handler(::user::message * pusermessage);


      virtual void * get_context_system();
      virtual void set_system(void * pvoidPluginSystem);

      virtual void on_receive(::aura::ipc::rx * prx, int message, void * pdata, int len);
      virtual bool set_window_position(iptr z,int x,int y,int cx,int cy,UINT nFlags);

      virtual void start_ca2();

      virtual void restart_aura_ipc();

      virtual void on_timer(::timer * ptimer);

      void _001Print(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace ca2plugin_container



