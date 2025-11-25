#include "framework.h"
#include "aura/update.h"
#include "acme/const/timer.h"


namespace production
{


   impact::impact(::particle * pparticle) :
      ::object(pobject),
      ::user::interaction(pobject),
      m_pbrushBkActive(e_create),
      m_pbrushBkInactive(e_create)
   {

      m_pproduction = nullptr;

      //file().ftd("C:\\home2\\ca2os\\ca2_spa\\stage", "C:\\teste.fileset");


      m_iLineHeight = 1;
      m_bLayout = false;
      m_pbrushBkActive->create_solid(rgb(150, 255, 130));
      m_pbrushBkInactive->create_solid(rgb(128, 208, 120));
      LOGFONT lf;
      memory_set(&lf, 0, sizeof(lf));

      wcscpy(lf.lfFaceName, L"Verdana");
      lf.lfHeight = 13;
      lf.lfHeight = 15;
      lf.lfWeight = 900;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_iVs = 124;
      m_iVsH = 49;
      m_iVsW = 41;

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {
      ::user::scroll_impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &impact::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_size, pchannel, this, &impact::on_message_size);
      //USER_MESSAGE_LINK(WM_PAINT, pchannel, this, &impact::_001OnPaint);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &impact::_001OnCreate);
      USER_MESSAGE_LINK(WM_CONTEXTMENU, pchannel, this, &impact::on_message_context_menu);
      //USER_MESSAGE_LINK(WM_SETCURSOR, pchannel, this, &impact::on_message_set_cursor);

      //   USER_MESSAGE_LINK(::user::e_message_lbutton_down, pchannel, this, &::user::interaction::_001OnLButtonDown);
      //   USER_MESSAGE_LINK(::user::e_message_lbutton_up, pchannel, this, &::user::interaction::_001OnLButtonUp);
      USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &impact::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_key_up, pchannel, this, &impact::on_message_key_up);

      USER_MESSAGE_LINK(::user::e_message_lbutton_down, pchannel, this, &impact::_001OnLButtonDown);
      USER_MESSAGE_LINK(::user::e_message_lbutton_up, pchannel, this, &impact::_001OnLButtonUp);
      USER_MESSAGE_LINK(::user::e_message_rbutton_up, pchannel, this, &impact::on_message_right_button_up);


      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &impact::on_message_show_window);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &impact::on_message_destroy);

      USER_MESSAGE_LINK(WM_USER, pchannel, this, &impact::_001OnUser);



   }

#ifdef DEBUG
   void impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   bool impact::pre_create_window(::user::system * pusersystem)
   {
      pusersystem->m_createstruct.style &= ~WS_EX_CLIENTEDGE;
      return ::user::impact::pre_create_window(pusersystem);
   }

   


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      if(update == ::id_update_current_area)
      {

         set_timer(::e_timer_update_current_area, 100, nullptr);

      }
      else if(ptopic->id() == id_clean)
      {

         m_pproduction->m_bClean = ptopic->payload(id_clean);

      }
      else if(ptopic->id() == id_build)
      {

         m_pproduction->m_bBuild = ptopic->payload(id_build);

      }

   }

   void impact::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);
   }

   void impact::on_message_size(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::size>psize(pmessage);

      ::int_rectangle rectangleDesktop;
      best_monitor(rectangleDesktop);

      m_iWScreen = rectangleDesktop.width();
      m_iHScreen = rectangleDesktop.height();
      ::int_rectangle rectangleX = this->rectangle();
      //GetClientRect(rectangleX);
      rectangleX.deflate(2, 2);
      int iW = rectangleX.width() / 2;
      int iH = rectangleX.height() / 2;
      iH = minimum(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectangleDesktop.width() / (double) rectangleDesktop.height();
      if(r < rScreen)
      {
         iH = (int) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (int) (iH * rScreen);
      }
      m_iW = iW;
      m_iH = iH;
   }


   void impact::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void impact:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      single_lock synchronouslock(&m_pproduction->m_mutexStatus,true);

      ::int_rectangle rectangleX = this->rectangle();
      //GetClientRect(rectangleX);

      pgraphics->SelectObject(_001GetFont(::user::font_default));

//      auto sz = pgraphics->get_text_extent("qg");
      m_iLineHeight = maximum(1, pgraphics->get_current_font()->get_height());

      pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

      ::int_rectangle rectangleText(rectangleX);

      rectangleText.bottom -= 84;

      ::int_rectangle rcItem;

      ::int_point pointOffset = get_context_offset();

      int iStart = pointOffset.y / m_iLineHeight;
      int y = m_iLineHeight - pointOffset.y % m_iLineHeight;
      if(pointOffset.y > m_iLineHeight)
      {
         iStart--;
         y -= m_iLineHeight;
      }
      ::int_rectangle rectangleClip(rectangleText);
      //ClientToScreen(rectangleClip);
      ::draw2d::region_pointer rgnClip(e_create);
      rgnClip->create_rect(rectangleClip);
      //pgraphics->Draw3dRect(rectangleText, rgb(200, 200, 200), rgb(200, 200, 200));
      pgraphics->SelectClipRgn(rgnClip);
      //single_lock synchronouslock(&m_pproduction->m_mutexStatus, true);
      //pgraphics->set_color(argb(0xcc, 90, 90, 90));
      auto pbrush = øcreate < ::draw2d::brush >();
      pbrush->create_solid(argb(0xcc, 90, 90, 90));
      pgraphics->SelectObject(brush);
      for(int i = iStart; i < m_pproduction->m_straStatus.get_size() && y < rectangleText.bottom; i++)
      {
         rcItem = rectangleText;
         rcItem.bottom = y + m_iLineHeight;
         rcItem.top = y ;
         pgraphics->draw_text(m_pproduction->m_straStatus[i], rcItem, e_align_bottom_left);
         y = rcItem.bottom;
      }
      pgraphics->SelectClipRgn(nullptr);



      ::int_rectangle rectangleArea;

      GetAreaThumbRect(rectangleArea, m_iV);
      if (m_pimageV)
      {

         m_pimageV->to(pgraphics, rectangleArea);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleArea, argb(255, 100, 200, 255));
         pgraphics->set_text_color(argb(255, 255, 255, 255));

         pgraphics->draw_text("Production", rectangleArea, e_align_horizontal_center | e_align_vertical_center);

      }

      GetAreaThumbRect(rectangleArea, m_iVs);
      if (m_pimageVs)
      {
/*         m_pimage->to(pgraphics, rectangleArea);

      }

      if(!m_pproduction->m_bFinished)
      {
         string strTime;
         auto dwMin = (m_pproduction->m_tickEnd - m_pproduction->m_tickStart) / 1000 / 60;
         auto dwSeg = ((m_pproduction->m_tickEnd - m_pproduction->m_tickStart) / 1000) % 60;
         strTime.Format("%dm %ds", dwMin, dwSeg);
         pgraphics->text_out(rectangleArea.right + 23, rectangleArea.top, strTime);
      }

   }

   void impact::_001OnCreate(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      ::int_rectangle rectangle;
      //rectangle.null();

      //if(!m_pscrollbarX->create_window(
      // e_orientation_horizontal,
      // WS_CHILD
      // | WS_VISIBLE,
      // rectangle,
      // this,
      // 1024))
      //  {
      // return;
      //  }

      //  rectangle.null();

      //if(!m_pscrollbarY->create_window(
      // e_orientation_vertical,
      // WS_CHILD
      // | WS_VISIBLE,
      // rectangle,
      // this,
      // 1025))
      //  {
      // return;
      //  }

      set_timer(31, 230, nullptr);
      set_timer(3003, 300, nullptr);
      set_timer(543218, 200, nullptr);
      //m_pimageV->load_image("wild_mountains_and_valleys-123.png");
      //pdraw2d->imaging().free(pfi);

/*      //m_pimage->load_image("bambu49transr.png");
      //pdraw2d->imaging().free(pfi);



      //make_production();


      m_pproduction = create_production();

      m_pproduction->m_pimpact  = this;


      papplication->m_pimpact = this;

      //m_pproduction->twitter_auth();
//      m_pproduction->twitter_twit("starting ca2 production application");




   }

   void impact::on_message_key_down(::message::message * pmessage)
   {

   }


   void impact::on_message_key_up(::message::message * pmessage)
   {
   }

   void impact::on_message_context_menu(::message::message * pmessage)
   {
      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      ::int_point point = pcontextmenu->GetPoint();
   }


   void impact::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
      }
   }


   void impact::on_message_set_cursor(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::GetAreaThumbRect(LPRECT lprect, int iArea)
   {
      ::int_rectangle rectangleX = this->rectangle();
      //GetClientRect(rectangleX);
      if(iArea == m_iV)
      {
         lprect->bottom = rectangleX.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_iVs)
      {
         lprect->bottom = rectangleX.bottom;
         lprect->top = lprect->bottom - m_iVsH;
         lprect->left = 1 + m_iVW + 10;
         lprect->right = lprect->left + m_iVsW;
      }
   }

   ::item_pointer impact::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      ::int_rectangle rectangleArea;
      GetAreaThumbRect(rectangleArea, m_iV);
      if (rectangleArea.contains(item.m_pointHitTest))
      {
         item = {::e_element_area, m_iV   };
         return;
      }
      GetAreaThumbRect(rectangleArea, m_iVs);
      if(rectangleArea.contains(item.m_pointHitTest))
      {
         item = { ::e_element_area, m_iVs };
         return;
      }
      
      item = ::e_element_none;
   

   }


   void impact::_001OnLButtonDown(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //    auto pmouse = pmessage->m_pmouse;

//      int iHitArea = hit_test(pmouse->m_point);

   }

   void impact::_001OnLButtonUp(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_pmouse;

      auto point = screen_to_client(pmouse->m_point);
      
      auto item = hit_test(pmouse);

      if(item == m_iV)
      {
         make_production();
      }
      else if(item == m_iVs)
      {
         make_production();
      }

   }

   void impact::on_message_right_button_up(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //    auto pmouse = pmessage->m_pmouse;

//      int iHitArea = hit_test(pmouse->m_point);
      /*   {
            ::aura::menu menu;
            menu.LoadXmlMenu(get_application(), "production\\popup_production.xml");
            menu.set_app(get_application());
            ::aura::menu menuPopup(menu.GetSubMenu(0));
            menuPopup.set_app(get_application());
            menuPopup.track_popup_menu(0, pmouse->m_point.x, pmouse->m_point.y, get_parent_frame().GetSafeoswindow_());
         }
        */
   }




   void impact::on_timer(::timer * ptimer)
   {
      ::user::scroll_impact::on_timer(ptimer);
      if(ptimer->m_uTimer == e_timer_update_current_area)
      {
         if(is_window_visible())
         {
            //set_need_redraw();
         }
      }
      else if(ptimer->m_uTimer == ::e_timer_update_current_area)
      {
         kill_timer(ptimer->m_uTimer);
      }
      else if(ptimer->m_uTimer == 5432180)
      {
         kill_timer(ptimer->m_uTimer);
      }
      else if(ptimer->m_uTimer == 3003)
      {
      }
      else if(ptimer->m_uTimer == 31)
      {
         if(!m_pproduction->m_bFinished)
         {
            m_pproduction->m_tickEnd = ::GetTickCount();
            set_need_redraw();
         }

      }
   }





   void impact::on_message_show_window(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::show_window>pshowwindow(pmessage);
   }

   void impact::make_production()
   {
      m_iStep = 1;
      ::pointer<application>papp =  (get_application());
      m_pproduction->start_production(papp->m_eversion);
   }


   void impact::production_loop(int iLoopCount)
   {
      m_iStep = 1;
      ::pointer<application>papp =  (get_application());
      m_pproduction->start_loop(papp->m_eversion, iLoopCount);
   }

   void impact::release_production()
   {

      production_loop(1);

   }


   void impact::_001OnUser(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);
      if(pusermessage->m_wparam == 1)
      {
         int iLineHeight = m_iLineHeight;
         {
            single_lock synchronouslock(&m_pproduction->m_mutexStatus,true);
            if(m_pproduction->m_straStatus.get_size() > 0)
            {
               ::int_size sizePage = get_page_size();
               m_sizeTotal.cx() = 80;
               m_sizeTotal.cy() = (LONG)(m_pproduction.m_straStatus.get_size() * iLineHeight + 84);
               synchronouslock.unlock();
               set_context_offset_y(maximum(0,m_sizeTotal.cy() - sizePage.cy() + iLineHeight));
               on_change_impact_size();
            }
            else
            {
               m_sizeTotal.cx() = 80;
               m_sizeTotal.cy() = 80;
            }
         }
         set_need_redraw();
      }
      else if(pusermessage->m_wparam == 2)
      {

         string_array_base stra;
         string_array_base straRelative;
         string_array_base straTitle;
         string strRemote;

         ::pointer<pane_impact>pimpact = get_typed_parent < pane_impact > ();

         pimpact->set_current_tab_by_id("filemanager::tabbed");

         ::pointer<::filemanager::document>pdocument = pimpact->m_pfilemanagerTabbed;

         string strBase = m_pproduction->m_strBase;

         m_iStep = 2;

         pdocument->get_operation_doc(true)->m_thread.queue_copy(
         m_pproduction->m_straFiles,
         "C:\\ca2\\vrel\\" + m_pproduction->m_strConfiguration + "\\" + m_pproduction->m_strFormatBuild,
         strBase,
         false,
         true,
         this);

         pdocument->get_operation_doc(true)->m_thread.kick();

      }
      else if(pusermessage->m_wparam == 0x1000)
      {
         if(m_iStep == 2)
         {
            ::pointer<pane_impact>pimpact = get_typed_parent < pane_impact > ();
            pimpact->set_current_tab_by_id(MAIN_IMPACT);
            m_pproduction->step();
         }
      }
   }

   production * impact::create_production()
   {
      production * pclass = ___new production(get_application());
      pclass->m_eversion = papplication->m_eversion;
      return pclass;
   }


   int_size impact::get_total_size()
   {

      return m_sizeTotal;

   }


} // namespace production




