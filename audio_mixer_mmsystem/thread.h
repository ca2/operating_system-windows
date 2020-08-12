#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM thread :
         public ::multimedia::audio_mixer::thread
      {
      public:


         


         enum e_message
         {
            MessageMixerThread = WM_USER + 113,
         };

         bool                                m_bPendingShowCommand;

         __pointer(::multimedia::audio_mixer::department) m_psection;


         thread();
         virtual ~thread();


         static LRESULT CALLBACK MessageProc(
         i32 code,       // hook code
         WPARAM wParam,  // undefined
         LPARAM lParam   // address of structure with message data
         );


         void install_message_routing(::channel * pchannel);

         virtual ::estatus init_thread() override;
         virtual void term_thread() override;
         // virtual bool on_idle(LONG lCount);
         virtual void pre_translate_message(::message::message * pmessage);


         DECL_GEN_SIGNAL(OnMixerMessage);
         DECL_GEN_SIGNAL(OnVmsmException);
         DECL_GEN_SIGNAL(OnUserMessage);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia





