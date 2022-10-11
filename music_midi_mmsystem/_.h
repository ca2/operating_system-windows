#pragma once


#include "app-veriwell/multimedia/_.h"
#include "multimedia_mmsystem/_.h"
#include "acme/operating_system.h"
//#include <mmeapi.h>


#if defined(_MUSIC_MIDI_MMSYSTEM_LIBRARY)
#define CLASS_DECL_MUSIC_MIDI_MMSYSTEM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_MUSIC_MIDI_MMSYSTEM  CLASS_DECL_IMPORT
#endif


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class midi;
         class sequencer;
         class buffer_array;

         ::e_status midi_in_get_error_text(MMRESULT mmr, string & strOsMessage, string & strMessage);


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music

#define MIDIMSG(status,channel,data1,data2) ( (u32)((status<<4) | channel | (data1<<8) | (data2<<16)) )

inline HMIDISTRM __hmidistream(const wparam & wparam) { return wparam.scast < HMIDISTRM >(); }
inline LPMIDIHDR __lpmidihdr(const wparam & wparam) { return wparam.scast < LPMIDIHDR >(); }
inline LPMIDIHDR __lpmidihdr(const lparam & lparam) { return lparam.raw_cast <LPMIDIHDR>(); }




