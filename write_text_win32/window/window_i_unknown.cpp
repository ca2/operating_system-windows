#include "framework.h"


namespace windowing_win32
{


   HRESULT STDMETHODCALLTYPE window::QueryInterface(REFIID riid, void ** ppvObject)
   {

      if (__uuidof(IDropTarget) == riid)
      {
         *ppvObject = this;
      }
      else if (__uuidof(IUnknown) == riid)
      {
         *ppvObject = this;
      }
      else
      {
         *ppvObject = nullptr;
         return E_FAIL;
      }

      this->AddRef();

      return S_OK;

   }


   ULONG STDMETHODCALLTYPE window::AddRef(void)
   {

      return (ULONG)increment_reference_count(REFERENCING_DEBUGGING_THIS);

   }


   ULONG STDMETHODCALLTYPE window::Release(void)
   {

      return (ULONG)release();

   }




} // namespace windowing_win32



