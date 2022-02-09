#include "framework.h"
#include "aura/update.h"


namespace backup
{


   pane_view::pane_view(::object * pobject) :
      ::object(pobject),
      ::userex::pane_tab_view(pobject),
      ::user::tab_view(pobject),
      place_holder_container(pobject)
   {


   }


   pane_view::~pane_view()
   {
   }


#ifdef DEBUG
   void pane_view::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG


   void pane_view::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      add_tab("backup", impact_backup);
      add_tab("Options", OPTIONS_IMPACT);

      set_current_tab_by_id(impact_backup);

   }


   void pane_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::tab_view::handle(ptopic, pcontext);

   }


   void pane_view::on_create_impact(::user::impact_data * pcreatordata)
   {

      switch(pcreatordata->m_atom)
      {
      case impact_backup:
      {
         pcreatordata->m_puserinteraction = create_view < impact > ();
         if(pcreatordata->m_puserinteraction != nullptr)
         {
            pcreatordata->m_pdocument = get_document();
         }
      }
      break;
      case OPTIONS_IMPACT:
      {
         __pointer(::user::document) pdocument = papplication->create_form(this, this);
         if(pdocument == nullptr)
            return;
         __pointer(::user::impact) pview = pdocument->get_view();
         auto pupdate = new_update();
         pupdate->m_actioncontext = ::e_source_system;
         ptopic->m_atom = id_browse;
         ptopic->_extended_topic()->payload(id_form) = "filemanager\\replace_name_in_file_system.xhtml";
         pdocument->update_all_views(ptopic);

         ptopic->m_atom = id_get_form_view;
         pdocument->update_all_views(ptopic);

         ptopic->m_atom = id_after_browse;
         pdocument->update_all_views(ptopic);


         pcreatordata->m_puserinteraction = (pview->get_parent_frame());
//         __pointer(form_child_frame) pframe = (pcreatordata->m_puserinteraction);
         pcreatordata->m_pdocument = pdocument;

      }
      break;
      default:
         ASSERT(false);
         break;
      }

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_view::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::_001OnCreate);
   }


   void pane_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::userex::pane_tab_view::handle(ptopic, pcontext);

      if (ptopic->m_bRet)
      {

         return;

      }

      ::production::form_callback::handle(ptopic, pcontext);

      if (ptopic->m_bRet)
      {

         return;

      }

   }


} // namespace backup




