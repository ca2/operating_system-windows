#include "framework.h"


//#include <windows.h>
#include <wmsdk.h>
//#include <atlbase.h>


#pragma comment(lib, "wmvcore")

// http://nogeekhere.blogspot.com.br/2009/05/how-to-extracting-embedded-album-art.html

string extract_mccdi(string str)
{

   wstring wszAudioFile(str);

   bool bOK = false;

   WM_PICTURE * pPicture = nullptr;
   memory mem;

   do
   {

      comptr<IWMSyncReader> pIWMSyncReader;
      if (FAILED(WMCreateSyncReader(nullptr, 0, &pIWMSyncReader))) break;

      if (FAILED(pIWMSyncReader->Open(wszAudioFile))) break;

      comptr<IWMHeaderInfo3> pIWMHeaderInfo3;
      if (FAILED(pIWMSyncReader->QueryInterface(&pIWMHeaderInfo3))) break;

      WMT_ATTR_DATATYPE wmtDataType = WMT_TYPE_STRING;
      ::u16 wStreamNum = 0;
      ::u16 wLength = 0;
      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
         &wStreamNum, g_wszWMMCDI, &wmtDataType, nullptr, &wLength))) break;
      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
         &wStreamNum, g_wszWMWMContentID, &wmtDataType, nullptr, &wLength))) break;



      // pPicture = (WM_PICTURE*)memory_alloc(wLength);
      mem.set_size(wLength);

      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
         &wStreamNum, g_wszWMMCDI, &wmtDataType, (byte *)mem.get_data(), &wLength))) break;

      bOK = true;

   } while (false);
   wstring wstr((wchar_t *)mem.get_data(), mem.get_size() / 2);
   return wstr;

}



