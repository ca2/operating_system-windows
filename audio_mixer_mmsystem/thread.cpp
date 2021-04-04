#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      thread::thread()
      {

         m_bPendingShowCommand = false;

      }


      thread::~thread()
      {


      }


      ::e_status thread::init_thread()
      {

//         set_auto_delete(false);

         return true;

      }


      void thread::term_thread()
      {
         // TODO:  perform any per-thread cleanup here
         //    CVMSApp * pApp = (CVMSApp *) System;
         //MessageFilterHookManager * pmfmh;
         //MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh);
         //pmfmh->MessageFilterUnhook();

         CoUninitialize();

         ::thread::term_thread();

      }


      void thread::install_message_routing(::channel * pchannel)
      {
         MESSAGE_LINK(thread::MessageMixerThread, pchannel, this, &thread::OnMixerMessage);
         MESSAGE_LINK(WM_USER, pchannel, this, &thread::OnUserMessage);
      }

      // BEGIN_MESSAGE_MAP(thread, thread)
      //{{AFX_MSG_MAP(thread)
      // NOTE - the ClassWizard will add and erase mapping macros here.
      //}}AFX_MSG_MAP
      //    ON_THREAD_MESSAGE(thread::MessageMixerThread, OnMixerMessage)
      /* xxx   ON_THREAD_MESSAGE(VMSM_V001, OnVmsmV001)
      ON_THREAD_MESSAGE(VMSM_EXCEPTION, OnVmsmException) */
      //    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
      // END_MESSAGE_MAP()

      /////////////////////////////////////////////////////////////////////////////
      // thread message handlers


      void thread::OnMixerMessage(::message::message * pmessage)
      {
         __pointer(::user::message) pusermessage(pmessage);

         if(pusermessage->m_wparam ==  23)
         {
         }
         else if(pusermessage->m_wparam ==  21)
         {
         }
         else if(pusermessage->m_wparam == 19)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumDeleteNotFound |
            //    CDataCentral::eBuildSongsAlbumAddNew |
            //  CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //false, this, this);
         }
         else if(pusermessage->m_wparam == 20)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumAddNew |
            //    CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //  true, this, this);
         }
         else if(pusermessage->m_wparam == 810)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      CDataCentral::eBuildSongsAlbumDeleteNotFound,
            //    false, this, this);
         }
         else if(pusermessage->m_wparam == 20191817)
         {
            ASSERT(false);
         }
         else if(pusermessage->m_wparam == 67985)
         {
            ASSERT(false);
            //        m_pMixerDocTemplate->close_all_documents(lParam != 0);
         }


         //    if(m_pMixerDocTemplate != nullptr)
         //  {
         //    m_pMixerDocTemplate->open_new_document();
         //  if(GetMainWnd() != nullptr)
         //{
         //  GetMainWnd()->SetForegroundWindow();
         //}
         //}
      }




      //bool thread::on_idle(LONG lCount)
      //{
      //   // TODO: add your specialized code here and/or call the base class
      //   return ::thread::on_idle(lCount);
      //}

      void thread::OnVmsmException(::message::message * pmessage)
      {
         UNREFERENCED_PARAMETER(pmessage);
         //__pointer(::axis::application) pApp = (__pointer(::axis::application)) System;
         //pApp->post_thread_message(VMSM_EXCEPTION, wParam, lParam);
      }


      void thread::OnUserMessage(::message::message * pmessage)
      {
         __pointer(::user::message) pusermessage(pmessage);

         switch(pusermessage->m_wparam)
         {

         case 21:
            //                    ASSERT(false);
            //                  //ReserveSong_(pMsg->lParam);
            //GetPlayerDocTemplate()->ReserveSong(lParam, false, true);
            break;
         case 22:
         {
            //  CDWArray * pdwa = (CDWArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->get_data()[1], pdwa->get_at(0), false, true);
            //delete pdwa;
         }
         break;
         case 23:
         {
            //CStrArray * pstra = (CStrArray *) lParam;
            //GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
            //delete pstra;
         }
         break;
         case 543:
         {

            //            if(m_poptionsview == nullptr)
            {
               //                m_poptionsview = new COptionsDialog();
               //              m_poptionsview->create(nullptr);
            }

            //            if(m_poptionsview != nullptr)
            {
               //            m_poptionsview->ShowWindow(SW_SHOWNORMAL);
            }

         }
         break;

         }

         switch(pusermessage->m_wparam)
         {
         case 131415:
            // ViewToolsAlbum();
            break;
         case 565758:
         {
            /*CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            __pointer(single_document_template) pAlbumDocTemplate = nullptr;
            if(GetAlbumThread())
            {
            pAlbumDocTemplate = GetAlbumThread()->GetMixerDocTemplate();
            }
            bool bVisible = false;
            if(pAlbumDocTemplate != nullptr)
            {
            bVisible = pAlbumDocTemplate->get_document_count() != nullptr;

            // avoid thread quit on close all documents
            GetAlbumThread()->GetMainWnd() = nullptr;

            GetAlbumThread()->GetMixerDocTemplate()->close_all_documents(false);
            }
            //CMixerFrameWnd * pAlbum = GetMixerDocTemplate();
            //bool bVisible;
            //if(pAlbum != nullptr)
            //{
            //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
            //if(bVisible)
            //  pAlbum->hide();
            //}
            lpdata->bVisible = bVisible;*/
         }
         break;
         case 676869:
         {
            //ASSERT(false);
            /*            CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            if(!lpdata->m_pobjectTaskdlg->create(IDD_TASK))
            {
            message_box("Could not create task dialog");
            return;
            }

            GetAlbumThread()->GetMainWnd() = lpdata->m_pobjectTaskdlg;
            */
         }
         case 787970:
         {
            /*CDBBuildAlbumThreadData * lpdata =
            (CDBBuildAlbumThreadData *)lParam;
            if(m_pMixerDocTemplate != nullptr)
            {
            if(lpdata->bVisible)
            {
            lpdata->lpDataCentral->m_csBuildAlbumThreadData.lock();
            lpdata->m_evStarted.lock();
            //lpdata->m_pobjectTaskdlg->m_pCloseWindow = pAlbum;
            //            lpdata->m_pobjectTaskdlg->m_lparamClose = 10;
            lpdata->lpDataCentral->m_csBuildAlbumThreadData.unlock();
            }
            }*/
         }
         break;
         case 345456:
         {

         }
         break;
         case 321432:
         {
            // On Task Dialog Stop
            //ASSERT(m_pdbcentral != nullptr);
            //m_pdbcentral->SetBuildAlbumThreadsCancelFlag();
         }
         break;
         case 3214:
         {
            //OnChangeEconoMode();

         }
         break;
         case 534231:
         {
            //GetKarWnd()->send_message_to_descendants(WM_USER, 534231);
         }
         break;

         default:;
            break;

         }

      }


      void thread::pre_translate_message(::message::message * pmessage)
      {

         return ::thread::pre_translate_message(pmessage);

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia






