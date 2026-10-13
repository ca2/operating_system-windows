// Created by Camilo on 2024-04-09 10:15 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "node.h"


#include "acme/_operating_system.h"
#ifdef __REACTOS__
#include <wininet.h>
#else
#define boolean windows_boolean
#include <ObjBase.h>      // include the base COM header
#include <Netlistmgr.h>
#undef boolean
#endif


// Instruct linker to link to the required COM libraries
#pragma comment(lib, "ole32.lib")


namespace apex_windows
{


   bool node::has_ip4_internet()
   {
#ifdef __REACTOS__
      // XP has no Network List Manager. This is a connection-state indication,
      // not a probe of internet reachability or an address-family guarantee.
      DWORD flags = 0;
      return InternetGetConnectedState(&flags, 0) && !(flags & INTERNET_CONNECTION_OFFLINE);
#else
      HRESULT hr = S_FALSE;
      bool bHasInternet = false;
      try
      {
         hr = CoInitialize(NULL);
         if (SUCCEEDED(hr))
         {
            INetworkListManager* pNetworkListManager;
            hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, __uuidof(INetworkListManager), (LPVOID*)&pNetworkListManager);
            if (SUCCEEDED(hr))
            {
               NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY::NLM_CONNECTIVITY_DISCONNECTED;
               VARIANT_BOOL isConnected = VARIANT_FALSE;
#ifdef __MINGW32__
               hr = pNetworkListManager->IsConnectedToInternet(&isConnected);
#else
               hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
#endif
               //if (SUCCEEDED(hr))
               //{
               //   if (isConnected == VARIANT_FALSE)
               //      return false;
               //}

               if (isConnected == VARIANT_TRUE && SUCCEEDED(pNetworkListManager->GetConnectivity(&nlmConnectivity)))
               {
                  if (nlmConnectivity & NLM_CONNECTIVITY_IPV4_INTERNET)
                  {
                     bHasInternet = true;
                  }
               }

               pNetworkListManager->Release();
            }
         }

         CoUninitialize();
      }
      catch (...)
      {
         bHasInternet = false;
      }

      return bHasInternet;
#endif
   }


   bool node::has_ip6_internet()
   {
#ifdef __REACTOS__
      // XP's WinINet fallback cannot establish IPv6 internet connectivity.
      return false;
#else
      HRESULT hr = S_FALSE;
      bool bHasInternet = false;
      try
      {
         hr = CoInitialize(NULL);
         if (SUCCEEDED(hr))
         {
            INetworkListManager* pNetworkListManager;
            hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, __uuidof(INetworkListManager), (LPVOID*)&pNetworkListManager);
            if (SUCCEEDED(hr))
            {
               NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY::NLM_CONNECTIVITY_DISCONNECTED;
               VARIANT_BOOL isConnected = VARIANT_FALSE;
#ifdef __MINGW32__
               hr = pNetworkListManager->IsConnectedToInternet(&isConnected);
#else
               hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
#endif
               //if (SUCCEEDED(hr))
               //{
               //   if (isConnected == VARIANT_FALSE)
               //      return false;
               //}

               if (isConnected == VARIANT_TRUE && SUCCEEDED(pNetworkListManager->GetConnectivity(&nlmConnectivity)))
               {
                  if (nlmConnectivity & NLM_CONNECTIVITY_IPV6_INTERNET)
                  {
                     bHasInternet = true;
                  }
               }

               pNetworkListManager->Release();
            }
         }

         CoUninitialize();
      }
      catch (...)
      {
         bHasInternet = false;
      }

      return bHasInternet;
#endif
   }


} // namespace apex_windows



