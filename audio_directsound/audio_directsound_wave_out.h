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

   bool wait(int class ::time)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = nullptr;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,class ::time,0,0))
      {
         return false;
      }

      if(WaitForSingleObject(gDoneEvent,INFINITE) != WAIT_OBJECT_0)
         return false;

      //      DeleteTimerQueue(hTimer);

      return true;
   }
   bool timer(int class ::time)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = nullptr;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,class ::time,class ::time,0))
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


         out(::particle * pparticle);
         virtual ~out();

         void     out_start(const class ::time & position);
         void install_message_routing(::channel * pchannel);

         virtual class ::time out_get_time();
         class ::time out_get_time();
         virtual void out_filled(::collection::index iBuffer) override;
         //virtual void out_buffer_ready(LPWAVEHDR lpwavehdr);

         virtual void     out_open(::thread * pthreadCallback, int iBufferCount, int iBufferSampleCount);
         virtual void     out_open_ex(::thread * pthreadCallback, int iBufferCount, int iBufferSampleCount, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample);
         virtual void     out_stop();
         virtual void     out_close();
         virtual void     out_pause();
         virtual void     out_restart();
         virtual void * get_os_data();
         //HWAVEOUT out_get_safe_HWAVEOUT();

         virtual void out_on_playback_end();
         virtual void out_free(::collection::index iBuffer) override;
         //virtual void out_free(LPWAVEHDR lpwavehdr);

         virtual bool init_thread() override;
         virtual void term_thread() override;

         virtual void     run() override;

         //DECLARE_MESSAGE_HANDLER(OnMultimediaOpen);
         //DECLARE_MESSAGE_HANDLER(OnMultimediaDone);
         //DECLARE_MESSAGE_HANDLER(OnMultimediaClose);

//         virtual void out_out_buffer_done(int iBuffer);
         //       virtual void out_out_buffer_done(LPWAVEHDR lpwavehdr);

         WAVEFORMATEX * wave_format();
         //LPWAVEHDR wave_hdr(int iBuffer);
         virtual void out_run_step();
      };


   } // namespace audio_directsound


} // namespace multimedia



