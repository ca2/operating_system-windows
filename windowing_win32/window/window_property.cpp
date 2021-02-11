#include "framework.h"


#include <propsys.h>
#include <propkey.h>


SHSTDAPI SHGetPropertyStoreForWindow(_In_ HWND hwnd, _In_ REFIID riid, _Outptr_ void ** ppv);


HRESULT SetTouchDisableProperty(HWND hwnd, BOOL fDisableTouch)
{

   IPropertyStore * pPropStore;

   HRESULT hrReturnValue = SHGetPropertyStoreForWindow(hwnd, IID_PPV_ARGS(&pPropStore));

   if (SUCCEEDED(hrReturnValue))
   {

      PROPVARIANT payload;

      payload.vt = VT_BOOL;

      payload.boolVal = fDisableTouch ? VARIANT_TRUE : VARIANT_FALSE;

      hrReturnValue = pPropStore->SetValue(PKEY_EdgeGesture_DisableTouchWhenFullscreen, payload);

      pPropStore->Release();

   }

   return hrReturnValue;

}
