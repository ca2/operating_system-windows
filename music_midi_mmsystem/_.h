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






inline HMIDISTRM __hmidistream(const wparam & wparam) { return wparam.scast < HMIDISTRM >(); }
inline LPMIDIHDR __lpmidihdr(const wparam & wparam) { return wparam.scast < LPMIDIHDR >(); }
inline LPMIDIHDR __lpmidihdr(const lparam & lparam) { return lparam.scast < LPMIDIHDR >(); }

#include "translation.h"

#include "buffer.h"

//#include "file.h"

//#include "sequence.h"

#include "sequencer.h"

//#include "player.h"

#include "in.h"

#include "out.h"

//#include "sequence_thread.h"

#include "midi.h"

#include "factory_exchange.h"



