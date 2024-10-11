#include "framework.h"
#include "audio/audio/wave/format.h"
#include "audio/audio/wave/buffer.h"


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
         waveformatex.nBlockAlign         = pwaveformat->m_waveformat.nBlockAlign;          /* block size_i32 of data */
         waveformatex.wBitsPerSample      = pwaveformat->m_waveformat.wBitsPerSample;       /* number of bits per sample of mono data */
         waveformatex.cbSize              = sizeof(waveformatex);
         /* extra information (after cbSize) */

      }


      void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, ::collection::index iBuffer)
      {

         ::wave::buffer::item * pitem  = pwavebuffer->get_buffer(iBuffer);

         pitem->m_posdata              = &wavehdr;

         wavehdr.lpData                = (LPSTR) pitem->m_pData;
         wavehdr.dwBufferLength        = (u32) (pwavebuffer->m_uiBufferSize);
         wavehdr.dwBytesRecorded       = 0;
         wavehdr.dwUser                = pitem->m_iIndex;
         wavehdr.dwFlags               = 0;

      }


      LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, ::collection::index iBuffer)
      {

         LPWAVEHDR lpwavehdr = __new WAVEHDR;

         translate(*lpwavehdr, pwavebuffer, iBuffer);

         return lpwavehdr;

      }

      LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, ::collection::index iBuffer)
      {

         ::wave::buffer::item * pbuffer = pwavebuffer->get_buffer(iBuffer);

         LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

         return pwavehdr;

      }



   } // namespace mmsystem


} // namespace multimedia


