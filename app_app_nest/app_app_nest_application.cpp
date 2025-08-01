#include "framework.h"


namespace ca2plugin_container
{


   application::application(::plugin::system * psystem, const ::scoped_string & scopedstrChannel) :
      ::object(psystem),
      ::thread(psystem),
      ::aura::application(psystem),
      ::axis::application(psystem),
      ::base::application(psystem),
      ::aura::application(psystem)
   {

      system() = psystem;

      m_strChannel = pszChannel;

//      m_timeRunLock = ::time(884);

   }


   application::~application()
   {

   }


   void application::restart_aura_ipc()
   {

      m_phost->m_strBitmapChannel = m_strChannel;

      string strChannel = "\\aura\\app_app_nest-";

      strChannel += m_strChannel;

      m_phost->::aura::ipc::ipc::open_ba(strChannel, "app_app_nest.exe");

   }

   bool application::initialize_communication()
   {

      restart_aura_ipc();

      m_phost->start_ca2();

      return true;

   }


   bool application::os_native_bergedge_start()
   {

      if (!initialize_communication())
         return false;

      return true;

   }


   void application::on_receive(::aura::ipc::rx * prx, const ::scoped_string & scopedstrMessage)
   {

      __UNREFERENCED_PARAMETER(pszMessage);

   }


   void application::on_receive(::aura::ipc::rx * prx, int message, void * pdata, int len)
   {

      if(m_phost != nullptr)
      {

         m_phost->on_receive(prx, message, pdata, len);

      }

   }


   bool application::destroy()
   {

      return true;

   }


   void     application::run()
   {

      return thread::run();

   }


   ::hotplugin::host * application::create_host()
   {

      m_phost = ___new host(this);

      m_phost->::aura::application::m_psession = m_psession;

      m_phost->get_application() = this;

      return m_phost;

   }


   bool application::on_run_step()
   {

      //if(!::aura::application::on_run_step())
      //{
      //
      //   return false;

      //}

      //if(psystem->install().is_installing_ca2())
      //{

      //   return false;

      //}

      return true;

   }



} // namespace ca2plugin_container












