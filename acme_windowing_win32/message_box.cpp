#include "framework.h"
#include "windowing.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME int message_box_to_windows_message_box(enum_message_box emessagebox);
CLASS_DECL_ACME enum_dialog_result windows_message_box_result_to_dialog_result(int iResult);


namespace win32
{


   namespace acme
   {


      namespace windowing
      {






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
                  auto iType = message_box_to_windows_message_box(pmessagebox->m_emessagebox);
                  ::wstring wstrMessage(pmessagebox->m_strMessage);
                  ::wstring wstrTitle(pmessagebox->m_strTitle);

                  auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);

                  pmessagebox->m_payloadResult = windows_message_box_result_to_dialog_result(iRet);


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



