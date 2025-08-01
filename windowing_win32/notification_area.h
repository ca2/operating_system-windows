#pragma once


#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/prototype/particle.h"
#include "acme/prototype/prototype/pointer.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{


   struct CLASS_DECL_WINDOWING_WIN32 TRAYDATA
   {

      HWND           hwnd;
      UINT           uID;
      UINT           uCallbackMessage;
      UINT           Reserved[2];
      HICON          hIcon;


   };


   struct CLASS_DECL_WINDOWING_WIN32 TrayItemInfo :
      virtual public ::particle
   {

      HWND           m_hwnd;
      unsigned int          m_uID;
      unsigned int          m_uCallbackMessage;
      string         m_strTip;
      string         m_strProcessPath;
      bool           m_bVisible;


   };


   CLASS_DECL_WINDOWING_WIN32 char GetDriveLetter(const ::scoped_string & scopedstrDevicePath);

   CLASS_DECL_WINDOWING_WIN32 HWND find_tray_toolbar_window();


   class CLASS_DECL_WINDOWING_WIN32 notification_area :
      virtual public ::particle
   {
   public:


      HWND                             m_hwndTray;
      ::image::image_list_pointer          m_pil16;
      
      pointer_array < TrayItemInfo >    m_infoa;
      HFONT                            m_hfontHidden;
      HFONT                            m_hfontRegular;


      notification_area();
      virtual ~notification_area();

      virtual void Initialize(::particle * pparticle);

      void ListTrayIcons(int defindex = 0);
      void EditCopy(int iItem);
      void DoubleClick(int iItem);
      void RightClick(int iItem);
      void LeftClick(int iItem);
      void MoveLeft(int iItem);
      void MoveRight(int iItem);
      void Refresh();
      void PostMessageToTrayIcon(int iItem, LPARAM lParam);


   };


} // namespace windowing_win32



