#pragma once


namespace ca2plugin_container
{


   class application :
      virtual public ::aura::application,
      virtual public ::hotplugin::composer
   {
   public:


      i32                    m_iReturn;

      string                     m_strChannel;

      host *                     m_phost;

      ::plugin::system *         m_psystem;


      application(::plugin::system * psystem,const char * pszChannel);
      virtual ~application();


      virtual void on_receive(::aura::ipc::rx * prx, const char * pszMessage);

      virtual void on_receive(::aura::ipc::rx * prx, i32 message, void * pdata, i32 len);

      virtual bool initialize_communication();

      virtual bool finalize();

      virtual bool os_native_bergedge_start();

      virtual ::e_status  run() override;

      virtual void restart_aura_ipc();

      virtual ::hotplugin::host * create_host();

      virtual bool on_run_step();


   };



} // namespace ca2plugin_container






