#pragma once

#include "app-multimedia/multimedia/multimedia.h"
//#include <Mmreg.h>
//#define STRINGIFY(x) #x
//#define TOSTRING(x) STRINGIFY(x)
#define XAUDIO2_H <##__DXSDK_DIR##/Include/xaudio2.h>
#include XAUDIO2_H



#if defined(_multimedia_xaudio7_project)
   #define CLASS_DECL_MULTIMEDIA_XAUDIO7  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_XAUDIO7  CLASS_DECL_IMPORT
#endif


#include "multimedia_xaudio7_translation.h"


#include "([a-z0-9_]+)_factory.h"
