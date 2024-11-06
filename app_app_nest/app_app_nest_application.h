#pragma once


namespace ca2plugin_container
{


   class application :
      virtual public ::aura::application,
      virtual public ::hotplugin::composer
   {
   public:


      int                    m_iReturn;

      string                     m_strChannel;

      host *                     m_phost;

      ::plugin::system *         system();


      application(::plugin::system * psystem, const ::string & pszChannel);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual void on_receive(::aura::ipc::rx * prx, const ::string & pszMessage);

      virtual void on_receive(::aura::ipc::rx * prx, int message, void * pdata, int len);

      virtual bool initialize_communication();

      virtual bool destroy();

      virtual bool os_native_bergedge_start();

      virtual void  run() override;

      virtual void restart_aura_ipc();

      virtual ::hotplugin::host * create_host();

      virtual bool on_run_step();


   };



} // namespace ca2plugin_container






