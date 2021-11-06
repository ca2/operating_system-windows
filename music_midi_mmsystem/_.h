#pragma once


#include "app-veriwell/multimedia/multimedia/_.h"
#include "multimedia_mmsystem/_.h"


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


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





