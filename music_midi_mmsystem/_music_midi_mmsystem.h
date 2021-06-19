// Created by camilo on 2021-06-10 01:04 PM <3Thomas Borregaard Sørensen__!!
#pragma once


#include "app-veriwell/multimedia/multimedia/_multimedia.h"
#include "multimedia_mmsystem/_multimedia_mmsystem.h"


inline HMIDISTRM __hmidistream(const wparam& wparam) { return wparam.scast < HMIDISTRM >(); }
inline LPMIDIHDR __lpmidihdr(const wparam& wparam) { return wparam.scast < LPMIDIHDR >(); }
inline LPMIDIHDR __lpmidihdr(const lparam& lparam) { return lparam.scast < LPMIDIHDR >(); }

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



