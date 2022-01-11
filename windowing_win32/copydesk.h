#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 copydesk :
      virtual public ::user::copydesk,
      virtual public ::user::message_window
   {
   public:


      //HWND m_hwnd;

      //__pointer(::user::interaction)      m_puserinteraction;

      /// negative value undefined
      ::count  m_cFileCount;
      /// -2 value undefined
      int   m_iPriorityTextFormat;
      /// negative value undefined
      int  m_iFilea;
      /// negative value undefined
      int  m_iText;
      /// negative value undefined
      int  m_iDib;


      copydesk();
      ~copydesk() override;


      DECLARE_MESSAGE_HANDLER(_001OnClipboardUpdate);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      
      void install_message_routing(::channel * pchannel) override;


      void initialize_copydesk(::windowing::window * pwindow) override;
      void destroy() override;


      virtual void OnClipboardUpdate();

      virtual ::count _get_file_count();
      virtual int _get_priority_text_format();


      virtual HGLOBAL hglobal_get_filea(const ::file::patha & stra);
      virtual HGLOBAL hglobal_get_wide_text(const ::string & str);
      virtual HGLOBAL hglobal_get_utf8_text(const ::string & str);
      virtual HGLOBAL hglobal_get_image(const ::image * pimage);


      void _set_filea(const ::file::patha & stra, e_op eop) override;
      void _get_filea(::file::patha & stra, e_op & eop) override;
      bool _has_filea() override;


      void _set_plain_text(const ::string & str) override;
      void _get_plain_text(string & str) override;
      bool _has_plain_text() override;


      void _desk_to_image(::image * pimage) override;
      void _image_to_desk(const ::image * pimage) override;
      bool _has_image() override;


   };


} // namespace windowing_win32



