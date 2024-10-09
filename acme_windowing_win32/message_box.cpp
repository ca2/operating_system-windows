#include "framework.h"


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         int message_box_to_windows_message_box(enum_message_box emessagebox)
         {

            int iMessageBox = 0;

            iMessageBox |= message_box_to_windows_message_box_type(emessagebox);

            iMessageBox |= message_box_to_windows_message_box_icon(emessagebox);

            iMessageBox |= message_box_to_windows_message_box_default_button(emessagebox);

            return iMessageBox;

         }


         enum_dialog_result windows_message_box_result_to_dialog_result(int iResult)
         {

            switch (iResult)
            {
            case IDOK:
               return e_dialog_result_ok;
            case IDCANCEL:
               return e_dialog_result_cancel;
            case IDABORT:
               return e_dialog_result_abort;
            case IDRETRY:
               return e_dialog_result_retry;
            case IDIGNORE:
               return e_dialog_result_ignore;
            case IDYES:
               return e_dialog_result_yes;
            case IDNO:
               return e_dialog_result_no;
            case IDCLOSE:
               return e_dialog_result_close;
            case IDHELP:
               return e_dialog_result_help;
            case IDTRYAGAIN:
               return e_dialog_result_try_again;
            case IDCONTINUE:
               return e_dialog_result_continue;
            case IDTIMEOUT:
               return e_dialog_result_timeout;
            default:
               return e_dialog_result_none;
            }

         }



         void windowing::show(::particle_pointer pparticle)
         {



            {

               auto pmessagebox = pparticle.cast < ::message_box>();

               if (pmessagebox)
               {


                  //namespace windows
                  //{


                  //   class message_box :
                  //      public ::operating_system::message_box
                  //   {
                  //   public:

                  //      //::atom do_modal(const ::scoped_string & scopedstrMessage,
                  //      //                               const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox,
                  //      //                               const ::scoped_string & scopedstrDetails) override
                  //      ::enum_dialog_result m_edialogresult;
                  //      void run() override
                  //      {
                  auto iType = message_box_to_windows_message_box(pmessageobx->m_emessagebox);
                  ::wstring wstrMessage(pmessagebox->m_strMessage);
                  ::wstring wstrTitle(pmessagebox->m_strTitle);

                  auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);

                  pmessagebox->m_edialogresult = windows_message_box_result_to_dialog_result(iRet);


               }


               void complete_step(sequencer & sequencer) override
               {

                  sequencer.add_result(m_edialogresult);

               }

            };


         } // namespace windows

      }

   }


      } // namespace windowing


   } // namespace acme


} // namespace win32



