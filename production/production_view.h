#pragma once


namespace production
{


   class document;


   class CLASS_DECL_CA2_PRODUCTION impact :
      virtual public ::user::scroll_impact
   {
   public:


      //int_size                          m_sizeTotal;
      int                     m_iStep;
      bool                    m_bLayout;

      int                     m_iLineHeight;

      production *      m_pproduction;
      tick m_tickLastSnapshotUpdate;
      int                     m_iW;
      int                     m_iH;
      int                     m_iWScreen;
      int                     m_iHScreen;
      int                     m_iArea;
      int                     m_iItemHeight;
      int                     m_iTaskOffset;

      ::collection::index                     m_iV;
      int                     m_iVH;
      int                     m_iVW;
      // veriwell ca2os ca2 out world stage
      ::collection::index                     m_iVs;
      int                     m_iVsH;
      int                     m_iVsW;
      ::image::image_pointer             m_pimageV;
      ::image::image_pointer             m_pimageVs;
      ::draw2d::brush_pointer          m_pbrushBkActive;
      ::draw2d::brush_pointer          m_pbrushBkInactive;


      impact(::particle * pparticle);
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





      void GetAreaThumbRect(LPRECT lprect, int iArea);
      void on_hit_test(::item & item);


      void release_production();
      void make_production();
      void production_loop(int iLoopCount);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnTabClick(int iTab);
      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem);
      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      //void handle(::topic * ptopic, ::context * pcontext) override;
      DECLARE_MESSAGE_HANDLER(_001OnLButtonDown);
      DECLARE_MESSAGE_HANDLER(_001OnLButtonUp);
      virtual void on_timer(::timer * ptimer);
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


      virtual ::int_size get_total_size();


      virtual void on_context_offset(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace production



