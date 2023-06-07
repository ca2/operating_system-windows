// enhancing by camilo on 2022-11-02 14:29 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/shell_launcher.h"
#include "acme/_operating_system.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS shell_launcher :
      virtual public ::apex::shell_launcher
   {
   public:


      HWND              m_hwnd;
      HINSTANCE         m_hinstance;
      HINSTANCE         m_hinstanceApp;   // out when SEE_MASK_NOCLOSEPROCESS is specified
      ULONG             m_fMask;          // in, SEE_MASK_XXX values
      void *            m_lpIDList;       // in, valid when SEE_MASK_IDLIST is specified, PCIDLIST_ABSOLUTE, for use with SEE_MASK_IDLIST & SEE_MASK_INVOKEIDLIST
      const char *      m_vssClass;       // in, valid when SEE_MASK_CLASSNAME is specified
      HKEY              m_hkeyClass;      // in, valid when SEE_MASK_CLASSKEY is specified
      u32               m_dwHotKey;       // in, valid when SEE_MASK_HOTKEY is specified
      union
      {
         HANDLE         m_hIcon;          // not used
         HANDLE         n_hMonitor;
      };
      HANDLE            m_hProcess;       // out, valid when SEE_MASK_NOCLOSEPROCESS specified


      shell_launcher();
      ~shell_launcher() override;


      void launch() override;


      //virtual void status() const override;


   };


} // namespace apex_windows



