// Created on 2021-04-28 21:56 BRT <3TBS_!! Second celebration of Mummis Birthday 70!!
// party with Carols Family!!
#include "framework.h"


HRESULT win_create_link(const widechar* pszPathObj, const widechar* pszPathLink, const widechar* pszDesc, const widechar* pszIconPath, ::i32 iIcon)
{

   HRESULT hres;

   IShellLinkW* psl;

   defer_co_initialize_ex(false);

   // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
   // has already been called.
   hres = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);

   if (SUCCEEDED(hres))
   {

      IPersistFile* ppf;

      // set the path to the shortcut target and add the description.
      psl->SetPath(pszPathObj);

      psl->SetDescription(pszDesc);

      if (pszIconPath != nullptr && *pszIconPath != L'\0')
      {

         psl->SetIconLocation(pszIconPath, iIcon);

      }

      // Query IShellLink for the IPersistFile interface, used for saving the
      // shortcut in persistent storage.
      hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

      if (SUCCEEDED(hres))
      {
         //WCHAR wsz[MAX_PATH];

         // Ensure that the string is Unicode.
         //            MultiByteToWideChar(CP_ACP, 0, pszPathLink, -1, wsz, MAX_PATH);


         // Add code here to check return value from MultiByteWideChar
         // for success.

         // Save the link by calling IPersistFile::Save.
         hres = ppf->Save(pszPathLink, true);

         ppf->Release();

      }

      psl->Release();

   }

   return hres;

}
