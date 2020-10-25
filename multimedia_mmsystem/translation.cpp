#include "framework.h"


namespace multimedia
{


   namespace mmsystem
   {


      void translate(WAVEFORMATEX & waveformatex, ::wave::format * pwaveformat)
      {


         waveformatex.wFormatTag          = pwaveformat->m_waveformat.wFormatTag;           /* format type */
         waveformatex.nChannels           = pwaveformat->m_waveformat.nChannels;            /* number of channels (i.e. mono, stereo...) */
         waveformatex.nSamplesPerSec      = pwaveformat->m_waveformat.nSamplesPerSec;       /* sample rate */
         waveformatex.nAvgBytesPerSec     = pwaveformat->m_waveformat.nAvgBytesPerSec;      /* for buffer estimation */
         waveformatex.nBlockAlign         = pwaveformat->m_waveformat.nBlockAlign;          /* block size of data */
         waveformatex.wBitsPerSample      = pwaveformat->m_waveformat.wBitsPerSample;       /* number of bits per sample of mono data */
         waveformatex.cbSize              = sizeof(waveformatex);
         /* extra information (after cbSize) */

      }


      void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, index iBuffer)
      {

         ::wave::buffer::item * pitem  = pwavebuffer->get_buffer(iBuffer);

         pitem->m_posdata              = &wavehdr;

         wavehdr.lpData                = (LPSTR) pitem->m_pData;
         wavehdr.dwBufferLength        = (u32) (pwavebuffer->m_uiBufferSize);
         wavehdr.dwBytesRecorded       = 0;
         wavehdr.dwUser                = pitem->m_iIndex;
         wavehdr.dwFlags               = 0;

      }


      LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, index iBuffer)
      {

         LPWAVEHDR lpwavehdr = new WAVEHDR;

         translate(*lpwavehdr, pwavebuffer, iBuffer);

         return lpwavehdr;

      }

      LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, index iBuffer)
      {

         ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);

         LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

         return pwavehdr;

      }

      ::estatus     translate(MMRESULT mmr)
      {

         switch(mmr)
         {
         case MMSYSERR_NOERROR:

            return ::success;

         case MMSYSERR_ALLOCATED:

            return error_already_allocated;

         default:

            return error_failed;

         };

      }


   } // namespace mmsystem


} // namespace multimedia





