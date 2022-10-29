#include "framework.h"
#include "acme/node/windows/registry.h"
#include <shlobj.h>
#include <string.h>
#include "explorer_restart.h"
#include "acme/filesystem/filesystem/acme_directory.h"


CLSID CLSID_DeskBandSample = { 0x19970ca2, 0x71a, 0x4b7e,{ 0x8a, 0xa2, 0xe5, 0x60, 0x81, 0xd, 0xab, 0x35 } };

bool register_desk_toolbar(::apex::system * psystem);

bool register_desk_toolbar_dll();

bool position_desk_toolbar1();






bool register_desk_toolbar(::apex::system* psystem)
{

   //taskbar position calculating code omitted

   defer_co_initialize_ex(false);

   //DWORD dwSession = 0;

   //if (!pre_explorer_restart(dwSession))
   //{

   //   return false;

   //}

   //sleep(1_s);
   //auto psystem = acmesystem()->m_paurasystem;

   auto pnode = psystem->node()->m_papexnode;

   ::file::path pathDll = psystem->m_pacmedirectory->module() / "_desk_tb.dll";

   pnode->register_dll(pathDll);

   //sleep(1_s);

   //pos_explorer_restart(dwSession);

   //sleep(1_s);

   //pre_explorer_restart(dwSession);

   //sleep(1_s);

   //pos_explorer_restart(dwSession);

   //sleep(5000_ms);

   position_desk_toolbar1();

   //pos_explorer_restart(dwSession);

   return true;

}


//bool register_desk_toolbar_dll()
//{
//
//   string strPathDll;
//
//   //#ifdef _DEBUG
//
//   strPathDll = ::dir::module() / "_desk_tb.dll";
//
//   //#else
//   //
//   //   strPathDll = ::dir::matter() / "time" / process_platform_name() /"stage/_desk_tb.dll";
//   //
//   //#endif
//
//   string strParam;
//
//   strParam = "/s \"" + strPathDll + "\"";
//
//   //wstring wstrParam(strParam);
//
//   //STARTUPINFOW si = {};
//
//   //si.cb = sizeof(si);
//
//   //si.wShowWindow = SW_HIDE;
//
//   //PROCESS_INFORMATION pi = {};
//
//   WCHAR wszSystem[2048];
//
//   GetSystemDirectoryW(wszSystem, sizeof(wszSystem) / sizeof(WCHAR));
//
//   wstring wstrSystem(wszSystem);
//
//   ::file::path path(wstrSystem);
//
//   path /= "regsvr32.exe";
//
//   property_set set;
//
//   set["privileged"] = true;
//
//   if (call_sync(path, strParam, path.folder(), ::e_display_none, 3_min, set) != 0)
//   {
//
//      return false;
//
//   }
//
//   //if (CreateProcessW(wstrPath, wstrParam, nullptr, nullptr, false, 0, nullptr, wstrSystem, &si, &pi))
//   //{
//
//   //   output_debug_string("created");
//
//   //}
//   //else
//   //{
//
//   //   output_debug_string("not created");
//
//   //}
//
//   //CloseHandle(pi.hProcess);
//
//   //CloseHandle(pi.hthread);
//
//   return true;
//
//}


bool position_desk_toolbar1()
{

   ::comptr<ITrayDeskBand> spTrayDeskBand;

   //HRESULT hr = spTrayDeskBand.CoCreateInstance(CLSID_TrayDeskBand);

   //if (SUCCEEDED(hr))
   {

      // Vista and higher

      //hr = spTrayDeskBand->DeskBandRegistrationChanged();


      //if (SUCCEEDED(hr))
      {

         //int iCount = 90;

         //while (iCount > 0)
         //{

         //   hr = spTrayDeskBand->IsDeskBandShown(CLSID_DeskBandSample);

         //   if (SUCCEEDED(hr))
         //   {

         //      break;

         //   }

         //   sleep(250_ms);

         //   iCount--;

         //}

         //if (SUCCEEDED(hr))
         //{

         //   if (hr == S_FALSE)
         //   {

         //      hr = spTrayDeskBand->ShowDeskBand(CLSID_DeskBandSample);

         //   }

         //   {

         //      int iCount = 600;

         //      while (iCount > 0)
         //      {

         //         hr = spTrayDeskBand->IsDeskBandShown(CLSID_DeskBandSample);

         //         if (SUCCEEDED(hr) && hr == S_OK)
         //         {

         //            goto do_extra_setup;

         //         }

         //         sleep(250_ms);

         //         iCount--;

         //      }

         //      return true;

         //DWORD dwSession = 0;

         //pre_explorer_restart(dwSession);

         //pos_explorer_restart(dwSession);

         //do_extra_setup:


         DWORD dwSession = 0;

         memory m2;

         //         iCount = 300;

         //while (iCount > 0)
         {

            ::acme_windows::registry::key k(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Streams\\Desktop", false);

            k.get("TaskbarWinXP", m2);

            byte * pFound;

            string strAddUp;

            DWORD dwOther;

            if ((pFound = (byte *)memory_find_memory(m2.get_data(), m2.get_size(), &CLSID_DeskBandSample, sizeof(CLSID_DeskBandSample))) != nullptr)
            {

               auto iStart = pFound - m2.get_data();

               if (iStart == 16)
               {

                  goto ready;

               }

               pre_explorer_restart2(dwSession);

               dwOther = *((DWORD *)&pFound[16]);

               m2.erase(iStart, 52);

            }
            else
            {

               pre_explorer_restart2(dwSession);

               DWORD * pdw = (DWORD *)m2.get_data();

               if (pdw[2] == 1)
               {

                  strAddUp = "01000000";

               }

               dwOther = *((DWORD *)&m2.get_data()[16]);

               dwOther -= 0x7e;

               pdw[2]++;

            }

            string str = "7E00000041050000000000003300000000000000000000007A0000000000000001000000" + strAddUp;

            memory m;

            m.from_hex(str);

            m.splice((byte *)&CLSID_DeskBandSample, sizeof(CLSID_DeskBandSample));

            m2.splice(m, 16);

            *((DWORD *)&m2.get_data()[16 + 52 + 4 + 16]) = dwOther;

            k.set("TaskbarWinXP", m2);


            /*      }
            else
            {

            }*/

            //            iCount--;

         }

         pos_explorer_restart2(dwSession);


      }

   }

ready:
   ;
   //}
   //else
   //{

   //   // WinXP workaround

   //   OLECHAR szOle[2048];

   //   ::StringFromGUID2(CLSID_DeskBandSample, szOle, sizeof(szOle) / sizeof(szOle[0]));

   //   string sAtom(szOle);

   //   if (!::GlobalFindAtom(sAtom))
   //   {

   //      ::GlobalAddAtom(sAtom);

   //   }

   //   // Beware! SHLoadInProc is not implemented under Vista and higher.
   //   hr = ::SHLoadInProc(CLSID_DeskBandSample);
   //}

   //HKEY hKey = { 0 };
   //DWORD result = 0;
   //result = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StuckRects2"),
   //   0, KEY_READ | KEY_WRITE, &hKey);
   //if (result == ERROR_SUCCESS)
   //{
   //   std::vector<byte> data;
   //   data.resize(256);
   //TCHAR settingValue[] = _T("Settings");
   //DWORD dwKeyDataType = 0;
   //DWORD dwDataBufSize = data.size();
   //result = ::RegQueryValueEx(hKey, settingValue, nullptr, &dwKeyDataType,
   //   (LPBYTE)data.data(), &dwDataBufSize);
   //while (ERROR_MORE_DATA == result)
   //{
   //   data.resize(256 + data.size());
   //   dwDataBufSize = data.size();
   //   result = ::RegQueryValueEx(hKey, settingValue, nullptr, &dwKeyDataType,
   //      (LPBYTE)data.data(), &dwDataBufSize);
   //}
   //data.resize(dwDataBufSize);
   //if (result == ERROR_SUCCESS)
   //{
   //   switch (dwKeyDataType)
   //   {
   //   case REG_BINARY:
   //      if (data.size() == 40)
   //      {
   //         byte taskbarPosition = data[12];
   //         taskbarPosition = edge;
   //         data[12] = taskbarPosition;
   //         RECTANGLE_I32* taskbarRect = (RECTANGLE_I32*)&data[24];
   //         CopyRect(taskbarRect, &abd.rc);
   //         result = ::RegSetValueEx(hKey, settingValue, 0, REG_BINARY, (LPBYTE)data.data(), dwDataBufSize);
   //      }
   //      break;
   //   }
   //}
   //::RegCloseKey(hKey);

   return true;



}




bool position_desk_toolbar2()
{
   //return true;
   //::comptr<ITrayDeskBand> spTrayDeskBand;

   //HRESULT hr = spTrayDeskBand.CoCreateInstance(CLSID_TrayDeskBand);

   //sleep(1_s);
   //if (SUCCEEDED(hr))
   {
      ::acme_windows::registry::key k;

      if (k._open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Discardable\\PostSetup\\Component Categories64\\{00021492-0000-0000-C000-000000000046}\\Enum", false))
      {

         memory m;

         if (k._get("Implementing", m))
         {

            if (!memory_find_memory(m.get_data(), m.get_size(), &CLSID_DeskBandSample, sizeof(CLSID_DeskBandSample)))
            {

               DWORD * pdwArraySize = (DWORD *)&m.get_data()[0x18];

               m.splice(
                  (byte *)&CLSID_DeskBandSample,
                  sizeof(CLSID_DeskBandSample),
                  0x18 + minimum((*pdwArraySize) * 16, 32));

               (*pdwArraySize)++;



               k.set("Implementing", m);

            }
         }

      }
   }
   {


   }
   {
      //   "Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Cached"
      {

         memory m;

         ::acme_windows::registry::key k;

         if (k._open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Cached", false))
         {

            if (!k._get("{19970CA2-071A-4B7E-8AA2-E560810DAB35} {EB0FE172-1A3A-11D0-89B3-00A0C90A90AC} 0xFFFF", m))
            {

               m.set_size(0);

               m.from_hex("01000000000000008BBA64EF5FD8D201");

               k._set("{19970CA2-071A-4B7E-8AA2-E560810DAB35} {EB0FE172-1A3A-11D0-89B3-00A0C90A90AC} 0xFFFF", m);

            }

         }

         //::acmefile()->put_contents("C:\\archive\\hell_cached.txt", ::hex::upper_from(m.get_data(), m.get_size()));

      }

      //01000000000000008BBA64EF5FD8D201
   }
   {

      //hr = spTrayDeskBand->DeskBandRegistrationChanged();
      //return true;
      // sleep(1_s);

      //DWORD dwSession = 0;

      //pre_explorer_restart(dwSession);

      //sleep(1_s);

      string str = "7E00000040050000000000003300000000000000000000007A000000000000000100000001000000";

      memory m;

      m.from_hex(str);

      {

         memory m2;

         ::acme_windows::registry::key k(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Streams\\Desktop", false);

         k._get("TaskbarWinXP", m2);

         if (!memory_find_memory(m2.get_data(), m2.get_size(), &CLSID_DeskBandSample, sizeof(CLSID_DeskBandSample)))
         {

            DWORD * pdw = (DWORD *)m2.get_data();

            m.splice((byte *)&CLSID_DeskBandSample, sizeof(CLSID_DeskBandSample));

            pdw[2]++;

            m2.splice(m, 16);

            k._set("TaskbarWinXP", m2);

         }

         //::acmefile()->put_contents("C:\\archive\\hells.txt", ::hex::upper_from(&m[16], 56));

      }

      //sleep(1_s);

      //pos_explorer_restart(dwSession);

      // Vista and higher


      //if (SUCCEEDED(hr))
      //{

      //   int iCount = 90;

      //   while (iCount > 0)
      //   {

      //      hr = spTrayDeskBand->IsDeskBandShown(CLSID_DeskBandSample);

      //      if (SUCCEEDED(hr))
      //      {

      //         break;

      //      }

      //      sleep(250_ms);

      //      iCount--;

      //   }

      //   if (SUCCEEDED(hr))
      //   {

      //      if (hr == S_FALSE)
      //      {

      //         hr = spTrayDeskBand->ShowDeskBand(CLSID_DeskBandSample);

      //      }

      //   }

      //}

   }
   //else
   //{

   //   // WinXP workaround

   //   OLECHAR szOle[2048];

   //   ::StringFromGUID2(CLSID_DeskBandSample, szOle, sizeof(szOle) / sizeof(szOle[0]));

   //   string sAtom(szOle);

   //   if (!::GlobalFindAtom(sAtom))
   //   {

   //      ::GlobalAddAtom(sAtom);

   //   }

   //   // Beware! SHLoadInProc is not implemented under Vista and higher.
   //   hr = ::SHLoadInProc(CLSID_DeskBandSample);
   //}

   //HKEY hKey = { 0 };
   //DWORD result = 0;
   //result = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StuckRects2"),
   //   0, KEY_READ | KEY_WRITE, &hKey);
   //if (result == ERROR_SUCCESS)
   //{
   //   std::vector<byte> data;
   //   data.resize(256);
   //TCHAR settingValue[] = _T("Settings");
   //DWORD dwKeyDataType = 0;
   //DWORD dwDataBufSize = data.size();
   //result = ::RegQueryValueEx(hKey, settingValue, nullptr, &dwKeyDataType,
   //   (LPBYTE)data.data(), &dwDataBufSize);
   //while (ERROR_MORE_DATA == result)
   //{
   //   data.resize(256 + data.size());
   //   dwDataBufSize = data.size();
   //   result = ::RegQueryValueEx(hKey, settingValue, nullptr, &dwKeyDataType,
   //      (LPBYTE)data.data(), &dwDataBufSize);
   //}
   //data.resize(dwDataBufSize);
   //if (result == ERROR_SUCCESS)
   //{
   //   switch (dwKeyDataType)
   //   {
   //   case REG_BINARY:
   //      if (data.size() == 40)
   //      {
   //         byte taskbarPosition = data[12];
   //         taskbarPosition = edge;
   //         data[12] = taskbarPosition;
   //         RECTANGLE_I32* taskbarRect = (RECTANGLE_I32*)&data[24];
   //         CopyRect(taskbarRect, &abd.rc);
   //         result = ::RegSetValueEx(hKey, settingValue, 0, REG_BINARY, (LPBYTE)data.data(), dwDataBufSize);
   //      }
   //      break;
   //   }
   //}
   //::RegCloseKey(hKey);

   return true;

}


