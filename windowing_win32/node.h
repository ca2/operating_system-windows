// Created by camilo on 2021/09/12 16:03 BRT <3TBS!!
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 node :
      virtual public ::aura::windows::node
   {
   public:


      node();
      ~node() override;

      
      ::e_status register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard) override;
      ::e_status unregister_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard) override;


   };


} // namespace windowing_win32



