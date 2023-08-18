// Created by camilo on 2023-08-17 01:42 <3ThomasBorregaardSorensen!
#include "framework.h"
#include "node.h"
#include "acme/_operating_system.h"
#include <sapi.h>


namespace acme_windows
{


   void node::speak(const ::scoped_string& scopedstr)
   {


      if (FAILED(::CoInitialize(NULL)))
         return;

      ISpVoice* pVoice = NULL;

      HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
      if (SUCCEEDED(hr))
      {
         wstring wstr = scopedstr;

         hr = pVoice->Speak((LPCWSTR)wstr, NULL, NULL);

         pVoice->Release();
         pVoice = NULL;
      }
      ::CoUninitialize();



   }


} // namespace acme_windows



