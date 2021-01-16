#pragma once


namespace multimedia
{


   namespace xaudio7
   {


      CLASS_DECL_MULTIMEDIA_XAUDIO7 void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
//      CLASS_DECL_MULTIMEDIA_XAUDIO7 void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iIndex);
      //    CLASS_DECL_MULTIMEDIA_XAUDIO7 LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iIndex);
      //  CLASS_DECL_MULTIMEDIA_XAUDIO7 LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iIndex);


      CLASS_DECL_MULTIMEDIA_XAUDIO7 ::e_status     translate(HRESULT mmr);


   } // namespace xaudio7


} // namespace multimedia





