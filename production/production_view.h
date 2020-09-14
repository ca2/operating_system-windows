#pragma once


namespace production
{


   class document;


   class CLASS_DECL_CA2_PRODUCTION view :
      virtual public ::user::scroll_view
   {
   public:


      //size                          m_sizeTotal;
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
      ::draw2d::brush_pointer          m_brushBkActive;
      ::draw2d::brush_pointer          m_brushBkInactive;


      view(::layered * pobjectContext);
      virtual ~view();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
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
      void on_hit_test(::user::item & item);


      void release_production();
      void make_production();
      void production_loop(i32 iLoopCount);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnTabClick(i32 iTab);
      virtual void install_message_routing(::channel * pchannel);
      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void update(::update * pupdate) override;

      ::user::document * get_document();

      //virtual void update(::update * pupdate) override;
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      virtual void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnUser);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);


      virtual ::size get_total_size();


      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace production



