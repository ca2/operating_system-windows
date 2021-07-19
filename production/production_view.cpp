#include "framework.h"
#include "aura/update.h"
#include "acme/const/timer.h"


namespace production
{


   view::view(::object * pobject) :
      ::object(pobject),
      ::user::interaction(pobject),
      m_brushBkActive(e_create),
      m_brushBkInactive(e_create)
   {

      m_pproduction = nullptr;

      //pcontext->m_papexcontext->file().ftd("C:\\home2\\ca2os\\ca2_spa\\stage", "C:\\teste.fileset");


      m_iLineHeight = 1;
      m_bLayout = false;
      m_brushBkActive->create_solid(rgb(150, 255, 130));
      m_brushBkInactive->create_solid(rgb(128, 208, 120));
      LOGFONT lf;
      __memset(&lf, 0, sizeof(lf));

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


   view::~view()
   {

   }


   void view::install_message_routing(::channel * pchannel)
   {
      ::user::scroll_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &view::on_message_size);
      //MESSAGE_LINK(WM_PAINT, pchannel, this, &view::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::_001OnCreate);
      MESSAGE_LINK(WM_CONTEXTMENU, pchannel, this, &view::on_message_context_menu);
      //MESSAGE_LINK(WM_SETCURSOR, pchannel, this, &view::on_message_set_cursor);

      //   MESSAGE_LINK(e_message_lbutton_down, pchannel, this, &::user::interaction::_001OnLButtonDown);
      //   MESSAGE_LINK(e_message_lbutton_up, pchannel, this, &::user::interaction::_001OnLButtonUp);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &view::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &view::on_message_key_up);

      MESSAGE_LINK(e_message_lbutton_down, pchannel, this, &view::_001OnLButtonDown);
      MESSAGE_LINK(e_message_lbutton_up, pchannel, this, &view::_001OnLButtonUp);
      MESSAGE_LINK(e_message_rbutton_up, pchannel, this, &view::on_message_right_button_up);


      MESSAGE_LINK(WM_SHOWWINDOW, pchannel, this, &view::on_message_show_window);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::on_message_destroy);

      MESSAGE_LINK(WM_USER, pchannel, this, &view::_001OnUser);



   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   bool view::pre_create_window(::user::system * pusersystem)
   {
      pusersystem->m_createstruct.style &= ~WS_EX_CLIENTEDGE;
      return ::user::impact::pre_create_window(pusersystem);
   }

   


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {
      if(update == ::id_update_current_area)
      {

         SetTimer(::e_timer_update_current_area, 100, nullptr);

      }
      else if(psubject->id() == id_clean)
      {

         m_pproduction->m_bClean = psubject->payload(id_clean);

      }
      else if(psubject->id() == id_build)
      {

         m_pproduction->m_bBuild = psubject->payload(id_build);

      }

   }

   void view::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);
   }

   void view::on_message_size(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::size) psize(pmessage);

      ::rectangle_i32 rectDesktop;
      best_monitor(rectDesktop);

      m_iWScreen = rectDesktop.width();
      m_iHScreen = rectDesktop.height();
      ::rectangle_i32 rectangleClient = get_client_rect();
      //GetClientRect(rectangleClient);
      rectangleClient.deflate(2, 2);
      i32 iW = rectangleClient.width() / 2;
      i32 iH = rectangleClient.height() / 2;
      iH = minimum(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (i32) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (i32) (iH * rScreen);
      }
      m_iW = iW;
      m_iH = iH;
   }


   void view::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void view:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      single_lock synchronouslock(&m_pproduction->m_mutexStatus,true);

      ::rectangle_i32 rectangleClient = get_client_rect();
      //GetClientRect(rectangleClient);

      pgraphics->SelectObject(_001GetFont(::user::font_default));

//      auto sz = pgraphics->get_text_extent("qg");
      m_iLineHeight = maximum(1, pgraphics->get_current_font()->get_height());

      pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      ::rectangle_i32 rectText(rectangleClient);

      rectText.bottom -= 84;

      ::rectangle_i32 rcItem;

      ::point_i32 pointOffset = get_viewport_offset();

      i32 iStart = pointOffset.y / m_iLineHeight;
      i32 y = m_iLineHeight - pointOffset.y % m_iLineHeight;
      if(pointOffset.y > m_iLineHeight)
      {
         iStart--;
         y -= m_iLineHeight;
      }
      ::rectangle_i32 rectClip(rectText);
      //ClientToScreen(rectClip);
      ::draw2d::region_pointer rgnClip(e_create);
      rgnClip->create_rect(rectClip);
      //pgraphics->Draw3dRect(rectText, rgb(200, 200, 200), rgb(200, 200, 200));
      pgraphics->SelectClipRgn(rgnClip);
      //single_lock synchronouslock(&m_pproduction->m_mutexStatus, true);
      //pgraphics->set_color(argb(0xcc, 90, 90, 90));
      ::draw2d::brush_pointer brush(e_create);
      brush->create_solid(argb(0xcc, 90, 90, 90));
      pgraphics->SelectObject(brush);
      for(i32 i = iStart; i < m_pproduction->m_straStatus.get_size() && y < rectText.bottom; i++)
      {
         rcItem = rectText;
         rcItem.bottom = y + m_iLineHeight;
         rcItem.top = y ;
         pgraphics->draw_text(m_pproduction->m_straStatus[i], rcItem, e_align_bottom_left);
         y = rcItem.bottom;
      }
      pgraphics->SelectClipRgn(nullptr);



      ::rectangle_i32 rectArea;

      GetAreaThumbRect(rectArea, m_iV);
      if (m_pimageV)
      {

         m_pimageV->to(pgraphics, rectArea);

      }
      else
      {

         pgraphics->fill_rectangle(rectArea, argb(255, 100, 200, 255));
         pgraphics->set_text_color(argb(255, 255, 255, 255));

         pgraphics->draw_text("Production", rectArea, e_align_horizontal_center | e_align_vertical_center);

      }

      GetAreaThumbRect(rectArea, m_iVs);
      if (m_pimageVs)
      {
/*         m_pimage->to(pgraphics, rectArea);

      }

      if(!m_pproduction->m_bFinished)
      {
         string strTime;
         auto dwMin = (m_pproduction->m_tickEnd - m_pproduction->m_tickStart) / 1000 / 60;
         auto dwSeg = ((m_pproduction->m_tickEnd - m_pproduction->m_tickStart) / 1000) % 60;
         strTime.Format("%dm %ds", dwMin, dwSeg);
         pgraphics->text_out(rectArea.right + 23, rectArea.top, strTime);
      }

   }

   void view::_001OnCreate(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      ::rectangle_i32 rectangle;
      //rectangle.null();

      //if(!m_pscrollbarHorizontal->create_window(
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

      //if(!m_pscrollbarVertical->create_window(
      // e_orientation_vertical,
      // WS_CHILD
      // | WS_VISIBLE,
      // rectangle,
      // this,
      // 1025))
      //  {
      // return;
      //  }

      SetTimer(31, 230, nullptr);
      SetTimer(3003, 300, nullptr);
      SetTimer(543218, 200, nullptr);
      //m_pimageV->load_image("wild_mountains_and_valleys-123.png");
      //pdraw2d->imaging().free(pfi);

/*      //m_pimage->load_image("bambu49transr.png");
      //pdraw2d->imaging().free(pfi);



      //make_production();


      m_pproduction = create_production();

      m_pproduction->m_pview  = this;


      papplication->m_pview = this;

      //m_pproduction->twitter_auth();
//      m_pproduction->twitter_twit("starting ca2 production application");




   }

   void view::on_message_key_down(::message::message * pmessage)
   {

   }


   void view::on_message_key_up(::message::message * pmessage)
   {
   }

   void view::on_message_context_menu(::message::message * pmessage)
   {
      __pointer(::message::context_menu) pcontextmenu(pmessage);
      ::point_i32 point = pcontextmenu->GetPoint();
   }


   void view::_001OnTabClick(i32 iTab)
   {
      if(iTab == 1)
      {
      }
   }


   void view::on_message_set_cursor(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::GetAreaThumbRect(LPRECT lprect, i32 iArea)
   {
      ::rectangle_i32 rectangleClient = get_client_rect();
      //GetClientRect(rectangleClient);
      if(iArea == m_iV)
      {
         lprect->bottom = rectangleClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_iVs)
      {
         lprect->bottom = rectangleClient.bottom;
         lprect->top = lprect->bottom - m_iVsH;
         lprect->left = 1 + m_iVW + 10;
         lprect->right = lprect->left + m_iVsW;
      }
   }

   void view::on_hit_test(::user::item & item)
   {

      ::rectangle_i32 rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if (rectArea.contains(item.m_pointHitTest))
      {
         item = {::user::e_element_area, m_iV   };
         return;
      }
      GetAreaThumbRect(rectArea, m_iVs);
      if(rectArea.contains(item.m_pointHitTest))
      {
         item = { ::user::e_element_area, m_iVs };
         return;
      }
      
      item = ::user::e_element_none;
   

   }


   void view::_001OnLButtonDown(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //    auto pmouse = pmessage->m_pmouse;

//      i32 iHitArea = hit_test(pmouse->m_point);

   }

   void view::_001OnLButtonUp(::message::message * pmessage)
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

   void view::on_message_right_button_up(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //    auto pmouse = pmessage->m_pmouse;

//      i32 iHitArea = hit_test(pmouse->m_point);
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




   void view::_001OnTimer(::timer * ptimer)
   {
      ::user::scroll_view::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == e_timer_update_current_area)
      {
         if(is_window_visible())
         {
            //set_need_redraw();
         }
      }
      else if(ptimer->m_uEvent == ::e_timer_update_current_area)
      {
         KillTimer(ptimer->m_uEvent);
      }
      else if(ptimer->m_uEvent == 5432180)
      {
         KillTimer(ptimer->m_uEvent);
      }
      else if(ptimer->m_uEvent == 3003)
      {
      }
      else if(ptimer->m_uEvent == 31)
      {
         if(!m_pproduction->m_bFinished)
         {
            m_pproduction->m_tickEnd = ::GetTickCount();
            set_need_redraw();
         }

      }
   }





   void view::on_message_show_window(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::show_window) pshowwindow(pmessage);
   }

   void view::make_production()
   {
      m_iStep = 1;
      __pointer(application) papp =  (get_application());
      m_pproduction->start_production(papp->m_eversion);
   }


   void view::production_loop(i32 iLoopCount)
   {
      m_iStep = 1;
      __pointer(application) papp =  (get_application());
      m_pproduction->start_loop(papp->m_eversion, iLoopCount);
   }

   void view::release_production()
   {

      production_loop(1);

   }


   void view::_001OnUser(::message::message * pmessage)
   {
      __pointer(::user::message) pusermessage(pmessage);
      if(pusermessage->m_wparam == 1)
      {
         i32 iLineHeight = m_iLineHeight;
         {
            single_lock synchronouslock(&m_pproduction->m_mutexStatus,true);
            if(m_pproduction->m_straStatus.get_size() > 0)
            {
               ::size_i32 sizePage = get_page_size();
               m_sizeTotal.cx = 80;
               m_sizeTotal.cy = (LONG)(m_pproduction.m_straStatus.get_size() * iLineHeight + 84);
               synchronouslock.unlock();
               set_viewport_offset_y(maximum(0,m_sizeTotal.cy - sizePage.cy + iLineHeight));
               on_change_view_size();
            }
            else
            {
               m_sizeTotal.cx = 80;
               m_sizeTotal.cy = 80;
            }
         }
         set_need_redraw();
      }
      else if(pusermessage->m_wparam == 2)
      {

         string_array stra;
         string_array straRelative;
         string_array straTitle;
         string strRemote;

         __pointer(pane_view) pview = GetTypedParent < pane_view > ();

         pview->set_current_tab_by_id("filemanager::tabbed");

         __pointer(::filemanager::document) pdocument = pview->m_pfilemanagerTabbed;

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
            __pointer(pane_view) pview = GetTypedParent < pane_view > ();
            pview->set_current_tab_by_id(MAIN_IMPACT);
            m_pproduction->step();
         }
      }
   }

   production * view::create_production()
   {
      production * pclass = new production(get_application());
      pclass->m_eversion = papplication->m_eversion;
      return pclass;
   }


   size_i32 view::get_total_size()
   {

      return m_sizeTotal;

   }


} // namespace production




