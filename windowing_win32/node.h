// Created by camilo on 2021/09/12 16:03 BRT <3TBS!!
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 node :
      virtual public ::aura::windows::node
   {
   public:


      //__creatable_from_base(node, ::acme::node);


      enum_message                                       m_emessageWindowsTaskbarCreatedMessage;


      node();
      ~node() override;

      
      void install_keyboard_hook(::matter * pmatterListener) override;
      void uninstall_keyboard_hook(::matter * pmatterListener) override;

      void install_mouse_hook(::matter * pmatterListener) override;
      void uninstall_mouse_hook(::matter * pmatterListener) override;


      virtual void register_windows_message();


   };


} // namespace windowing_win32



