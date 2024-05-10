// Created by Camilo on 2024-04-09 10:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "node.h"


#include "acme/_operating_system.h"
#define boolean windows_boolean
#include <ObjBase.h>      // include the base COM header
#include <Netlistmgr.h>
#undef boolean


// Instruct linker to link to the required COM libraries
#pragma comment(lib, "ole32.lib")


namespace apex_windows
{


   bool node::has_ip4_internet()
   {
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
               hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
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
   }


   bool node::has_ip6_internet()
   {
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
               hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
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
   }


} // namespace apex_windows



