#include "framework.h"
#include "shell_launcher.h"
#include "acme/exception/interface_only.h"


namespace apex_windows
{

   
   shell_launcher::shell_launcher()
   {


   }


   shell_launcher::~shell_launcher()
   {


   }


   void shell_launcher::launch()
   {

      //if(m_iMode == 0)
      //{

      //   m_h = ::ShellExecuteW(
      //      m_oswindow,
      //      wstring(m_strOperation),
      //      wstring(m_strFile),
      //      wstring(m_strParameters),
      //      wstring(m_strDirectory),
      //      windows_show_window(m_edisplay, XXXXm_eactivation));

      //}

      throw ::interface_only();

   }


   //bool shell_launcher::succeeded()
   //{

   //   //return ((iptr)m_h) >= 32;

   //   return false;

   //}


} // namespace apex_windows



