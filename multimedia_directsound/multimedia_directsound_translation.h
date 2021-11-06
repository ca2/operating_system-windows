#pragma once


namespace multimedia
{


   namespace directsound
   {


      CLASS_DECL_MULTIMEDIA_DIRECTSOUND void translate(WAVEFORMATEX & formatex, ::wave::format * pwaveformat);
//      CLASS_DECL_MULTIMEDIA_DIRECTSOUND void translate(WAVEHDR & wavehdr, ::wave::buffer * pwavebuffer, int iIndex);
      //    CLASS_DECL_MULTIMEDIA_DIRECTSOUND LPWAVEHDR create_new_WAVEHDR(::wave::buffer * pwavebuffer, int iIndex);
      //  CLASS_DECL_MULTIMEDIA_DIRECTSOUND LPWAVEHDR get_os_data(::wave::buffer * pwavebuffer, int iIndex);


      CLASS_DECL_MULTIMEDIA_DIRECTSOUND ::e_status     translate(HRESULT mmr);


   } // namespace directsound


} // namespace multimedia





