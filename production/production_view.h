#pragma once


namespace production
{


   class document;


   class CLASS_DECL_CA2_PRODUCTION impact :
      virtual public ::user::scroll_view
   {
   public:


      //size_i32                          m_sizeTotal;
      i32                     m_iStep;
      bool                    m_bLayout;

      i32                     m_iLineHeight;

      production *      m_pproduction;
      tick m_tickLastSnapshotUpdate;
      i32                     m_iW;
      i32                     m_iH;
      i32                     m_iWScreen;
      i32                     m_iHScreen;
      i32                     m_iArea;
      i32                     m_iItemHeight;
      i32                     m_iTaskOffset;

      ::index                     m_iV;
      i32                     m_iVH;
      i32                     m_iVW;
      // veriwell ca2os ca2 out world stage
      ::index                     m_iVs;
      i32                     m_iVsH;
      i32                     m_iVsW;
      ::image_pointer             m_pimageV;
      ::image_pointer             m_pimageVs;
      ::draw2d::brush_pointer          m_pbrushBkActive;
      ::draw2d::brush_pointer          m_pbrushBkInactive;


      impact(::object * pobject);
      virtual ~impact();
#ifdef DEBUG
      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;
#endif

      enum e_message
      {
         MessageOp = WM_USER + 1123,
      };

      enum EOp
      {
         OpUpdateCurrentArea,
      };


      virtual production * create_production();





      void GetAreaThumbRect(LPRECT lprect, i32 iArea);
      void on_hit_test(::item & item);


      void release_production();
      void make_production();
      void production_loop(i32 iLoopCount);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnTabClick(i32 iTab);
      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem);
      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      //virtual void handle(::topic * ptopic, ::context * pcontext) override;
      DECLARE_MESSAGE_HANDLER(_001OnLButtonDown);
      DECLARE_MESSAGE_HANDLER(_001OnLButtonUp);
      virtual void _001OnTimer(::timer * ptimer);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnCreate);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnUser);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);


      virtual ::size_i32 get_total_size();


      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace production



