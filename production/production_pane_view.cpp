#include "framework.h"
#include "aura/update.h"


namespace production
{


   pane_impact::pane_impact(::particle * pparticle) :
      ::object(pobject),
      ::user::tab_impact(pobject),
      ::userex::pane_tab_impact(pobject),
      place_holder_container(pobject)
   {

   }


   pane_impact::~pane_impact()
   {

   }




#ifdef DEBUG
   void pane_impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void pane_impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_impact message handlers

   void pane_impact::_001OnCreate(::message::message * pmessage)
   {
//      ::pointer<::message::create>pcreate(pmessage);
      if(pmessage->previous())
         return;

      add_tab("Production", MAIN_IMPACT);
      add_tab("Options", impact_configuration);

      set_current_tab_by_id(MAIN_IMPACT);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::tab_impact::handle(ptopic, pcontext);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

   }



   bool pane_impact::pre_create_window(::user::system * pusersystem)
   {
      pusersystem->m_createstruct.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(pusersystem);
   }


   void pane_impact::on_create_impact(::user::impact_data * pcreatordata)
   {
      switch(pcreatordata->id())
      {
      case CONTEXT_MENU_IMPACT:
      {
         /*::pointer<::filemanager::manager>pdocument = puser->filemanager()->open_child_list(false, true);
         if(pdocument != nullptr)
         {
            pdocument->get_filemanager_data()->m_iIconSize = 16;
            pdocument->get_filemanager_data()->m_bListText = true;
            pdocument->get_filemanager_data()->m_bListSelection = false;
            pdocument->get_filemanager_template()->m_strFilePopup = "filemanager\\file_popup.xml";
            pdocument->get_filemanager_data()->m_strDataKey = "production_menu";
            pdocument->get_filemanager_data()->m_pcallback = this;
            pdocument->Initialize(true);
            pdocument->update_all_impacts(nullptr, 1234);
            pdocument->update_all_impacts(nullptr, 123458);
            ::pointer<::user::impact>pimpact = pdocument->get_impact();
            pdocument->FileManagerBrowse(dir().appdata()/ "production/menu", ::e_source_system);
            if(pimpact != nullptr)
            {
               ::pointer<::user::frame_window>pframe =  (pimpact->get_parent_frame());
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
         ::pointer<::user::interaction>puie = ::user::impact::create_impact < ::production::impact > (pcreatordata);
         if(puie != nullptr)
         {
            pcreatordata->m_pdocument = get_document();
         }
         pcreatordata->m_eflag.add(::user::e_flag_hide_all_others_on_show);
      }
      break;
      /*      case PaneViewFileManager:
               {
                  ::pointer<::create>cc(get_application());
                  cc->m_bMakeVisible = false;
                  cc->m_bTransparentBackground = true;
                  cc->m_puserinteractionParent = this;

                  get_document()->m_pfilemanagerdoc = Sess(papp).filemanager()->open(papp, cc);
                  ::pointer<::filemanager::manager>pdocument = get_document()->m_pfilemanagerdoc;
                  if(pdocument != nullptr)
                  {
                     pdocument->get_filemanager_data()->m_strDataKeyModifier = "production_filemanager";
                     pdocument->Initialize(true);
                     pdocument->update_all_impacts(nullptr, 1234);
                     pdocument->update_all_impacts(nullptr, 123458);
                     ::pointer<::user::impact>pimpact = pdocument->get_impact();
                     if(pimpact != nullptr)
                     {
                        ::pointer<::user::frame_window>pframe =  (pimpact->get_parent_frame());
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
      //   ::pointer<::filemanager::manager>pdocument = puser->filemanager()->open_child_list(false, true);
      //   if(pdocument != nullptr)
      //   {
      //      pdocument->get_filemanager_data()->m_iIconSize = 48;
      //      pdocument->get_filemanager_data()->m_bListText = false;
      //      pdocument->get_filemanager_data()->m_bListSelection = false;
      //      pdocument->get_filemanager_data()->m_pcallback = this;
      //      pdocument->get_filemanager_data()->m_strDataKey = "production_3-action-launch";
      //      pdocument->Initialize(true);
      //      pdocument->update_all_impacts(nullptr, 1234);
      //      pdocument->update_all_impacts(nullptr, 123458);
      //      ::pointer<::user::impact>pimpact = pdocument->get_impact();
      //      pdocument->FileManagerBrowse(dir().appdata()/ "production\\3-action-launch", ::e_source_system);
      //      if(pimpact != nullptr)
      //      {
      //         ::pointer<::user::frame_window>pframe =  (pimpact->get_parent_frame());
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
         ::pointer<::user::document>pdocument = papplication->create_form(this, pcreatordata->m_pholder);
         if(pdocument == nullptr)
            return;
         ::pointer<::user::impact>pimpact = pdocument->get_impact();
         m_pviewOptions =  (pimpact);

         m_pviewOptions->m_pcallback = this;

         auto pupdate = topic(id_browse);
         pupdate->m_actioncontext = ::e_source_system;
         ptopic->id() = ;
         ptopic->payload(id_form) = "production\\options.xhtml";
         pdocument->update_all_impacts(ptopic);

         ptopic->id() = id_get_form_impact;
         pdocument->update_all_impacts(ptopic);

         ptopic->id() = id_after_browse;
         pdocument->update_all_impacts(ptopic);


         pcreatordata->m_puserinteraction = (pimpact->get_parent_frame());
         ::pointer<form_child_frame>pframe = (pcreatordata->m_puserinteraction);
         pcreatordata->m_pdocument = pdocument;
         //pcreatordata->m_puserinteraction = pframe;

      }
      break;
      default:
         break;
      }
      ::userex::pane_tab_impact::on_create_impact(pcreatordata);
   }




   void pane_impact::_001OnMenuMessage(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      set_current_tab_by_id(m_pimpactdataOld->id());
   }

   void pane_impact::install_message_routing(::channel * pchannel)
   {
      ::user::tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(WM_USER, pchannel, this, &pane_impact::_001OnUserMessage);
      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::_001OnCreate);
      //	MESSAGE_LINK(e_message_size, pchannel, this, &pane_impact::on_message_size);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &pane_impact::_001OnMenuMessage);


   }


   void pane_impact::OnFileManagerOpenFile(
   ::filemanager::data * pdata,
   ::file::item_array & itema)
   {
      __UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         pcontext->os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
      }
      get_parent_frame()->hide();
   }

   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {
      if(ptopic->id() == ::id_set_check)
      {
         if(ptopic->user_interaction_id() == "clean")
         {
            ::pointer<::user::interaction>pinteraction = m_pviewOptions->get_child_by_id("clean");
            ::pointer<::user::check_box>pcheckbox =  (pinteraction);
            auto ptopic = topic(id_clean);
            ptopic->payload(id_clean) = pcheckbox->echeck() == ::e_check_checked;
            get_document()->update_all_impacts(ptopic);
         }
         else if(ptopic->user_interaction_id() == "build")
         {
            ::pointer<::user::interaction>pinteraction = m_pviewOptions->get_child_by_id("build");
            ::pointer<::user::check_box>pcheckbox =  (pinteraction);
            auto ptopic = new_action(id_build);
            ptopic->payload(id_build) = pcheckbox->echeck() == ::e_check_checked;
            get_document()->update_all_impacts(ptopic);

         }

      }

   }


   ::pointer<::production::document>pane_impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   void pane_impact::_001OnUserMessage(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);
      if(pusermessage->m_wparam == 1)
      {
         set_current_tab_by_id("tabbed_file_manager");
      }
   }


} // namespace production




