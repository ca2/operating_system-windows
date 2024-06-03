#pragma once


#include "acme/_.h"


#if defined(_nano_speech_sapi_project)
   #define CLASS_DECL_NANO_SPEECH_SAPI  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_NANO_SPEECH_SAPI  CLASS_DECL_IMPORT
#endif



