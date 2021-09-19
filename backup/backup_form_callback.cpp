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
      __UNREFERENCED_PARAMETER(psubject);
   }


   void form_callback::handle(::subject * psubject, ::context * pcontext)
   {

      auto pview = psubject->get_form();

      if(psubject->m_id == ::e_subject_click)
      {
         if(psubject->m_puserinteraction->m_id == "lfs")
         {
            auto pupdate = new_update();
            pupdate->m_actioncontext = ::e_source_system;
            psubject->id() = id_browse;
            psubject->payload(id_form) = "filemanager_add_location_lfs.xhtml";
            dynamic_cast < ::user::form_view * > (pview)->get_document()->update_all_views(psubject);
            auto pinteraction = pview->get_child_by_name("lfs");
            
            string strPath;
            pinteraction->_001SetText(strPath, pupdate->m_actioncontext);

            psubject->Ret();

            return;


         }
         else if(psubject->m_puserinteraction->m_id == "ftp")
         {
            auto pupdate = new_update();
            pupdate->m_actioncontext = ::e_source_system;
            psubject->id() = id_browse;
            psubject->payload(id_form) = "filemanager_add_location_ftp.xhtml";
            dynamic_cast < ::user::form_view * > (pview)->get_document()->update_all_views(psubject);
            psubject->Ret();

            return;


         }
         else if(psubject->m_puserinteraction->m_id == "submit")
         {
            /*         if(pview->m_strPathName == "filemanager_add_location_lfs.xhtml")
                     {
                        string_array wstra;
                        //VmsDataGet(m_pmanager->get_filemanager_template()->m_datakeyStatic, 0, 0, wstra);
                        Ex1VirtualGuie * pinteraction = pview->get_child_by_name("lfs");
                        __pointer(::user::edit_text) ptext =pinteraction;
                        string str;
                        ptext->_001GetText(str);
                        wstra.AddUnique(str);
                        //VmsDataSet(m_pmanager->get_filemanager_template()->m_datakeyStatic, 0, 0, wstra);

                     }
                     else if(pview->m_strPathName == "filemanager_add_location_ftp.xhtml")
                     {
                     }
                     else if(pview->m_strPathName == "filemanager\\replace_name_in_file_system.xhtml")
                     {
                        auto pupdate = new_update();
                        Ex1VirtualGuieInterface * pinteraction = pview->get_child_by_name("encontrar");
                        __pointer(::user::edit_text) ptext =pinteraction;
                        //ptext->_001GetText(update.m_strFind);
                        pinteraction = pview->get_child_by_name("substituir");
                        ptext =pinteraction;
                        //ptext->_001GetText(update.m_strReplace);
                        pview->get_document()->update_all_views(psubject);
                     }*/
            psubject->Ret();

            return;

         }

      }

   }


} // namespace backup




