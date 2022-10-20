#pragma once


#include "apex/parallelization/service_handler.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS service_handler :
      virtual public ::service_handler
   {
   public:



      SERVICE_STATUS             m_status;

      SERVICE_STATUS_HANDLE      m_handle;

      static service_handler *   s_pservicehandler;

      DWORD m_dwStopTimeout;
      

      service_handler(u32 controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
      ~service_handler() override;


      virtual void control_start(u32 uControl);

      virtual void control_stop(u32 uControl);

      virtual void _server();

      virtual void SetServiceStatus();

      virtual void update_state(u32 state, HRESULT errorCode = S_OK);

      //virtual void _main_server(::u32 argumentCount, wchar_t * arguments);

      static void WINAPI ServiceMain(DWORD argumentCount, PWSTR * arguments);

      static void WINAPI ServiceHandler(DWORD control);
      
      virtual void queue_user_work_item(ULONG flags = WT_EXECUTELONGFUNCTION);

      static DWORD WINAPI thread_proc(void * pcontext);
      
      static void serve(service * pservice);

      virtual void _main_server(::u32 argumentCount, PWSTR * arguments);

      virtual void defer_service();

      //virtual void enable_service();
      //virtual void disable_service();

      virtual void start_service();
      virtual void stop_service();


   };


} // namespace apex_windows



