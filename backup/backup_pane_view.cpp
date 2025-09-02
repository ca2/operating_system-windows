#include "framework.h"
#include "aura/update.h"


namespace backup
{


   pane_impact::pane_impact(::particle * pparticle) :
      ::object(pobject),
      ::userex::pane_tab_impact(pobject),
      ::user::tab_impact(pobject),
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


   void pane_impact::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      add_tab("backup", impact_backup);
      add_tab("Options", OPTIONS_IMPACT);

      set_current_tab_by_id(impact_backup);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::tab_impact::handle(ptopic, phandlercontext);

   }


   void pane_impact::on_create_impact(::user::impact_data * pcreatordata)
   {

      switch(pcreatordata->id())
      {
      case impact_backup:
      {
         pcreatordata->m_puserinteraction = create_impact < impact > ();
         if(pcreatordata->m_puserinteraction != nullptr)
         {
            pcreatordata->m_pdocument = get_document();
         }
      }
      break;
      case OPTIONS_IMPACT:
      {
         ::pointer<::user::document>pdocument = papplication->create_form(this, this);
         if(pdocument == nullptr)
            return;
         ::pointer<::user::impact>pimpact = pdocument->get_impact();
         auto pupdate = new_update();
         pupdate->m_actioncontext = ::e_source_system;
         ptopic->id() = id_browse;
         ptopic->payload(id_form) = "filemanager\\replace_name_in_file_system.xhtml";
         pdocument->update_all_impacts(ptopic);

         ptopic->id() = id_get_form_impact;
         pdocument->update_all_impacts(ptopic);

         ptopic->id() = id_after_browse;
         pdocument->update_all_impacts(ptopic);


         pcreatordata->m_puserinteraction = (pimpact->get_parent_frame());
//         ::pointer<form_child_frame>pframe = (pcreatordata->m_puserinteraction);
         pcreatordata->m_pdocument = pdocument;

      }
      break;
      default:
         ASSERT(false);
         break;
      }

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_impact::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &pane_impact::_001OnCreate);
   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::userex::pane_tab_impact::handle(ptopic, phandlercontext);

      if (ptopic->m_bRet)
      {

         return;

      }

      ::production::form_callback::handle(ptopic, phandlercontext);

      if (ptopic->m_bRet)
      {

         return;

      }

   }


} // namespace backup




