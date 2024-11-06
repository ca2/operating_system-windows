#pragma once


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS service :
      public service_base
   {
   public:


      SERVICE_STATUS             m_status;

      SERVICE_STATUS_HANDLE      m_handle;

      static service *           s_pservice;
      

      service(unsigned int controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
      virtual ~service();


      virtual void Start(unsigned int);

      virtual void Stop(unsigned int);

      virtual void _server();

      virtual void SetServiceStatus();

      virtual void UpdateState(unsigned int state, HRESULT errorCode = S_OK);

      //virtual void _main_server(unsigned int argumentCount, wchar_t * arguments);

      static void WINAPI ServiceMain(DWORD argumentCount, PWSTR * arguments);

      static void WINAPI ServiceHandler(DWORD control);
      
      virtual void queue_user_work_item(WINULONG flags = WT_EXECUTELONGFUNCTION);

      static DWORD WINAPI thread_proc(void * pcontext);
      
      static void serve(service * pservice);

      virtual void _main_server(unsigned int argumentCount, PWSTR * arguments);


   };


} // namespace apex_windows



