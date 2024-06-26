#pragma once


namespace multimedia
{


   namespace mmsystem
   {


      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, ::collection::index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, ::collection::index iIndex);
      CLASS_DECL_MULTIMEDIA_MMSYSTEM LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, ::collection::index iIndex);


      //CLASS_DECL_MULTIMEDIA_MMSYSTEM void     translate(MMRESULT mmr);


   } // namespace mmsystem


} // namespace multimedia


//CLASS_DECL_MULTIMEDIA_MMSYSTEM ::e_status mmresult_status(MMRESULT mmr);



