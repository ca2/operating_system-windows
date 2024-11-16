#include "framework.h"
#include "shell_open.h"


namespace windows
{


   shell_open::shell_open()
   {


   }


   shell_open::~shell_open()
   {


   }



   void shell_open::initialize(::particle * pparticle)
   {

      auto estatus = ::shell_open::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   HDDEDATA CALLBACK shell_open::DdeCallback(
      unsigned int uType,
      unsigned int uFmt,
      HCONV hconv,
      HDDEDATA hsz1,
      HDDEDATA hsz2,
      HDDEDATA hdata,
      HDDEDATA dwData1,
      HDDEDATA dwData2
   )
   {
      __UNREFERENCED_PARAMETER(uFmt);
      __UNREFERENCED_PARAMETER(hconv);
      __UNREFERENCED_PARAMETER(dwData1);
      __UNREFERENCED_PARAMETER(dwData2);
      switch (uType)
      {
      case XTYP_REGISTER:
      case XTYP_UNREGISTER:
         return (HDDEDATA) nullptr;

      case XTYP_ADVDATA:
         return (HDDEDATA)DDE_FACK;

      case XTYP_XACT_COMPLETE:
         return (HDDEDATA) nullptr;

      case XTYP_CONNECT:
      {
         
         ::pointer<::windows::shell_open>pshellopen = ::get_task()->get_application();

         if (!DdeCmpStringHandles((HSZ)hsz1, pshellopen->m_hszSystemTopic))
         {
            if (!DdeCmpStringHandles((HSZ)hsz2, pshellopen->m_hszAppName))
            {
               return (HDDEDATA)true;
            }
         }
         return (HDDEDATA)false;
      }

      case XTYP_DISCONNECT:
         return (HDDEDATA) nullptr;

      case XTYP_EXECUTE:
      {
         // get the command string
         unsigned int dwSize = DdeGetData(
            hdata,
            nullptr,
            0,
            0);

         string str;

         dwSize = DdeGetData(
            hdata,
            (LPBYTE)str.get_buffer(dwSize),
            dwSize,
            0);

         str.release_buffer();

         //throw ::not_implemented();
         /*
         // execute the command
         if (!psystem->OnDDECommand( (char *)(const wchar_t *)str))
            TRACE1("Error: failed to execute DDE command '%S'.\n", str);
         */
         //
         VERIFY(DdeFreeDataHandle(hdata));
         return (HDDEDATA) nullptr;
      }

      default:
         return (HDDEDATA) nullptr;
      }
   }

   void shell_open::initialize_shell_open()
   {


      m_dwDde = 0;

      if (!DdeInitializeW(&m_dwDde,         // receives instance identifier
         (PFNCALLBACK)DdeCallback, // pointer to callback function
         //CBF_FAIL_EXECUTES |        // filter XTYPE_EXECUTE
         APPCMD_FILTERINITS, // filter notifications
         0))
      {

         m_hszAppName = DdeCreateStringHandleW(m_dwDde, L"vmpLight", 0);

         m_hszSystemTopic = DdeCreateStringHandleW(m_dwDde, L"::auraacmesystem()", 0);

         DdeNameService(m_dwDde, m_hszAppName, 0, DNS_REGISTER);

      }


      return ::success;


   }


} // namespace windows
