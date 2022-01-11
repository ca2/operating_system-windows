#pragma once


#define MIDIMSG(status,channel,data1,data2) ( (u32)((status<<4) | channel | (data1<<8) | (data2<<16)) )


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         void     midi_in_get_error_text(MMRESULT mmr, string & strOsMessage, string & strMessage);


      } // namespace mmsystem


   } // namespace midi


} // namespace music
