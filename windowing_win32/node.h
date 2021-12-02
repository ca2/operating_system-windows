// Created by camilo on 2021/09/12 16:03 BRT <3TBS!!
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 node :
      virtual public ::aura::windows::node
   {
   public:


      enum_message                                       m_emessageWindowsTaskbarCreatedMessage;


      node();
      ~node() override;

      
      ::e_status install_keyboard_hook(::matter * pmatterListener) override;
      ::e_status uninstall_keyboard_hook(::matter * pmatterListener) override;

      ::e_status install_mouse_hook(::matter * pmatterListener) override;
      ::e_status uninstall_mouse_hook(::matter * pmatterListener) override;


      virtual ::e_status register_windows_message();


   };


} // namespace windowing_win32



