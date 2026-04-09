#include "framework.h"
#include "windowing.h"
#include "acme/_operating_system.h"


CLASS_DECL_SUBSYSTEM_WIN32 int message_box_to_windows_message_box(::user::enum_message_box emessagebox);
CLASS_DECL_SUBSYSTEM_WIN32 enum_dialog_result windows_message_box_result_to_dialog_result(int iResult);


namespace win32
{


   namespace acme
   {


      namespace windowing
      {






         void windowing::show(::particle_pointer pparticle)
         {



            {

               auto pmessageboxpayload = pparticle.cast < ::message_box_payload>();

               if (pmessageboxpayload)
               {


                  //namespace subsystem_win32
                  //{


                  //   class message_box :
                  //      public ::operating_system::message_box
                  //   {
                  //   public:

                  //      //::atom do_modal(const ::scoped_string & scopedstrMessage,
                  //      //                               const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox,
                  //      //                               const ::scoped_string & scopedstrDetails) override
                  //      ::enum_dialog_result m_edialogresult;
                  //      void run() override
                  //      {
                  auto iType = message_box_to_windows_message_box(pmessageboxpayload->m_emessagebox);
                  ::wstring wstrMessage(pmessageboxpayload->m_strMessage);
                  ::wstring wstrTitle(pmessageboxpayload->m_strTitle);

                  auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);

                  pmessageboxpayload->m_payloadResult = windows_message_box_result_to_dialog_result(iRet);


               }


        /*       void complete_step(sequencer & sequencer) override
               {

                  sequencer.add_result(m_edialogresult);

               }*/

            };


         } // namespace subsystem_win32

      //}

   //}


      } // namespace windowing


   } // namespace acme


} // namespace win32



