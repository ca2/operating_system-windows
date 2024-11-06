
#include "framework.h"


namespace windowing_win32
{


   //int window::SetScrollPos(int nBar, int nPos, bool bRedraw)
   //{

   //   return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);

   //}


   //int window::GetScrollPos(int nBar) const
   //{

   //   return ::GetScrollPos(((::windows::interaction_impl *)this)->get_handle(), nBar);

   //}


   //void window::SetScrollRange(int nBar, int nMinPos, int nMaxPos, bool bRedraw)
   //{

   //   ::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);

   //}

   
   //void window::GetScrollRange(int nBar, LPINT pMinPos, LPINT lpMaxPos) const
   //{

   //   ::GetScrollRange(((::windows::interaction_impl *)this)->get_handle(), nBar, pMinPos, lpMaxPos);

   //}

   //// Turn on/off non-control scrollbars
   ////   for WS_?SCROLL scrollbars - show/hide them
   ////   for control scrollbar - enable/disable them
   //void interaction_impl::EnableScrollBarCtrl(int nBar, bool bEnable)
   //{
   //   // WS_?SCROLL scrollbar - show or hide
   //   ShowScrollBar(nBar, bEnable);

   //}


   //bool interaction_impl::SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, bool bRedraw)
   //{

   //   ASSERT(pScrollInfo != nullptr);

   //   HWND hwnd = get_handle();
   //   pScrollInfo->cbSize = sizeof(*pScrollInfo);

   //   ::SetScrollInfo(oswindow, nBar, pScrollInfo, bRedraw);

   //   return true;

   //}


   //bool interaction_impl::GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask)
   //{

   //   __UNREFERENCED_PARAMETER(nMask);
   //   ASSERT(pScrollInfo != nullptr);


   //   HWND hwnd = get_handle();
   //   return ::GetScrollInfo(oswindow, nBar, pScrollInfo) != false;

   //}

   //int interaction_impl::GetScrollLimit(int nBar)
   //{
   //   int nMin, nMax;
   //   GetScrollRange(nBar, &nMin, &nMax);
   //   SCROLLINFO info;
   //   if (GetScrollInfo(nBar, &info, SIF_PAGE))
   //   {
   //      nMax -= maximum(info.nPage - 1, 0);
   //   }
   //   return nMax;
   //}

   //void interaction_impl::ScrollWindow(int xAmount, int yAmount,
   //   const ::int_rectangle * rectangle, const ::int_rectangle * lpClipRect)

   //{
   //   //ASSERT(::IsWindow(get_handle()));

   //   //if(is_window_visible() || prectangle != nullptr || lpClipRect != nullptr)

   //   //{
   //   //   // When visible, let Windows do the scrolling
   //   //   ::ScrollWindow(get_handle(),xAmount,yAmount,prectangle,lpClipRect);

   //   //}
   //   //else
   //   //{
   //   //   // Windows does not perform any scrolling if the interaction_impl is
   //   //   // not visible.  This leaves child windows unscrolled.
   //   //   // To ac::collection::count for this oversight, the child windows are moved
   //   //   // directly instead.
   //   //   ::windowing::window * pwindow_Child = ::GetWindow(get_handle(),GW_CHILD);
   //   //   if(oswindow_Child != nullptr)
   //   //   {
   //   //      for(; oswindow_Child != nullptr;
   //   //            oswindow_Child = ::GetNextWindow(oswindow_Child,GW_HWNDNEXT))
   //   //      {
   //   //         ::int_rectangle rectangle;
   //   //         ::window_rectangle(oswindow_Child,&rectangle);
   //   //         _001ScreenToClient(&rectangle);
   //   //         ::set_window_position(oswindow_Child,nullptr,rectangle.left() + xAmount,rectangle.top() + yAmount,0,0,SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
   //   //      }
   //   //   }
   //   //}

   //}


} // namespace windowing_win32



