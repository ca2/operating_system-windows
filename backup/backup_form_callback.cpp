#include "framework.h"
#include "aura/update.h"


namespace backup
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::update(::user::form * pform, ::update & update)
   {
      __UNREFERENCED_PARAMETER(pform);
      __UNREFERENCED_PARAMETER(ptopic);
   }


   void form_callback::handle(::topic * ptopic, ::context * pcontext)
   {

      //auto pimpact = ptopic->get_form();

      if(ptopic->m_atom == ::id_click)
      {
         if(ptopic->user_element_id() == "lfs")
         {
            auto pupdate = new_update();
            pupdate->m_actioncontext = ::e_source_system;
            ptopic->m_atom = id_browse;
            ptopic->payload(id_form) = "filemanager_add_location_lfs.xhtml";
            dynamic_cast < ::user::form_impact * > (pimpact)->get_document()->update_all_impacts(ptopic);
            auto pinteraction = pimpact->get_child_by_name("lfs");
            
            string strPath;
            pinteraction->_001SetText(strPath, pupdate->m_actioncontext);

            ptopic->Ret();

            return;


         }
         else if(ptopic->user_element_id() == "ftp")
         {
            auto pupdate = new_update();
            pupdate->m_actioncontext = ::e_source_system;
            ptopic->m_atom = id_browse;
            ptopic->payload(id_form) = "filemanager_add_location_ftp.xhtml";
            dynamic_cast < ::user::form_impact * > (pimpact)->get_document()->update_all_impacts(ptopic);
            ptopic->Ret();

            return;


         }
         else if(ptopic->user_element_id() == "submit")
         {
            /*         if(pimpact->m_strPathName == "filemanager_add_location_lfs.xhtml")
                     {
                        string_array wstra;
                        //VmsDataGet(m_pmanager->get_filemanager_template()->m_datakeyStatic, 0, 0, wstra);
                        Ex1VirtualGuie * pinteraction = pimpact->get_child_by_name("lfs");
                        __pointer(::user::edit_text) ptext =pinteraction;
                        string str;
                        ptext->_001GetText(str);
                        wstra.AddUnique(str);
                        //VmsDataSet(m_pmanager->get_filemanager_template()->m_datakeyStatic, 0, 0, wstra);

                     }
                     else if(pimpact->m_strPathName == "filemanager_add_location_ftp.xhtml")
                     {
                     }
                     else if(pimpact->m_strPathName == "filemanager\\replace_name_in_file_system.xhtml")
                     {
                        auto pupdate = new_update();
                        Ex1VirtualGuieInterface * pinteraction = pimpact->get_child_by_name("encontrar");
                        __pointer(::user::edit_text) ptext =pinteraction;
                        //ptext->_001GetText(update.m_strFind);
                        pinteraction = pimpact->get_child_by_name("substituir");
                        ptext =pinteraction;
                        //ptext->_001GetText(update.m_strReplace);
                        pimpact->get_document()->update_all_impacts(ptopic);
                     }*/
            ptopic->Ret();

            return;

         }

      }

   }


} // namespace backup




