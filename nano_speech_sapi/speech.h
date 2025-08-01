// From acme_windows audio_mmsystem/out.h to
// nano_speech_sapi nano speech component implementation by
// by camilo on 2024-05-15 02:02 <3ThomasBorregaardSorensen!
// Merged code from text_to_speech_sapi component on
// 2024-05-15 02:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/nano/speech/speech.h"
#include "acme/operating_system/windows_common/com/comptr.h"

#include "acme/_operating_system.h"


//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////


#include <sapi.h>        // SAPI (for windows::tts::speaker)


namespace sapi
{


   namespace nano
   {


      namespace speech
      {


         class  CLASS_DECL_NANO_SPEECH_SAPI speech :
            virtual public ::nano::speech::speech
         {
         public:

            string_map < map < enum_gender, comptr < ISpVoice > > >           m_voicemap;
            string_map < map < enum_gender, comptr < ISpObjectToken > > >     m_tokenmap;



            speech();
            ~speech() override;


            void speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang = "en-us", enum_gender egender = e_gender_none) override;

            virtual comptr < ISpVoice > SpGetVoiceByLangAndGender(const ::scoped_string& scopedstrLang, enum_gender egender);

            virtual comptr < ISpObjectToken > SpGetTokenByLangAndGender(const ::scoped_string& scopedstrLang, enum_gender egender);

            virtual HRESULT SpGetCategoryFromId(const WCHAR* pszCategoryId, ISpObjectTokenCategory** ppCategory, BOOL fCreateIfNotExist = false);

            virtual HRESULT SpGetTokenFromId(const WCHAR* pszTokenId, ISpObjectToken** ppToken, BOOL fCreateIfNotExist = false);

            virtual HRESULT SpGetDefaultTokenFromCategoryId(
               const WCHAR* pszCategoryId,
               ISpObjectToken** ppToken,
               BOOL fCreateCategoryIfNotExist = true);


            bool SpGetDefaultTokenFromCategoryId__LangAndGender(
               const WCHAR* pszCategoryId,
               ISpObjectToken** ppToken,
               const ::scoped_string & scopedstrLang,
               enum_gender egender,
               const_char_pointer pszAttributes,
               BOOL fCreateCategoryIfNotExist);


            bool _SpGetDefaultTokenFromCategoryId__LangAndGender(
               const WCHAR* pszCategoryId,
               ISpObjectToken** ppToken,
               const ::scoped_string& scopedstrLang,
               enum_gender egender,
               const_char_pointer pszAttributes,
               BOOL fCreateCategoryIfNotExist);

         };


      } // namespace speech


   }// namespace nano


} // namespace sapi



