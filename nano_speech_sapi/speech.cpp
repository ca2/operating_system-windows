// From acme_windows node::speak to
// nano_speech_sapi nano speech component implementation by
// by camilo on 2024-05-15 01:59 <3ThomasBorregaardSorensen!
#include "framework.h"
#include "speech.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/_operating_system.h"
#include "acme_windows_common/cotaskptr.h"
#include <sapi.h>


namespace sapi
{


   namespace nano
   {


      namespace speech
      {


         speech::speech()
         {



         }


         speech::~speech()
         {


         }



         void speech::speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang, enum_gender egender)
         {


            if (FAILED(::CoInitialize(NULL)))
            {

               return;

            }

            ISpVoice* pVoice = NULL;

            HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);

            if (SUCCEEDED(hr))
            {

               wstring wstr = scopedstr;

               hr = pVoice->Speak((LPCWSTR)wstr, NULL, NULL);

               pVoice->Release();

               pVoice = NULL;

            }

            ::CoUninitialize();


         }


         comptr < ISpVoice > speech::SpGetVoiceByLangAndGender(const ::scoped_string& scopedstrLang, enum_gender egender)
         {

            node()->defer_co_initialize_ex(false);

            if (egender == e_gender_none)
            {

               egender = e_gender_male;

            }

            _synchronous_lock synchronouslock(this->synchronization());

            comptr < ISpVoice >& pvoice = m_voicemap[scopedstrLang][egender];

            HRESULT hr = S_OK;

            if (pvoice.is_set())
            {

               return pvoice;

            }

            pvoice.CoCreateInstance(CLSID_SpVoice);

            auto ptoken = SpGetTokenByLangAndGender(scopedstrLang, egender);

            if (ptoken)
            {

               hr = pvoice->SetVoice(ptoken);

               if (FAILED(hr))
               {

                  throw ::exception(error_failed);

               }

            }

            return pvoice;

         }


         comptr < ISpObjectToken > speech::SpGetTokenByLangAndGender(const ::scoped_string& scopedstrLang, enum_gender egender)
         {

            comptr < ISpObjectToken >& ptoken = m_tokenmap[scopedstrLang][egender];

            if (ptoken.is_set())
            {

               return ptoken;

            }

            HRESULT hr = E_FAIL;

            if (scopedstrLang.is_empty() && egender == e_gender_none)
            {

               hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &ptoken, false);

               if (SUCCEEDED(hr))
               {

                  return ptoken;

               }

            }

            hr = SpGetDefaultTokenFromCategoryId__LangAndGender(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", &ptoken, scopedstrLang, egender, "", false);

            if (SUCCEEDED(hr))
            {

               return ptoken;

            }

            return nullptr;

         }

         // Declare local identifiers:

         HRESULT speech::SpGetCategoryFromId(const WCHAR* pszCategoryId, ISpObjectTokenCategory** ppCategory, BOOL fCreateIfNotExist)
         {
            HRESULT hr;

            comptr < ISpObjectTokenCategory > pcategory;
            hr = pcategory.CoCreateInstance(CLSID_SpObjectTokenCategory);

            if (SUCCEEDED(hr))
            {
               hr = pcategory->SetId(pszCategoryId, fCreateIfNotExist);
            }

            if (SUCCEEDED(hr))
            {
               *ppCategory = pcategory.detach();
            }

            return hr;
         }


         HRESULT speech::SpGetTokenFromId(const WCHAR* pszTokenId, ISpObjectToken** ppToken, BOOL fCreateIfNotExist)
         {
            HRESULT hr;

            comptr < ISpObjectToken > ptoken;
            hr = ptoken.CoCreateInstance(CLSID_SpObjectToken);

            if (SUCCEEDED(hr))
            {
               hr = ptoken->SetId(nullptr, pszTokenId, fCreateIfNotExist);
            }

            if (SUCCEEDED(hr))
            {
               *ppToken = ptoken.detach();
            }


            return hr;

         }

         HRESULT speech::SpGetDefaultTokenFromCategoryId(
            const WCHAR* pszCategoryId,
            ISpObjectToken** ppToken,
            BOOL fCreateCategoryIfNotExist)
         {
            HRESULT hr;

            comptr<ISpObjectTokenCategory> pcategory;
            hr = SpGetCategoryFromId(pszCategoryId, &pcategory, fCreateCategoryIfNotExist);

            if (SUCCEEDED(hr))
            {
               cotaskptr < LPWSTR > pszTokenId;
               hr = pcategory->GetDefaultTokenId(&pszTokenId);
               if (SUCCEEDED(hr))
               {
                  hr = SpGetTokenFromId(pszTokenId, ppToken);

               }
            }

            return hr;
         }


         bool speech::SpGetDefaultTokenFromCategoryId__LangAndGender(
            const WCHAR* pszCategoryId,
            ISpObjectToken** ppToken,
            const ::scoped_string& scopedstrLang,
            enum_gender egender,
            const char* pszAttributes,
            BOOL fCreateCategoryIfNotExist)
         {

            HRESULT hr = _SpGetDefaultTokenFromCategoryId__LangAndGender
            (pszCategoryId,
               ppToken,
               scopedstrLang,
               egender,
               pszAttributes,
               fCreateCategoryIfNotExist);

            if (SUCCEEDED(hr))
            {

               return true;

            }

            if (egender != e_gender_none)
            {

               hr = _SpGetDefaultTokenFromCategoryId__LangAndGender
               (pszCategoryId,
                  ppToken,
                  scopedstrLang,
                  e_gender_none,
                  pszAttributes,
                  fCreateCategoryIfNotExist);

               if (SUCCEEDED(hr))
               {

                  return true;

               }

            }

            if (scopedstrLang.has_character())
            {

               hr = _SpGetDefaultTokenFromCategoryId__LangAndGender
               (pszCategoryId,
                  ppToken,
                  "en-us",
                  egender,
                  pszAttributes,
                  fCreateCategoryIfNotExist);

               if (SUCCEEDED(hr))
               {

                  return true;

               }


            }

            return false;

         }


         bool speech::_SpGetDefaultTokenFromCategoryId__LangAndGender(
            const WCHAR* pszCategoryId,
            ISpObjectToken** ppToken,
            const ::scoped_string& scopedstrLang,
            enum_gender egender,
            const char* pszAttributes,
            BOOL fCreateCategoryIfNotExist)
         {

            HRESULT hr;

            comptr<ISpObjectTokenCategory> pcategory;

            hr = SpGetCategoryFromId(pszCategoryId, &pcategory, fCreateCategoryIfNotExist);

            string str(scopedstrLang);

            str.make_lower();

            string strLang;

            if (str == "en" || str == "us" || str == "english")
            {

               strLang = "409";

            }
            else if (str == "pt" || str == "br" || str == "portugues" || str == "português")
            {

               strLang = "416";

            }
            else
            {

               ::property_set set;

               string strNetworkPayload = file()->as_string("matter://speech/windows/lang.network_payload");

               try
               {

                  set.parse_network_payload(strNetworkPayload);

               }
               catch (...)
               {

               }

               if (set[str].has_character())
               {

                  strLang = set[str];

               }
               else
               {

                  strLang = "409";

               }

            }

            string strAttributes(pszAttributes);

            string_array straAttributes;

            straAttributes.add_smallest_tokens(strAttributes, { ";" });

            straAttributes.insert_at(0, "Language=" + strLang);

            if (egender == e_gender_male)
            {

               straAttributes.insert_at(1, "Gender=Male");

            }
            else if (egender == e_gender_female)
            {

               straAttributes.insert_at(1, "Gender=Female");

            }

            //auto pFind = straAttributes.find_first_begins_ci("voice=");

            //string strVoice;

            //if (::is_set(pFind))
            //{

            //   strVoice = straAttributes.erase_at(iFind);

            //}

            if (SUCCEEDED(hr))
            {
               //      WCHAR * pszTokenId;
               // Declare local identifiers:
               HRESULT                           hr = S_OK;
               comptr<IEnumSpObjectTokens>      cpSpEnumTokens;

               if (SUCCEEDED(hr))
               {

                  hr = pcategory->EnumTokens(nullptr, nullptr, &cpSpEnumTokens);

               }

               ULONG ulCount;

               if (SUCCEEDED(hr))
               {

                  cpSpEnumTokens->GetCount(&ulCount);

               }

               auto iAttributesToMatchCount = straAttributes.get_count();

               for (; iAttributesToMatchCount >= 0; iAttributesToMatchCount--)
               {

                  for (ULONG i = 0; i < ulCount; i++)
                  {

                     comptr<ISpObjectToken> ptoken;

                     hr = cpSpEnumTokens->Item(i, &ptoken);

                     if (SUCCEEDED(hr))
                     {

                        bool bAllMatch = true;

                        for (int iAttribute = 0; iAttribute < iAttributesToMatchCount; iAttribute++)
                        {

                           wstring wstrAttribute = straAttributes[iAttribute];

                           BOOL bMatches;

                           hr = ptoken->MatchesAttributes(wstrAttribute, &bMatches);

                           if (FAILED(hr) || !bMatches)
                           {

                              bAllMatch = false;

                              break;

                           }

                        }

                        if (bAllMatch)
                        {

                           *ppToken = ptoken;

                           ptoken.m_p = nullptr;

                           return true;

                        }

                     }

                  }

               }

               //for (ULONG i = 0; i < ulCount; i++)
               //{

               //   comptr<ISpObjectToken> ptoken;

               //   hr = cpSpEnumTokens->Item(i, &ptoken);

               //   if (SUCCEEDED(hr))
               //   {

               //      wstring wstrLang;

               //      wstrLang = L"Language=";
               //      wstrLang += wstring(strLang);
               //      BOOL bMatches;

               //      hr = ptoken->MatchesAttributes(wstrLang, &bMatches);


               //      if (SUCCEEDED(hr) && bMatches)
               //      {
               //         *ppToken = ptoken;
               //         ptoken.m_p = nullptr;
               //         return true;
               //      }


               //   }

               //}

               return SUCCEEDED(SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, ppToken, false));

            }

            return SUCCEEDED(hr);
         }


      } // namespace speech


   } // namespace nano


} // namespace sapi



