#include "framework.h"
#include "service_handler.h"
#include "acme/exception/exception.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"
#include "apex/platform/system.h"


#ifdef WINDOWS
unsigned int Win32FromHResult(HRESULT value);
#endif


namespace apex_windows
{


   service_handler * service_handler::s_pservicehandler = nullptr;


   service_handler::service_handler(unsigned int controlsAccepted) :
      m_handle(0)
   {

      s_pservicehandler = this;

      m_dwStopTimeout = 30 * 1000; // 30 seconds

   #ifdef WINDOWS_DESKTOP
      m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
      m_status.dwCurrentState = SERVICE_START_PENDING;
      m_status.dwControlsAccepted = controlsAccepted;
   #endif

   }


   service_handler::~service_handler()
   {

   }


   void service_handler::control_start(unsigned int u)
   {

      queue_user_work_item();

   }


   void service_handler::_server()
   {


#ifdef WINDOWS_DESKTOP


      SERVICE_TABLE_ENTRYW serviceTable[] =
      {

         // Even though the service name is ignored for own process services,
         // it must be a valid string and cannot be 0.
         { (WCHAR *)L"", ServiceMain },

         // Designates the end of table.
         { 0, 0 }

      };

      if (!::StartServiceCtrlDispatcherW(serviceTable))
      {

         throw ::exception(error_failed);

      }

#endif

   }




   //*****************************************************************************
   //
   //      Name:           SetServiceStatus
   //      Description:    Wrapper for the SetServiceStatus SCM function.
   //
   //*****************************************************************************
   void service_handler::SetServiceStatus()
   {

      // If m_service is zero it means we're not running as a service but
      // rather from the console. This is possible in debug mode.

      if (::is_null(s_pservicehandler))
      {

         return;

      }

#ifdef WINDOWS_DESKTOP

      if (!::SetServiceStatus(m_handle, &m_status))
      {

         DWORD dwLastError = ::GetLastError();

         throw ::exception(error_failed);

      }

#endif

   }


   void service_handler::queue_user_work_item(ULONG flags)
   {

      if (::QueueUserWorkItem(thread_proc, this, flags))
      {

         throw ::exception(error_failed);

      }

      fork([this]()
         {

            run();

         });

      //return ::success;

   }


   void service_handler::serve(service * pservice)
   {

      ASSERT(0 == s_pservicehandler);

      s_pservicehandler->m_pservice = pservice;

      s_pservicehandler->run();

   }


   void service_handler::control_stop(unsigned int u)
   {

      s_pservicehandler->stop_service();
      //s_pservicehandler->m_ = e_service_status_stopping;

      //s_pservicehandler->m_stopped.wait(::time((unsigned int)m_dwStopTimeout));

   }


   DWORD WINAPI service_handler::thread_proc(void * pcontext)
   {

      service * pservice = (service *)pcontext;
      
      ::e_status estatus = ::success;

      try
      {

         pservice->run();

      }
      catch (...)
      {

      }

      return (DWORD) estatus.as_huge_integer();

   }


   //*****************************************************************************
   //
   //      Name:           ServiceMain
   //      Description:    The starting point for the service.
   //
   //*****************************************************************************
   void WINAPI service_handler::ServiceMain(DWORD argumentCount, PWSTR * arguments)
   {

      // Since there's no way to inform the SCM of failure before a successful
      // call to RegisterServiceCtrlHandler, if an error occurs before we have
      // a service status handle we don't catch any exceptions and let the
      // process terminate. The SCM will diligently log this event.
      //

      ASSERT(s_pservicehandler != nullptr);

      s_pservicehandler->m_pservice->set_arguments(argumentCount, arguments);

      s_pservicehandler->run();

   }


   //*****************************************************************************
   //
   //      Name:           Handler
   //      Description:    The handler function called by the control dispatcher
   //                      when an event occurs.
   //
   //*****************************************************************************
   void WINAPI service_handler::ServiceHandler(DWORD control)
   {

      try
      {

         switch (control)
         {
         case SERVICE_CONTROL_CONTINUE:
         {

            s_pservicehandler->update_state(SERVICE_CONTINUE_PENDING);
            s_pservicehandler->control_start(control);
            s_pservicehandler->update_state(SERVICE_RUNNING);

            break;

         }
         case SERVICE_CONTROL_PAUSE:
         {

            s_pservicehandler->update_state(SERVICE_PAUSE_PENDING);
            s_pservicehandler->control_stop(control);
            s_pservicehandler->update_state(SERVICE_PAUSED);

            break;

         }
         case SERVICE_CONTROL_SHUTDOWN:
         case SERVICE_CONTROL_STOP:
         {

            s_pservicehandler->update_state(SERVICE_STOP_PENDING);
            s_pservicehandler->control_stop(control);
            s_pservicehandler->update_state(SERVICE_STOPPED);

            auto psystem = s_pservicehandler->system();

            psystem->set_finish();

            break;

         }
         default:
            break;
         }

      }
      catch (const ::exception & e)
      {

         HRESULT hresult = S_OK;

         if (e.m_errorcodea.has_element() && e.m_errorcodea.first().m_etype == e_error_code_type_hresult)
         {

            hresult = (HRESULT) e.m_errorcodea.first().m_iOsError;

         }

         s_pservicehandler->update_state(SERVICE_STOPPED, hresult);

      }

   }


   void service_handler::_main_server(unsigned int argumentCount, PWSTR * arguments)
   {

      if (1 != argumentCount || 0 == arguments || 0 == arguments[0])
      {

         throw ::exception(error_bad_argument);

      }

      s_pservicehandler->m_pservice->m_strServiceName = arguments[0];

      s_pservicehandler->m_handle = ::RegisterServiceCtrlHandlerW(L"", ServiceHandler);

      if (s_pservicehandler->m_handle == nullptr)
      {

         DWORD dwLastError = ::GetLastError();
         
         throw ::exception(error_failed);

      }

      s_pservicehandler->SetServiceStatus();

      try
      {

         s_pservicehandler->control_start(0);

         s_pservicehandler->update_state(SERVICE_RUNNING);

      }
      catch (const ::exception & e)
      {

         //
         // If the service can't start it should throw ::exception( an exception from the
         // Start method. If this happens, we catch it here and notify the
         // SCM so that it can log the error code.
         //
         HRESULT hresult = S_OK;

         if (e.m_errorcodea.has_element() && e.m_errorcodea.first().m_etype == e_error_code_type_hresult)
         {

            hresult = (HRESULT) e.m_errorcodea.first().m_iOsError;

         }

         s_pservicehandler->update_state(SERVICE_STOPPED, hresult);

      }


   }




   //*****************************************************************************
   //
   //      Name:           update_state
   //      Description:    Updates the current state and exit code of the service
   //                      and notifies the service control manager of the machine.
   //
   //*****************************************************************************
   void service_handler::update_state(unsigned int state, HRESULT errorCode)
   {


      m_status.dwCurrentState = state;

      ASSERT(0 == m_status.dwWin32ExitCode);
      ASSERT(0 == m_status.dwServiceSpecificExitCode);

      if (FAILED(errorCode))
      {
         if (FACILITY_WIN32 == HRESULT_FACILITY(errorCode))
         {
            m_status.dwWin32ExitCode = Win32FromHResult(errorCode);
         }
         else
         {
            m_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
            m_status.dwServiceSpecificExitCode = errorCode;
         }
      }

      SetServiceStatus();

   }


   void service_handler::defer_service()
   {

      return ::service_handler::defer_service();

   }


   void service_handler::start_service()
   {

      ///return ::error_failed;

   }


   void service_handler::stop_service()
   {

      //return ::error_failed;

   }


} // namespace apex_windows


#ifdef WINDOWS


unsigned int Win32FromHResult(HRESULT value)
{

   ASSERT(FACILITY_WIN32 == HRESULT_FACILITY(value));

   return value & ~0x80070000;

}
#endif



