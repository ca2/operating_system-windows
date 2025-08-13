/*
Copyright(C) Nishant Sivakumar.
URLs - http://blog.voidnish.com and http://www.voidnish.com
Contact : nish@voidnish.com
*/
// ShellTrayInfoImpact.cpp : implementation of the notification_area class
//
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "notification_area.h"
#include "icon.h"
#include "acme/constant/message.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/international.h"
#include "apex_windows/process_data.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"


#include "acme/_operating_system.h"


#include <CommCtrl.h>



namespace windowing_win32
{

   // notification_area

   notification_area::notification_area()
      //#ifdef WINDOWS_DESKTOP
      //   :
      //      m_hfontHidden(nullptr),
      //      m_hfontRegular(nullptr)
      //#endif
   {
      // TODO: add construction code here

   }

   notification_area::~notification_area()
   {
#ifdef WINDOWS_DESKTOP
      //::DeleteObject(m_hfontHidden);
      //::DeleteObject(m_hfontRegular);
#else
      //      throw ::exception(todo);
#endif
   }

   void notification_area::Initialize(::particle * pparticle)
   {

#ifdef WINDOWS_DESKTOP

      //LOGFONTW lf = {0};
      //wcscpy(lf.lfFaceName, wstring(pnode->font_name(e_font_sans)));

      //lf.lfHeight = 16;
      //m_hfontRegular = CreateFontIndirectW(&lf);

      //lf.lfItalic = true;
      //m_hfontHidden = CreateFontIndirectW(&lf);

      //m_hwndTray = FindTrayToolbarWindow();

      //m_pil16 = __allocate image_list();

      //m_pil16->create(16,16,ILC_COLOR24,16,16);

#endif

      ListTrayIcons();

   }

   void notification_area::ListTrayIcons(int defindex /*= 0*/)
   {

#ifdef WINDOWS_DESKTOP
      
      __UNREFERENCED_PARAMETER(defindex);

      m_infoa.erase_all();

      m_pil16->erase_all();

      if (m_hwndTray == nullptr)
      {
         
         m_hwndTray = find_tray_toolbar_window();

         if (m_hwndTray == nullptr)
         {

            return;

         }

      }

      DWORD dwTrayPid = 0;

      if (!GetWindowThreadProcessId(m_hwndTray, &dwTrayPid))
      {

         return;

      }

      if (dwTrayPid == 0)
         return;

      int count = (int)::SendMessage(m_hwndTray, TB_BUTTONCOUNT, 0, 0);

      process_data < TBBUTTON > data(dwTrayPid);

      TBBUTTON tb = { 0 };
      TRAYDATA tray = { 0 };
      TrayItemInfo info;

      for (int i = 0; i < count; i++)
      {
         ::SendMessage(m_hwndTray, TB_GETBUTTON, i, (LPARAM)data.get_data());
         data.ReadData(&tb);
         data.ReadData<TRAYDATA>(&tray, (const void *)tb.dwData);

         DWORD dwProcessId = 0;

         GetWindowThreadProcessId(tray.hwnd, &dwProcessId);

         auto psystem = system();

         auto pnode = psystem->node();

         info.m_strProcessPath = pnode->process_identifier_module_path(dwProcessId);

         unichar TipChar;
         unichar sTip[1024] = { 0 };
         unichar * pTip = (unichar *)tb.iString;

         if (!(tb.fsState & TBSTATE_HIDDEN))
         {
            int x = 0;
            do
            {
               if (x == 1023)
               {
                  wcscpy(sTip, L"[ToolTip was either too long or not set]");
                  break;
               }
               data.ReadData<unichar>(&TipChar, (const void *)pTip++);
            } while (sTip[x++] = TipChar);
         }
         else
            wcscpy(sTip, L"[Hidden icon]");

         info.m_strTip = unicode_to_utf8(sTip);

         info.m_hwnd = tray.hwnd;
         info.m_uCallbackMessage = tray.uCallbackMessage;
         info.m_uID = tray.uID;

         info.m_bVisible = !(tb.fsState & TBSTATE_HIDDEN);

         int iconindex = 0;

         ICONINFO  iinfo;

         if (GetIconInfo(tray.hIcon, &iinfo) != 0)
         {

            auto pwindowingicon = __allocate ::windowing_win32::icon();
            
            pwindowingicon->add_icon(tray.hIcon);

            ::pointer<::image::icon>picon;

            picon.create(this);

            picon->initialize_with_windowing_icon(pwindowingicon);

            ::image::image_source imagesource(picon);

            iconindex = m_pil16->add(imagesource);

         }

         ::DestroyIcon(tray.hIcon);
         ::DeleteObject(iinfo.hbmColor);
         ::DeleteObject(iinfo.hbmMask);

         //LVITEM lv = {0};
         //lv.iItem = GetListCtrl().get_item_count();
         //lv.iSubItem = 0;
         //lv.mask = LVIF_IMAGE;
         //lv.iImage = iconindex;

         m_infoa.add(___new TrayItemInfo(info));
         //int index = GetListCtrl().InsertItem(&lv);
         //GetListCtrl().set_item_text(index,1,info.sTip);
         //GetListCtrl().set_item_text(index,2,info.sProcessPath);
      }

      //if( (count>0) && (defindex>=0) && (defindex<count) )
      //   GetListCtrl().SetItemState(defindex,
      //      LVIS_FOCUSED|LVIS_SELECTED,
      //      LVIS_FOCUSED|LVIS_SELECTED);
#else
      throw ::exception(todo);
#endif
   }

   void notification_area::EditCopy(int iItem)
   {
      __UNREFERENCED_PARAMETER(iItem);
      /*   POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
         if(pos)
         {
            int index = GetListCtrl().GetNextSelectedItem(pos);
            OpenClipboard();
            EmptyClipboard();
            HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, sizeof char * 512);
            char * pStr = (char *)GlobalLock(hText);
            _stprintf(pStr, "Tray Tip : %s\r\nOwner : %s",
               m_infoa[index].sTip, m_infoa[index].sProcessPath);
            GlobalUnlock(hText);
            SetClipboardData(CF_TEXT, hText);
            CloseClipboard();
         }*/
   }

   void notification_area::DoubleClick(int iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_left_button_double_click);
   }

   void notification_area::LeftClick(int iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_left_button_down);
      PostMessageToTrayIcon(iItem, e_message_left_button_up);
   }

   void notification_area::RightClick(int iItem)
   {
      PostMessageToTrayIcon(iItem, e_message_right_button_down);
      PostMessageToTrayIcon(iItem, e_message_right_button_up);
   }

   void notification_area::PostMessageToTrayIcon(int iItem, LPARAM lParam)
   {
#ifdef WINDOWS_DESKTOP
      ::PostMessage(m_infoa[iItem]->m_hwnd, m_infoa[iItem]->m_uCallbackMessage, m_infoa[iItem]->m_uID, lParam);
#endif
   }

   void notification_area::MoveLeft(int iItem)
   {
#ifdef WINDOWS_DESKTOP
      if (iItem > 0)
      {
         ::SendMessage(m_hwndTray, TB_MOVEBUTTON, iItem, iItem - 1);
         ListTrayIcons(iItem - 1);
      }
#else
      throw ::exception(todo);
#endif
   }

   void notification_area::MoveRight(int iItem)
   {
#ifdef WINDOWS_DESKTOP
      if (iItem < (m_infoa.get_size() - 1))
      {
         ::SendMessage(m_hwndTray, TB_MOVEBUTTON, iItem, iItem + 1);
         ListTrayIcons(iItem + 1);
      }
#else
      throw ::exception(todo);
#endif
   }


   void notification_area::Refresh()
   {
      ListTrayIcons();
   }

   /*
      Copyright(C) Nishant Sivakumar.
      URLs - http://blog.voidnish.com and http://www.voidnish.com
      Contact : nish@voidnish.com
   */



   HWND find_tray_toolbar_window()
   {
      HWND hwnd = nullptr;

      hwnd = ::FindWindowW(L"Shell_TrayWnd", nullptr);

      if (hwnd != nullptr)
      {
         
         hwnd = ::FindWindowExW(hwnd, nullptr, L"TrayNotifyWnd", nullptr);

         if (hwnd != nullptr)
         {

            hwnd = ::FindWindowExW(hwnd, nullptr, L"SysPager", nullptr);

            if (hwnd != nullptr)
            {
            
               hwnd = ::FindWindowExW(hwnd, nullptr, L"ToolbarWindow32", nullptr);

            }

         }

      }

      return hwnd;

   }


} // namespace windowing_win32




