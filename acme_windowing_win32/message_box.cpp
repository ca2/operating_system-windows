#include "framework.h"
#include "acme/user/interface/message_box.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows/windows.h"
#include "windowing.h"

//CLASS_DECL_ACME ::i32 message_box_to_windows_message_box(const ::user::e_message_box & emessagebox);
//CLASS_DECL_ACME enum_dialog_result windows_message_box_result_to_dialog_result(::i32 iResult);


namespace win32
{


   namespace acme
   {


      namespace windowing
      {






         void windowing::show(::particle_pointer pparticle)
         {



            {

               auto pmessageboxpayload = pparticle.cast < ::user_interface::message_box>();

               if (pmessageboxpayload)
               {


                  //namespace windows
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
                  auto iType = ::windows::message_box_to_windows_message_box(pmessageboxpayload->get_emessagebox());
                  ::wstring wstrMessage(pmessageboxpayload->get_message());
                  ::wstring wstrTitle(pmessageboxpayload->get_title());

                  auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);

                  pmessageboxpayload->set_dialog_response(::windows::windows_message_box_result_to_dialog_result(iRet));


               }


        /*       void complete_step(sequencer & sequencer) override
               {

                  sequencer.add_result(m_edialogresult);

               }*/

            };


         } // namespace windows

      //}

   //}


      } // namespace windowing


   } // namespace acme


} // namespace win32



