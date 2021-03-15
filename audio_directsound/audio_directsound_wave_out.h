#pragma once

class millis_timer
{

public:


   HANDLE hTimerQueue;
   HANDLE gDoneEvent;

   millis_timer()
   {

      // Use an event object to track the TimerRoutine execution
      gDoneEvent = CreateEvent(nullptr,true,false,nullptr);
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


   namespace audio_directsound
   {


      class  CLASS_DECL_AUDIO_DIRECTSOUND out :
         virtual public ::wave::out
      {
      public:


         int                              m_iBuffer;

         LPDIRECTSOUND8                   m_pdirectsound;
         LPDIRECTSOUNDBUFFER              m_psoundbuffer;
         WAVEFORMATEX                     m_waveformatex;
         LPDIRECTSOUNDNOTIFY              m_psoundnotify;

         array < HANDLE >                 m_haEvent;
         array < DSBPOSITIONNOTIFY >      m_notifya;


         out(::context_object * pcontextobject);
         virtual ~out();

         ::e_status     out_start(const imedia_time & position);
         void install_message_routing(::channel * pchannel);

         virtual imedia_time out_get_time();
         imedia_time out_get_time();
         virtual void out_filled(index iBuffer) override;
         //virtual void out_buffer_ready(LPWAVEHDR lpwavehdr);

         virtual ::e_status     out_open(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount);
         virtual ::e_status     out_open_ex(::thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample);
         virtual ::e_status     out_stop();
         virtual ::e_status     out_close();
         virtual ::e_status     out_pause();
         virtual ::e_status     out_restart();
         virtual void * get_os_data();
         //HWAVEOUT out_get_safe_HWAVEOUT();

         virtual void out_on_playback_end();
         virtual void out_free(index iBuffer) override;
         //virtual void out_free(LPWAVEHDR lpwavehdr);

         virtual bool init_thread() override;
         virtual void term_thread() override;

         virtual ::e_status     run() override;

         //DECL_GEN_SIGNAL(OnMultimediaOpen);
         //DECL_GEN_SIGNAL(OnMultimediaDone);
         //DECL_GEN_SIGNAL(OnMultimediaClose);

//         virtual void out_out_buffer_done(int iBuffer);
         //       virtual void out_out_buffer_done(LPWAVEHDR lpwavehdr);

         WAVEFORMATEX * wave_format();
         //LPWAVEHDR wave_hdr(int iBuffer);
         virtual void out_run_step();
      };


   } // namespace audio_directsound


} // namespace multimedia



