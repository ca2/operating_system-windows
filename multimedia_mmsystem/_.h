#pragma once


#include "app-core/audio/_.h"
//#include "app-core/audio/_.h"
#include "apex_windows/_.h"
//#include "apex/operating_system.h"
#include <mmsystem.h>


#if defined(_MULTIMEDIA_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_IMPORT
#endif


namespace multimedia
{


   namespace mmsystem
   {


      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, index iIndex);


      //CLASS_DECL_MULTIMEDIA_MMSYSTEM void     translate(MMRESULT mmr);


   } // namespace mmsystem


} // namespace multimedia


//CLASS_DECL_MULTIMEDIA_MMSYSTEM::e_status mmresult_to_status(MMRESULT mmr);


CLASS_DECL_MULTIMEDIA_MMSYSTEM::e_status mmresult_to_status(MMRESULT mmr);




