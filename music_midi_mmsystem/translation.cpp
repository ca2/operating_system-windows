#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         ::e_status     midi_in_get_error_text(MMRESULT mmr, string & strOsMessage, string & strMessage)
         {

            if(mmr == MMSYSERR_NOERROR)
            {

               return ::success;

            }

            wstring wstr;

            if (midiInGetErrorTextW(mmr, wstr.get_string_buffer(4096), 4096 * sizeof(wchar_t)) == MMSYSERR_NOERROR)
            {

               wstr.release_string_buffer();

               strOsMessage = wstr;

            }

            if (mmr == MIDIERR_NODEVICE)
            {
               strMessage = "MIDIERR_NODEVICE : device is in use?!";
            }
            else if (mmr == MMSYSERR_INVALPARAM)
            {
               strMessage = "MMSYSERR_INVALPARAM : An invalid or corrupted parameter was specified to a MMSystem function?!:!?";
            }
            else if (mmr == MMSYSERR_BADDEVICEID)
            {
               strMessage = "MMSYSERR_BADDEVICEID : bad device id";
            }
            else if (mmr == MMSYSERR_NOMEM)
            {
               strMessage = "MMSYSERR_NOMEM : no memory : ca2 application memory leak?!?! close other programs?!?! both?!?!";
            }
            else
            {
               strMessage = "(Missing error description) : missing ::music::midi::mmsystem::translate_mmr implementation...!!";
            }

            return error_failed;

         }


         //UINT translate_out_device(UINT uiDevice)
         //{

         //   if (uiDevice == ::music::midi::device_default)
         //   {

         //      //m_uiDeviceID = MIDI_MAPPER;
         //      return 0; // Windows 8 "abolished" MIDI_MAPPER - TODO : Own "Midi Selector..."

         //   }
         //   else
         //   {

         //      return uiDevice;

         //   }

         //}

      } // namespace mmsystem

   } // namespace midi_mmsystem


} // namespace music