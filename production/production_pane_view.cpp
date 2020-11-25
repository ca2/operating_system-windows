#include "framework.h"
#include "aura/update.h"


namespace production
{


   pane_view::pane_view(::layered * pobjectContext) :
      ::object(pobject),
      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {

   }


   pane_view::~pane_view()
   {

   }




#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(::message::message * pmessage)
   {
//      SCAST_PTR(::message::create, pcreate, pmessage);
      if(pmessage->previous())
         return;

      add_tab("Production", MAIN_IMPACT);
      add_tab("Options", impact_configuration);

      set_cur_tab_by_id(MAIN_IMPACT);

   }


   void pane_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::tab_view::on_subject(psubject, pcontext);

   }


   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();

   }



   bool pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_impact(::user::impact_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case CONTEXT_MENU_IMPACT:
      {
         /*__pointer(::filemanager::manager) pdocument = puser->filemanager()->open_child_list(false, true);
         if(pdocument != nullptr)
         {
            pdocument->get_filemanager_data()->m_iIconSize = 16;
            pdocument->get_filemanager_data()->m_bListText = true;
            pdocument->get_filemanager_data()->m_bListSelection = false;
            pdocument->get_filemanager_template()->m_strFilePopup = "filemanager\\file_popup.xml";
            pdocument->get_filemanager_data()->m_datakey = "production_menu";
            pdocument->get_filemanager_data()->m_pcallback = this;
            pdocument->Initialize(true);
            pdocument->update_all_views(nullptr, 1234);
            pdocument->update_all_views(nullptr, 123458);
            __pointer(::user::impact) pview = pdocument->get_view();
            pdocument->FileManagerBrowse(Context.dir().appdata()/ "production/menu", ::source_system);
            if(pview != nullptr)
            {
               __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
               if(pframe != nullptr)
               {
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  pframe->SetParent(this);
                  pcreatordata->m_pdocument = pdocument;
                  pcreatordata->m_puserinteraction = pframe;
               }
            }
         }*/
      }
      break;
      case MAIN_IMPACT:
      {
         __pointer(::user::interaction) puie = ::user::impact::create_view < ::production::view > (pcreatordata);
         if(puie != nullptr)
         {
            pcreatordata->m_pdocument = get_document();
         }
         pcreatordata->m_eflag.add(::user::flag_hide_all_others_on_show);
      }
      break;
      /*      case PaneViewFileManager:
               {
                  __pointer(::create) cc(get_context_application());
                  cc->m_bMakeVisible = false;
                  cc->m_bTransparentBackground = true;
                  cc->m_puserinteractionParent = this;

                  get_document()->m_pfilemanagerdoc = Sess(papp).filemanager()->open(papp, cc);
                  __pointer(::filemanager::manager) pdocument = get_document()->m_pfilemanagerdoc;
                  if(pdocument != nullptr)
                  {
                     pdocument->get_filemanager_data()->m_strDataKeyModifier = "production_filemanager";
                     pdocument->Initialize(true);
                     pdocument->update_all_views(nullptr, 1234);
                     pdocument->update_all_views(nullptr, 123458);
                     __pointer(::user::impact) pview = pdocument->get_view();
                     if(pview != nullptr)
                     {
                        __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
                        if(pframe != nullptr)
                        {
                           //pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                           //pframe->set_parent(this);
                           pcreatordata->m_pdocument = pdocument;
                           pcreatordata->m_puserinteraction = pframe;
                        }
                     }
                  }
               }
               break;*/
      //case impact_three_action_launch:
      //{
      //   __pointer(::filemanager::manager) pdocument = puser->filemanager()->open_child_list(false, true);
      //   if(pdocument != nullptr)
      //   {
      //      pdocument->get_filemanager_data()->m_iIconSize = 48;
      //      pdocument->get_filemanager_data()->m_bListText = false;
      //      pdocument->get_filemanager_data()->m_bListSelection = false;
      //      pdocument->get_filemanager_data()->m_pcallback = this;
      //      pdocument->get_filemanager_data()->m_datakey = "production_3-action-launch";
      //      pdocument->Initialize(true);
      //      pdocument->update_all_views(nullptr, 1234);
      //      pdocument->update_all_views(nullptr, 123458);
      //      __pointer(::user::impact) pview = pdocument->get_view();
      //      pdocument->FileManagerBrowse(Context.dir().appdata()/ "production\\3-action-launch", ::source_system);
      //      if(pview != nullptr)
      //      {
      //         __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
      //         if(pframe != nullptr)
      //         {
      //            pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
      //            pframe->SetParent(this);
      //            pcreatordata->m_pdocument = pdocument;
      //            pcreatordata->m_puserinteraction = pframe;
      //         }
      //      }
      //   }
      //}
      //break;
      case impact_configuration:
      {
         __pointer(::user::document) pdocument = Application.create_form(this, pcreatordata->m_pholder);
         if(pdocument == nullptr)
            return;
         __pointer(::user::impact) pview = pdocument->get_view();
         m_pviewOptions =  (pview);

         m_pviewOptions->m_pcallback = this;

         auto pupdate = new_action(id_browse);
         pupdate->m_actioncontext = ::source_system;
         psubject->id() = ;
         psubject->value(id_form) = "production\\options.xhtml";
         pdocument->update_all_views(psubject);

         psubject->id() = id_get_form_view;
         pdocument->update_all_views(psubject);

         psubject->id() = id_after_browse;
         pdocument->update_all_views(psubject);


         pcreatordata->m_puserinteraction = (pview->GetParentFrame());
         __pointer(form_child_frame) pframe = (pcreatordata->m_puserinteraction);
         pcreatordata->m_pdocument = pdocument;
         //pcreatordata->m_puserinteraction = pframe;

      }
      break;
      default:
         break;
      }
      ::userex::pane_tab_view::on_create_impact(pcreatordata);
   }




   void pane_view::_001OnMenuMessage(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      set_cur_tab_by_id(m_pimpactdataOld->m_id);
   }

   void pane_view::install_message_routing(::channel * pchannel)
   {
      ::user::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(WM_USER, pchannel, this, &pane_view::_001OnUserMessage);
      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::_001OnCreate);
      //	MESSAGE_LINK(e_message_size, pchannel, this, &pane_view::_001OnSize);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &pane_view::_001OnMenuMessage);


   }


   void pane_view::OnFileManagerOpenFile(
   ::filemanager::data * pdata,
   ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         Context.os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
      }
      GetParentFrame()->hide();
   }

   void pane_view::on_control_event(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_set_check)
      {
         if(pevent->m_puie->m_id == "clean")
         {
            __pointer(::user::interaction) pinteraction = m_pviewOptions->get_child_by_id("clean");
            __pointer(::user::check_box) pcheckbox =  (pinteraction);
            auto psubject = new_action(id_clean);
            psubject->value(id_clean) = pcheckbox->echeck() == ::check_checked;
            get_document()->update_all_views(psubject);
         }
         else if(pevent->m_puie->m_id == "build")
         {
            __pointer(::user::interaction) pinteraction = m_pviewOptions->get_child_by_id("build");
            __pointer(::user::check_box) pcheckbox =  (pinteraction);
            auto psubject = new_action(id_build);
            psubject->value(id_build) = pcheckbox->echeck() == ::check_checked;
            get_document()->update_all_views(psubject);

         }

      }

   }


   __pointer(::production::document) pane_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void pane_view::_001OnUserMessage(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(pbase->m_wparam == 1)
      {
         set_cur_tab_by_id("tabbed_file_manager");
      }
   }


} // namespace production




