#pragma once


namespace multimedia
{


   namespace audio_directsound
   {


      class  CLASS_DECL_AUDIO_DIRECTSOUND in :
         virtual public ::wave::in
      {
      public:


         //HWAVEIN              m_hwavein;

         WAVEFORMATEX         m_waveformatex;


         in(::object * pobject);
         virtual ~in();


         virtual bool in_initialize_encoder();

         virtual ::e_status     in_add_buffer(i32 iBuffer);
         //virtual ::e_status     in_add_buffer(LPWAVEHDR lpwavehdr);

         //HWAVEIN in_get_safe_HWAVEIN();
         virtual void * get_os_data();

         ::e_status     in_open(i32 iBufferCount, i32 iBufferSampleCount);
         ::e_status     in_close();
         ::e_status     in_stop();
         ::e_status     in_start();
         ::e_status     in_reset();

         virtual void translate_in_message(::message::message * pmessage);

         virtual bool init_thread() override;
         virtual void term_thread() override;
         virtual void pre_translate_message(::message::message * pmessage);

         //static void CALLBACK in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

         WAVEFORMATEX * wave_format();
         //LPWAVEHDR wave_hdr(int iBuffer);


      };


   } // namespace audio_directsound


} // namespace multimedia




