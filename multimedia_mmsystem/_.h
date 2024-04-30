#pragma once


#include "audio/audio/_.h"
//#include "audio/audio/_.h"
#include "apex_windows/_.h"

#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include <mmsystem.h>


#if defined(_multimedia_mmsystem_project)
   #define CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_IMPORT
#endif


namespace multimedia
{


   namespace mmsystem
   {


      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, ::raw::index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, ::raw::index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, ::raw::index iIndex);


      //CLASS_DECL_MULTIMEDIA_MMSYSTEM void     translate(MMRESULT mmr);


   } // namespace mmsystem


} // namespace multimedia


//CLASS_DECL_MULTIMEDIA_MMSYSTEM::e_status mmresult_status(MMRESULT mmr);


//CLASS_DECL_MULTIMEDIA_MMSYSTEM::e_status mmresult_status(MMRESULT mmr);




