#include "framework.h"


namespace windowing_win32
{


   HRESULT STDMETHODCALLTYPE window::DragEnter(IDataObject * pDataObj, DWORD grfKeyState, POINTL point, DWORD * pdwEffect)
   {

      //HWND hwnd = get_hwnd();

      //::message::drag_and_drop m(__oswindow(hwnd), this, MESSAGE_OLE_DRAGENTER);

      //m.pDataObj = pDataObj;
      //m.grfKeyState = grfKeyState;
      //m.point = point;
      //m.dwEffect = DROPEFFECT_NONE;

      //try
      //{

      //   message_handler(&m);

      //}
      //catch (...)
      //{

      //}

      //// Call the drag and drop helper.
      //if (m_bUseDnDHelper)
      //{
      //   // The DnD helper needs an IDataObject interface, so get one from
      //   // the COleDataObject.  Note that the false lparam means that
      //   // GetIDataObject will not AddRef() the returned interface, so
      //   // we do not Release() it.
      //   ::int_point point(m.point.x, m.point.y);

      //   m_piDropHelper->DragEnter(get_handle(), m.pDataObj, &point, m.dwEffect);
      //}

      //*pdwEffect = m.dwEffect;

      return S_OK;

   }


   HRESULT STDMETHODCALLTYPE window::DragOver(DWORD grfKeyState, POINTL point, DWORD * pdwEffect)
   {

      //::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGOVER);

      //m.pDataObj = nullptr;
      //m.grfKeyState = grfKeyState;
      //m.point = point;
      //m.dwEffect = DROPEFFECT_NONE;

      //try
      //{

      //   message_handler(&m);

      //}
      //catch (...)
      //{

      //}

      //// Call the drag and drop helper.
      //if (m_bUseDnDHelper)
      //{
      //   // The DnD helper needs an IDataObject interface, so get one from
      //   // the COleDataObject.  Note that the false lparam means that
      //   // GetIDataObject will not AddRef() the returned interface, so
      //   // we do not Release() it.
      //   ::int_point point(m.point.x, m.point.y);
      //   m_piDropHelper->DragOver(&point, m.dwEffect);
      //}


      //*pdwEffect = m.dwEffect;

      return S_OK;
   }


   HRESULT STDMETHODCALLTYPE window::DragLeave(void)
   {

      //::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGLEAVE);

      //m.pDataObj = nullptr;
      //m.grfKeyState = 0;
      //m.point = { 0,0 };
      //m.dwEffect = DROPEFFECT_NONE;

      //try
      //{

      //   message_handler(&m);

      //}
      //catch (...)
      //{

      //}

      //// Call the drag and drop helper.
      //if (m_bUseDnDHelper)
      //{
      //   m_piDropHelper->DragLeave();
      //}


      return S_OK;

   }


   HRESULT STDMETHODCALLTYPE window::Drop(IDataObject * pDataObj, DWORD grfKeyState, POINTL point, DWORD * pdwEffect)
   {

      //::message::drag_and_drop m(m_oswindow, this, MESSAGE_OLE_DRAGDROP);

      //m.pDataObj = pDataObj;
      //m.grfKeyState = grfKeyState;
      //m.point = point;
      //m.dwEffect = DROPEFFECT_NONE;

      //try
      //{

      //   message_handler(&m);

      //}
      //catch (...)
      //{

      //}

      //// Call the drag and drop helper.
      //if (m_bUseDnDHelper)
      //{
      //   // The DnD helper needs an IDataObject interface, so get one from
      //   // the COleDataObject.  Note that the false lparam means that
      //   // GetIDataObject will not AddRef() the returned interface, so
      //   // we do not Release() it.
      //   ::int_point point(m.point.x, m.point.y);
      //   m_piDropHelper->Drop(m.pDataObj, &point, m.dwEffect);
      //}

      //*pdwEffect = m.dwEffect;

      return S_OK;

   }


} // namespace windowing_win32







//DWORD WINAPI drop_target(LPVOID p)
//{
//
//   window * pimpl = (window *)p;
//
//   HRESULT hr = OleInitialize(nullptr);
//
//   hr = ::RegisterDragDrop(pimpl->get_handle(), pimpl);
//
//   if (SUCCEEDED(CoCreateInstance(CLSID_DragDropHelper, nullptr,
//      CLSCTX_INPROC_SERVER,
//      IID_IDropTargetHelper,
//      (void **)&pimpl->m_piDropHelper)))
//   {
//
//      pimpl->m_bUseDnDHelper = true;
//
//   }
//
//   MSG msg;
//
//   while (::GetMessage(&msg, nullptr, 0, 0xffffffffu))
//   {
//
//      TranslateMessage(&msg);
//
//      DispatchMessage(&msg);
//
//   }
//
//   return 0;
//
//}
//

