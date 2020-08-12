#pragma once

class millis_timer
{

public:


   HANDLE hTimerQueue;
   HANDLE gDoneEvent;

   millis_timer()
   {

      // Use an event object to track the TimerRoutine execution
      gDoneEvent = CreateEvent(nullptr,TRUE,FALSE,nullptr);
      if(nullptr == gDoneEvent)
      {
         throw - 1;
      }
      // Create the timer queue.
      hTimerQueue = CreateTimerQueue();
      if(nullptr == hTimerQueue)
      {
         throw - 1;
      }
   }

   ~millis_timer()
   {

      CloseHandle(gDoneEvent);

      // Delete all timers in the timer queue.
      DeleteTimerQueue(hTimerQueue);


   }


   static VOID CALLBACK TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired)
   {
      millis_timer * ptimer = (millis_timer *)lpParam;

      SetEvent(ptimer->gDoneEvent);

      ptimer->on_millis_timer_step();
   }

   bool wait(int millis)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = nullptr;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,millis,0,0))
      {
         return false;
      }

      if(WaitForSingleObject(gDoneEvent,INFINITE) != WAIT_OBJECT_0)
         return false;

      //      DeleteTimerQueue(hTimer);

      return true;
   }
   bool timer(int millis)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = nullptr;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,millis,millis,0))
      {
         return false;
      }

      if(WaitForSingleObject(gDoneEvent,INFINITE) != WAIT_OBJECT_0)
         return false;

      //      DeleteTimerQueue(hTimer);

      return true;
   }

   virtual void on_millis_timer_step()
   {
   }

};

namespace multimedia
{


   namespace audio_xaudio7
   {


      class  CLASS_DECL_AUDIO_XAUDIO7 out :
         virtual public ::wave::out,
         virtual public IXAudio2VoiceCallback
      {
      public:


         //HANDLE streamEndEventHandle;
         //VoiceCallback(): streamEndEventHandle(CreateEvent(nullptr,FALSE,FALSE,nullptr)){}
         //~VoiceCallback()
         //{
         //CloseHandle(streamEndEventHandle);
         //}

         // Called when the voice has just finished playing a contiguous audio stream.
         STDMETHOD_(void,OnStreamEnd())
         {

         }

         // Unused methods in this application
         STDMETHOD_(void,OnVoiceProcessingPassEnd()) { }
         STDMETHOD_(void,OnVoiceProcessingPassStart(UINT32 SamplesRequired)) {    }
         STDMETHOD_(void,OnBufferEnd(void * pBufferContext))  ;
         STDMETHOD_(void,OnBufferStart(void * pBufferContext)) {    }
         STDMETHOD_(void,OnLoopEnd(void * pBufferContext)) {    }
         STDMETHOD_(void,OnVoiceError(void * pBufferContext,HRESULT Error)) { }
         class run_step_thread :
            virtual public ::thread
         {
         public:

            out * m_pout;

            run_step_thread(out * pout);

            virtual i32 run();

         };

         IXAudio2 *                       m_pxaudio;
         IXAudio2MasteringVoice *         m_pvoice;
         IXAudio2SourceVoice *            m_psourcevoice;

         run_step_thread *                m_prunstepthread;

         int                              m_iBuffer;

         WAVEFORMATEX                     m_waveformatex;



         out(__pointer(::axis::application) papp);
         virtual ~out();


         ::estatus     out_start(const imedia_position & position);
         virtual bool  on_run_step();
         void install_message_routing(::channel * pchannel);

         virtual imedia_time out_get_position_millis();
         imedia_position out_get_position();
         virtual void out_buffer_ready(int iBuffer);
         //virtual void out_buffer_ready(LPWAVEHDR lpwavehdr);

         virtual ::estatus     out_open(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount);
         virtual ::estatus     out_open_ex(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample);
         virtual ::estatus     out_stop();
         virtual ::estatus     out_close();
         virtual ::estatus     out_pause();
         virtual ::estatus     out_restart();
         virtual void * get_os_data();
         //HWAVEOUT out_get_safe_HWAVEOUT();

         virtual void out_on_playback_end();
         virtual void out_free(int iBuffer);
         //virtual void out_free(LPWAVEHDR lpwavehdr);

         virtual bool initialize_thread() override;
         virtual i32 exit_instance();

         virtual i32 run();

         //DECL_GEN_SIGNAL(OnMultimediaOpen);
         //DECL_GEN_SIGNAL(OnMultimediaDone);
         //DECL_GEN_SIGNAL(OnMultimediaClose);

//         virtual void out_out_buffer_done(int iBuffer);
         //       virtual void out_out_buffer_done(LPWAVEHDR lpwavehdr);

         WAVEFORMATEX * wave_format();
         //LPWAVEHDR wave_hdr(int iBuffer);
         virtual void out_run_step();
      };


   } // namespace audio_xaudio7


} // namespace multimedia



