#include "framework.h"
#include "control.h"
#include "source.h"
#include "device.h"
#include "audio_mixer.h"
#include "destination.h"
#include "acme/exception/exception.h"
#include "acme/platform/application.h"
#include "acme/prototype/text/text.h"
#include "audio-system/audio_mixer/callback.h"
//#include "audio-system/audio_mixer/user/level_control.h"
#include "audio-system/audio_mixer/control_data_volume.h"
//#include "audio-system/audio_mixer/user/label.h"
//#include "audio-system/audio_mixer/user/toggle_control.h"
#include "audio-system/audio_mixer/control_data_switch.h"
#include "acme_windows/mmresult.h"

//namespace multimedia
//{
//

namespace audio_mixer_mmsystem
{


   control::control()
   {

      m_pmixersource = nullptr;
      m_mixercontrol.cbStruct = sizeof(MIXERCONTROL);
      m_mixercontroldetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
      m_mixercontroldetails.paDetails = nullptr;
   }


   control::~control()
   {

      if (m_mixercontroldetails.paDetails != nullptr)
      {

         free(m_mixercontroldetails.paDetails);

      }

   }


   bool control::CreateWindows(::pointer<::user::interaction>pParent, int iStyle)
   {
      __UNREFERENCED_PARAMETER(pParent);
      __UNREFERENCED_PARAMETER(iStyle);
      return true;
   }



   bool control::CreateWindowsVolumeV001(
   ::pointer<::user::interaction>pParent,
   unsigned int nStartID,
   unsigned int * nNextID)
   {

      ASSERT(m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME);

      static wchar_t        szScrollBar[] = L"scrollbar";
      static wchar_t        szTitle[] = L"Fader Class: '%s'";

      unsigned int                        cb;
      unsigned int                        lcChannels;
      unsigned int                        lcMultipleItems;
      int                         nRange;
      int                         nPageInc;

      ::pointer<::audio_mixer_mmsystem::source>source = m_pmixersource;

      ASSERT(source != nullptr);

      lcChannels = (unsigned int)source->m_mixerline.cChannels;
      if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
         m_mixercontroldetails.cChannels = 1;

      lcMultipleItems = 1;
      if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
         lcMultipleItems = (unsigned int)m_mixercontrol.cMultipleItems;

      if (lcChannels > 2)
         return false;
      if (lcMultipleItems != 1)
         return false;

      cb = lcChannels * lcMultipleItems * sizeof(MIXERCONTROLDETAILS_UNSIGNED);
      m_mixercontroldetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
      if (m_mixercontroldetails.paDetails != nullptr)
         free(m_mixercontroldetails.paDetails);
      m_mixercontroldetails.paDetails = malloc(cb);

      nRange = (int)minimum(32767, m_mixercontrol.Metrics.cSteps - 1);
      bool bOk = false;
      for (int i = 5; i <= 10; i++)
      {
         nPageInc = nRange / i;
         if (nPageInc < 1)
         {
            bOk = true;
            nPageInc = 1;
            break;
         }
         if (nRange % i == 0)
         {
            bOk = true;
            break;
         }
      }
      if (!bOk)
      {
         for (int i = 5; i <= 10; i++)
         {
            nPageInc = nRange / i;
            if (nRange % i > (nPageInc / 2))
            {
               bOk = true;
               break;
            }
         }
      }

      unsigned int nID = nStartID;
      unsigned int nVolumeID = nID++;
      unsigned int nVolumeLabelID = nID++;
      unsigned int nBalanceID = nID++;
      unsigned int nBalanceLabelID = nID++;

      //::int_rectangle rectangle(0, 0, 0, 0);

      auto pcontroldatavolume = øcreate_new <::audio_mixer::control_data_volume>();

      pcontroldatavolume->m_iType = ::audio_mixer::control_data::TypeStereoVolume;
      pcontroldatavolume->m_uiMixerID = source->get_device()->m_uiMixerID;
      pcontroldatavolume->m_uiLineID = source->m_mixerline.dwLineID;
      pcontroldatavolume->m_uiControlID = m_mixercontrol.dwControlID;
      pcontroldatavolume->nRange = nRange;
      pcontroldatavolume->nPageInc = nPageInc;

      create_volume_control(pcontroldatavolume, pParent);


      auto pcontroldataLabel = øcreate_new <::audio_mixer::control_data>();
      pcontroldataLabel->m_iType = ::audio_mixer::control_data::TypeStereoVolumeLabel;
      pcontroldataLabel->m_uiMixerID = m_pmixersource->get_device()->m_uiMixerID;
      pcontroldataLabel->m_uiLineID = source->m_mixerline.dwLineID;
      pcontroldataLabel->m_uiControlID = m_mixercontrol.dwControlID;

      create_volume_label(pcontroldataLabel, pParent);


      if (lcChannels == 2)
      {

         //::pointer<::audio_mixer_user::level_control>pinteraction = source->get_device()->get_mixer()->get_audio_mixer_callback()->allocate_level_control();
         //if (pinteraction == nullptr)
           // return false;

         //pinteraction->create_control(pParent, nBalanceID);
         //::pointer<::audio_mixer::control_data_volume>mcdvBalance = pinteraction->get_data();
         auto pvolumeBalance = øcreate_new <::audio_mixer::control_data_volume>();
         pvolumeBalance->m_iType = ::audio_mixer::control_data::TypeStereoBalance;
         pvolumeBalance->m_uiMixerID = m_pmixersource->get_device()->m_uiMixerID;
         pvolumeBalance->m_uiLineID = source->m_mixerline.dwLineID;
         pvolumeBalance->m_uiControlID = m_mixercontrol.dwControlID;
         pvolumeBalance->nRange = nRange;
         pvolumeBalance->nPageInc = nPageInc;

         create_balance_control(pvolumeBalance, pParent);

         ::pointer<::audio_mixer_user::label>plabel = m_pmixersource->get_device()->get_mixer()->get_audio_mixer_callback()->allocate_label();
         if (plabel == nullptr)
            return false;



         //plabel->create_control(pParent, nBalanceLabelID);
         //::pointer<::audio_mixer::control_data>mcdBalanceLabel = plabel->get_data();
         //mcdBalanceLabel->m_iType = ::audio_mixer::control_data::TypeStereoBalanceLabel;
         //mcdBalanceLabel->m_uiMixerID = m_pmixersource->get_device()->m_uiMixerID;
         //mcdBalanceLabel->m_uiLineID = source->m_mixerline.dwLineID;
         //mcdBalanceLabel->m_uiControlID = m_mixercontrol.dwControlID;
         ////xxx      str.load_string(IDS_MIXER_BALANCE);
         //plabel->set_window_text(str);
         //add(plabel.m_p);


         auto pcontroldataLabel = øcreate_new <::audio_mixer::control_data>();
         pcontroldataLabel->m_iType = ::audio_mixer::control_data::TypeStereoBalanceLabel;
         pcontroldataLabel->m_uiMixerID = m_pmixersource->get_device()->m_uiMixerID;
         pcontroldataLabel->m_uiLineID = source->m_mixerline.dwLineID;
         pcontroldataLabel->m_uiControlID = m_mixercontrol.dwControlID;

         create_balance_label(pcontroldataLabel, pParent);

      }

      *nNextID = nID;

      return true;

   }


   bool control::_001CreateMuteControl(
   ::pointer<::user::interaction>pParent,
   unsigned int nStartID,
   unsigned int * nNextID)
   {
      ASSERT((m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN);

      unsigned int                        cb;
      unsigned int                        lcChannels;
      unsigned int                        lcMultipleItems;


      ASSERT(m_pmixersource != nullptr);

      ::pointer<::audio_mixer_mmsystem::source>source = m_pmixersource;

      lcChannels = (unsigned int)source->m_mixerline.cChannels;
      if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
         lcChannels = 1;

      lcMultipleItems = 1;
      if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
         lcMultipleItems = (unsigned int)m_mixercontrol.cMultipleItems;

      //if(lcChannels > 2)
      //  return false;
      //if(lcMultipleItems != 1)
      //  return false;

      int iItemCount = lcChannels * lcMultipleItems;

      cb = iItemCount * sizeof(MIXERCONTROLDETAILS_BOOLEAN);
      m_mixercontroldetails.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
      if (m_mixercontroldetails.paDetails != nullptr)
         free(m_mixercontroldetails.paDetails);
      m_mixercontroldetails.paDetails = malloc(cb);

      unsigned int nID = nStartID;
      unsigned int nMuteID;

      ::text::text text;

      //auto pcontext = pParent->m_papplication;

      if (m_pmixersource == m_pmixersource->get_destination())
      {

         text = m_papplication->__text("mix::mute_all");

      }
      else
      {

         text = m_papplication->__text("mix::mute");

      }

      auto pdevice = m_pmixersource->get_device();

      auto pmixer = pdevice->get_mixer();

      auto pcallback = pmixer->get_audio_mixer_callback();

      for (int iItem = 0; iItem < iItemCount; iItem++)
      {
         nMuteID = nID++;

         auto pswitchMute = øcreate_new < ::audio_mixer::control_data_switch >();
         pswitchMute->m_iType = ::audio_mixer::control_data::TypeUniformMute;
         pswitchMute->m_uiMixerID = source->get_device()->m_uiMixerID;
         pswitchMute->m_uiControlID = m_mixercontrol.dwControlID;

         create_mute_control(pswitchMute, pParent);

      }

      *nNextID = nID;

      return true;

   }


   /*void control::OnArrayReallocation(void *pNewPointer)
   {
   m_pmixersource = (::audio_mixer::source *) pNewPointer;
   }
   */

   void control::Prepare()
   {
      m_mixercontroldetails.dwControlID = m_mixercontrol.dwControlID;
   }

   /*      ::pointer<::audio_mixer_user::control>control::GetControl(int iType)
         {
            ::audio_mixer_user::control  * pusercontrol = nullptr;
            for(int i = 0; i < this->get_size(); i++)
            {
               pusercontrol = this->element_at(i);
               if(pusercontrol == nullptr)
                  continue;
               if(pusercontrol->m_pdata->get_type() == iType)
               {
                  return pusercontrol;
               }
            }
            return nullptr;
         }

         ::audio_mixer_user::control * control::GetControlByIndex(::collection::index iIndex)
         {
            return this->element_at(iIndex);
         }
         */

   void control::OnMixerControlChange()
   {

      if (m_usercontrola.is_empty())
      {

         return;

      }

      //void                            mmrc;
      //    oswindow                            htxt;
      //    PMACONTROLINSTANCE_FADER        pmaci_fader;
      //    LPMACONTROLINSTANCE             pmaci;
      //    LPMIXERLINE                     pmxl;
      //    LPMIXERCONTROL                  pmxctrl;
      PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u;
      int                             nRange;
      //    int                             nValue;
      unsigned int                            cChannels;
      unsigned int                            cMultipleItems;
      //    unsigned int                            u;
      //    unsigned int                            uIndex;
      //    unsigned int                            v;
      //    MIXERCONTROLDETAILS             mxcd;
      //   oswindow                            hsbFocus;
      //    oswindow                            hsb;


      //    hsbFocus = GetFocus();
      //    if (nullptr == hsbFocus)
      //    {
      //        hsbFocus = get_child_by_id(oswindow, IDD_MACONTROL_MULTICHANNEL_BASE);
      //    }
      //    else
      //    {
      //        uIndex = GetDlgCtrlId(hsbFocus);
      //        if (uIndex < IDD_MACONTROL_MULTICHANNEL_BASE)
      //        {
      //            hsbFocus = get_child_by_id(oswindow, IDD_MACONTROL_MULTICHANNEL_BASE);
      //        }
      //    }


      //
      //
      //
      //    pmaci_fader = (PMACONTROLINSTANCE_FADER)(unsigned int)GetWindowLong(oswindow, DWL_USER);
      //    pmaci       = pmaci_fader->pmaci;
      //    pmxl        = pmaci->pmxl;
      //    pmxctrl     = pmaci->pmxctrl;
      //    pmxcd_u     = &pmaci_fader->pmxcd_u[0];
      //    nRange      = pmaci_fader->nRange;

      ::pointer<::audio_mixer_mmsystem::source>source = m_pmixersource;
      ::pointer<::audio_mixer_mmsystem::device>device = source->get_device();

      cChannels = (unsigned int)source->m_mixerline.cChannels;
      if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
         cChannels = 1;

      m_mixercontroldetails.cChannels = cChannels;


      //
      //
      //
      //    m_mixercontroldetails.cChannels      = cChannels;
      m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;

      MMRESULT mmresult = mixerGetControlDetails((HMIXEROBJ)device->m_hMixer, &m_mixercontroldetails, MIXER_GETCONTROLDETAILSF_VALUE);

      auto estatus = mmresult_status(mmresult);

      if (!estatus)
      {
         //        message_box(nullptr, MB_OK | e_message_box_icon_exclamation,
         //                "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
         //              m_mixercontrol.dwControlID, m_pmixersource->get_device()->m_hMixer, mmrc);
         //return;

         throw ::exception(estatus);

      }

      cMultipleItems = 1;

      if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
         cMultipleItems = (unsigned int)m_mixercontrol.cMultipleItems;

      if (m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME)
      {
         ASSERT(cMultipleItems == 1);
         if (cChannels == 2)
         {
            ::pointer<::audio_mixer::control_data_volume>lpmcdVolume = GetWindowData(::audio_mixer::control_data::TypeStereoVolume);

            //double dActualBalance = pslBalance->GetPos();

            double dActualBalance = balance_get_position();

            nRange = lpmcdVolume->nRange;
            pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED)m_mixercontroldetails.paDetails;
            int nLeftValue = (int)MulDiv(pmxcd_u[0].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);
            int nRightValue = (int)MulDiv(pmxcd_u[1].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);


            int nMaxValue = maximum(nLeftValue, nRightValue);
            int nBalance = nMaxValue == 0 ?
               nRange / 2 :
               (nRange +
                MulDiv(nRightValue - nLeftValue, nRange, nMaxValue)) / 2;


            // pslVolume->SetPos(nRange - nMaxValue);


            volume_set_position(nRange - nMaxValue);

            double dRangeSlack = nMaxValue == 0 ?
               nRange / 2 :
               ((double)nRange) / (2 * nMaxValue) + 0.5;
            if (dActualBalance > nBalance + dRangeSlack ||
                  dActualBalance < nBalance - dRangeSlack)
            {
               //pslBalance->SetPos(nBalance);

               balance_set_position(nBalance);
            }
            informationf("Left %d Right %d nBalance %d\n", nLeftValue, nRightValue, nBalance);
         }
         else if (cChannels == 1)
         {
            //::pointer<::audio_mixer_user::level_control>pslVolume = GetControl(::audio_mixer::control_data::TypeStereoVolume);
            ::pointer<::audio_mixer::control_data_volume>lpmcdVolume = GetWindowData(::audio_mixer::control_data::TypeStereoVolume);

            nRange = lpmcdVolume->nRange;
            
            pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED)m_mixercontroldetails.paDetails;
            
            int nValue = (int)MulDiv(pmxcd_u[0].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);
            
            //int iGetPos = pslVolume->GetPos();
            
            int iGetPos = (int) volume_get_position();

            if (iGetPos != (nRange - nValue))
            {

               //pslVolume->SetPos(nRange - nValue);
               volume_set_position(nRange - nValue);

            }

         }
      }
      else if ((m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN)
      {

         ::collection::index i = 0;

         for (auto & pusercontrol : m_usercontrola)
         {

            //          ::pointer<::audio_mixer_user::toggle_control>pmutecontrol = pusercontrol;

            PMIXERCONTROLDETAILS_BOOLEAN pmxcd_f = (PMIXERCONTROLDETAILS_BOOLEAN)m_mixercontroldetails.paDetails;

            bool fValue = pmxcd_f[cMultipleItems - i - 1].fValue != false;

            //            pmutecontrol->set_check(fValue ? e_check_checked : e_check_unchecked, ::e_source_user);

            mute_set_check(fValue);

            i++;

         }

      }

   }


   /*
   ::audio_mixer::control_data * control::GetWindowData(int iType)
   {
      ::audio_mixer_user::control * pusercontrol = nullptr;
      for(int i = 0; i < this->get_size(); i++)
      {
         pusercontrol = this->element_at(i);
         if(pusercontrol == nullptr)
            continue;
         if(pusercontrol->m_pdata->get_type() == iType)
         {
            return pusercontrol->m_pdata;
         }
      }
      return nullptr;
   }*/

   /*bool control::OnNotify(unsigned int nID, LPNMHDR lpnmhdr)
   {
   __UNREFERENCED_PARAMETER(nID);
   if(lpnmhdr->code == TB_BOTTOM ||
   lpnmhdr->code == TB_ENDTRACK ||
   lpnmhdr->code == TB_LINEDOWN ||
   lpnmhdr->code == TB_LINEUP ||
   lpnmhdr->code == TB_PAGEDOWN ||
   lpnmhdr->code == TB_PAGEUP ||
   lpnmhdr->code == TB_THUMBPOSITION ||
   lpnmhdr->code == TB_THUMBTRACK ||
   lpnmhdr->code == TB_TOP)
   {
   audio_mixer::control * pinteraction = GetControlByDlgCtrlID(lpnmhdr->idFrom);
   if(pinteraction != nullptr)
   {
   //            ::audio_mixer_user::level_control * plevelcontrol = (::audio_mixer_user::level_control *) pinteraction;
   /*if(base_class <CSliderCtrl >::bases(pusercontrol))
   {
   CSliderCtrl * pSlider = (CSliderCtrl *) pusercontrol;
   ::audio_mixer::control_data * pData;
   if(nullptr != (pData = GetWindowDataByDlgCtrlID(lpnmhdr->idFrom)))
   {

   if(pData->get_type() == ::audio_mixer::control_data::TypeStereoBalance ||
   pData->get_type() == ::audio_mixer::control_data::TypeStereoVolume)
   {
   CSliderCtrl * pslBalance;
   CSliderCtrl * pslVolume;
   if(pData->get_type() == ::audio_mixer::control_data::TypeStereoBalance)
   {
   pslBalance = pSlider;
   pslVolume = (CSliderCtrl *) GetControl(::audio_mixer::control_data::TypeStereoVolume)->GetWnd();
   ASSERT(pslVolume != nullptr);
   }
   else if(pData->get_type() == ::audio_mixer::control_data::TypeStereoVolume)
   {
   pslVolume = pSlider;
   pslBalance = (CSliderCtrl *) GetControl(::audio_mixer::control_data::TypeStereoBalance)->GetWnd();
   ASSERT(pslVolume != nullptr);
   }
   m_mixercontroldetails.cChannels = (unsigned int)m_pmixersource->m_mixerline.cChannels;
   if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
   m_mixercontroldetails.cChannels = 1;

   //
   //
   //
   //                        m_mixercontroldetails.cChannels      = cChannels;
   m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
   if(m_mixercontroldetails.cChannels == 2)
   {
   ::audio_mixer::control_data_volume * lpmcdVolume = (::audio_mixer::control_data_volume *) GetWindowData(::audio_mixer::control_data::TypeStereoVolume);
   int nRange = lpmcdVolume->nRange;
   int nBalance  = pslBalance->GetPos();
   int nMaxValue = nRange - pslVolume->GetPos();
   int nMinValue = nBalance * 2 * nMaxValue / nRange;
   int nLeftValue;
   int nRightValue;
   if(nBalance == nRange / 2)
   {
   nLeftValue = nMaxValue;
   nRightValue = nMaxValue;
   }
   else if(nBalance > nRange / 2)
   {
   nLeftValue = nMinValue;
   nRightValue = nMaxValue;
   }
   else
   {
   nLeftValue = nMaxValue;
   nRightValue = nMinValue;
   }

   PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
   pmxcd_u[0].dwValue = (int)MulDiv(
   nLeftValue ,
   m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
   nRange) +  m_mixercontrol.Bounds.dwMinimum;
   pmxcd_u[1].dwValue = (int)MulDiv(
   nRightValue ,
   m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
   nRange) +  m_mixercontrol.Bounds.dwMinimum;
   void     mmrc = mixerSetControlDetails(
   (HMIXEROBJ)m_pmixersource->get_device()->m_hMixer,
   &m_mixercontroldetails,
   MIXER_GETCONTROLDETAILSF_VALUE);
   if (MMSYSERR_NOERROR == mmrc)
   {
   OnMixerControlChange();
   }
   else
   {
   //                                message_box(nullptr, MB_OK | e_message_box_icon_exclamation,
   //                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
   //                                      m_mixercontrol.dwControlID, m_pmixersource->get_device()->m_hMixer, mmrc);
   }

   }
   else if(m_mixercontroldetails.cChannels == 1)
   {
   CSliderCtrl * pslVolume = (CSliderCtrl *) GetControl(::audio_mixer::control_data::TypeStereoVolume)->GetWnd();
   ::audio_mixer::control_data_volume * lpmcdVolume = (::audio_mixer::control_data_volume *) GetWindowData(::audio_mixer::control_data::TypeStereoVolume);
   int nRange = lpmcdVolume->nRange;
   int nValue = nRange - pslVolume->GetPos();
   PMIXERCONTROLDETAILS_UNSIGNED pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
   pmxcd_u[0].dwValue = (int)MulDiv(nValue, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum, nRange) + m_mixercontrol.Bounds.dwMinimum;
   void     mmrc = mixerSetControlDetails(
   (HMIXEROBJ)m_pmixersource->get_device()->m_hMixer,
   &m_mixercontroldetails,
   MIXER_GETCONTROLDETAILSF_VALUE);
   if (MMSYSERR_NOERROR == mmrc)
   {
   OnMixerControlChange();
   }
   else
   {
   //                                message_box(nullptr, MB_OK | e_message_box_icon_exclamation,
   ///                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
   //                                     m_mixercontrol.dwControlID, m_pmixersource->get_device()->m_hMixer, mmrc);
   }
   }
   return true;
   }
   }*/

   //            }
   /*}

   }
   return false;

   }*/

   /*

         ::audio_mixer_user::control * control::GetControlByDlgCtrlID(unsigned int nID)
         {
            ::audio_mixer_user::control * pusercontrol = nullptr;
            for(int i = 0; i < this->get_size(); i++)
            {
               pusercontrol = this->element_at(i);
               if(pusercontrol == nullptr)
                  continue;
               if((unsigned int) pusercontrol->GetDlgCtrlId() == nID)
               {
                  return pusercontrol;
               }
            }
            return nullptr;

         }

         ::audio_mixer::control_data * control::GetWindowDataByDlgCtrlID(unsigned int nID)
         {
            ::audio_mixer_user::control * pusercontrol = nullptr;
            for(int i = 0; i < this->get_size(); i++)
            {
               pusercontrol = this->element_at(i);
               if(pusercontrol == nullptr)
                  continue;
               if((unsigned int) pusercontrol->GetDlgCtrlId() == nID)
               {
                  return pusercontrol->m_pdata;
               }
            }
            return nullptr;
         }
         */

   void control::OnVHScroll(unsigned int nSBCode, unsigned int nPos, ::pointer<::user::interaction>pScrollBar)
   {
      __UNREFERENCED_PARAMETER(nPos);
      ::pointer<::user::interaction>pParamWnd = pScrollBar;
      if (nSBCode == SB_LEFT ||
            nSBCode == SB_ENDSCROLL ||
            nSBCode == SB_LINELEFT ||
            nSBCode == SB_LINERIGHT ||
            nSBCode == SB_PAGELEFT ||
            nSBCode == SB_PAGERIGHT ||
            nSBCode == SB_THUMBPOSITION ||
            nSBCode == SB_THUMBTRACK ||
            nSBCode == SB_RIGHT ||
            nSBCode == SB_BOTTOM ||
            nSBCode == SB_ENDSCROLL ||
            nSBCode == SB_LINEUP ||
            nSBCode == SB_LINEDOWN ||
            nSBCode == SB_PAGEUP ||
            nSBCode == SB_PAGEDOWN ||
            nSBCode == SB_TOP)
      {
         //::audio_mixer_user::control * pinteraction = GetControlByDlgCtrlID(pParamWnd->GetDlgCtrlId().as_unsigned_int());
         //if (pinteraction != nullptr)
         {
            //::audio_mixer_user::level_control * pSlider = dynamic_cast<::audio_mixer_user::level_control *>(pinteraction);
            //if (nullptr != pSlider)
            {
               //mix::SliderInterface * pSlider = dynamic_cast < ::audio_mixer_user::level_control * > ( pusercontrol);
               ::audio_mixer::control_data * pData;
               //if (nullptr != (pData = GetWindowDataByDlgCtrlID(pParamWnd->GetDlgCtrlId().as_unsigned_int())))
               if (nullptr != (pData = GetWindowData(::audio_mixer::control_data::TypeStereoVolume)))
               {

                  if (pData->get_type() == ::audio_mixer::control_data::TypeStereoBalance ||
                        pData->get_type() == ::audio_mixer::control_data::TypeStereoVolume)
                  {
                     ::pointer<::audio_mixer_mmsystem::source>source = m_pmixersource;
                        ::pointer<::audio_mixer_mmsystem::device>device = source->get_device();
                        //::pointer<::audio_mixer_user::level_control>pslBalance;
                        //::pointer<::audio_mixer_user::level_control>pslVolume;
                        if (pData->get_type() == ::audio_mixer::control_data::TypeStereoBalance)
                        {
                           //pslBalance = pSlider;
                           //pslVolume = GetControl(::audio_mixer::control_data::TypeStereoVolume);
                           //ASSERT(pslVolume != nullptr);
                        }
                        else if (pData->get_type() == ::audio_mixer::control_data::TypeStereoVolume)
                        {
                           //pslVolume = pSlider;
                           //pslBalance = GetControl(::audio_mixer::control_data::TypeStereoBalance);
                           //ASSERT(pslVolume != nullptr);
                        }
                     m_mixercontroldetails.cChannels = (unsigned int)source->m_mixerline.cChannels;
                     if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
                        m_mixercontroldetails.cChannels = 1;

                     //
                     //
                     //
                     //m_mixercontroldetails.cChannels      = cChannels;
                     m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
                     if (m_mixercontroldetails.cChannels == 2)
                     {
                        
                        ::pointer<::audio_mixer::control_data_volume>lpmcdVolume = GetWindowData(::audio_mixer::control_data::TypeStereoVolume);
                        
                        int nRange = lpmcdVolume->nRange;
                        
                        //int nBalance = pslBalance->GetPos();

                        int nBalance = (int) balance_get_position();

                        //int nMaxValue = nRange - pslVolume->GetPos();

                        int nMaxValue = nRange - (int) volume_get_position();

                        int nLeftValue;

                        int nRightValue;

                        if (nBalance == nRange / 2)
                        {

                           nLeftValue = nMaxValue;

                           nRightValue = nMaxValue;

                        }
                        else if (nBalance > nRange / 2)
                        {

                           nLeftValue = 2 * nMaxValue - MulDiv(nBalance, 2 * nMaxValue, nRange);

                           nRightValue = nMaxValue;

                        }
                        else
                        {

                           nLeftValue = nMaxValue;

                           nRightValue = MulDiv(nBalance, 2 * nMaxValue, nRange);

                        }

                        PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED)m_mixercontroldetails.paDetails;

                        pmxcd_u[0].dwValue = (int)MulDiv(
                                             nLeftValue,
                                             m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                                             nRange) + m_mixercontrol.Bounds.dwMinimum;

                        pmxcd_u[1].dwValue = (int)MulDiv(
                                             nRightValue,
                                             m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                                             nRange) + m_mixercontrol.Bounds.dwMinimum;

                        MMRESULT mmresult = mixerSetControlDetails((HMIXEROBJ)device->m_hMixer, &m_mixercontroldetails, MIXER_GETCONTROLDETAILSF_VALUE);

                        auto estatus = mmresult_status(mmresult);

                        if (!estatus)
                        {

                           throw ::exception(estatus);

                        }

                        //if (::success == mmrc)
                        //{

                        OnMixerControlChange();

                        //}
                        //else
                        //{
                        //   //                                message_box(nullptr, MB_OK | e_message_box_icon_exclamation,
                        //   //                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                        //   //                                      m_mixercontrol.dwControlID, m_pmixersource->get_device()->m_hMixer, mmrc);
                        //}

                     }
                     else if (m_mixercontroldetails.cChannels == 1)
                     {
                        
                        //CSliderCtrl * pslVolume = (CSliderCtrl *) GetWindow(::audio_mixer::control_data::TypeStereoVolume);
                        
                        ::pointer<::audio_mixer::control_data_volume>lpmcdVolume = GetWindowData(::audio_mixer::control_data::TypeStereoVolume);
                        
                        int nRange = lpmcdVolume->nRange;
                        
                        //int nValue = nRange - pslVolume->GetPos();
                        
                        int nValue = nRange - (int) volume_get_position();

                        PMIXERCONTROLDETAILS_UNSIGNED pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED)m_mixercontroldetails.paDetails;

                        pmxcd_u[0].dwValue = (int)MulDiv(nValue, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum, nRange) + m_mixercontrol.Bounds.dwMinimum;

                        MMRESULT mmresult = mixerSetControlDetails((HMIXEROBJ)device->m_hMixer, &m_mixercontroldetails, MIXER_GETCONTROLDETAILSF_VALUE);

                        auto estatus = mmresult_status(mmresult);

                        if (estatus.failed())
                        {

                           throw ::exception(estatus);

                        }

                        OnMixerControlChange();
                        //}
                        //else
                        //{
                        //   string strMessage;
                        //   strMessage.formatf("mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                        //                     m_mixercontrol.dwControlID, device->m_hMixer, mmrc);
                        //   //pScrollBar->message_box(strMessage, nullptr, e_message_box_icon_exclamation);
                        //}
                     }

                     return;

                  }

               }

            }

         }

      }

   }


   bool control::OnCommand(WPARAM wParam, LPARAM lParam)
   {
      __UNREFERENCED_PARAMETER(lParam);
      WORD wNotifyCode = HIWORD(wParam);
      WORD wID = LOWORD(wParam);

      //::pointer<::audio_mixer_user::control>puserinteraction = GetControlByDlgCtrlID((unsigned int)wID);

      //::pointer<::audio_mixer_user::toggle_control>pmutecontrol = puserinteraction;

      //if (pmutecontrol != nullptr)
      {
         ::pointer<::audio_mixer::control_data>pData;
         //throw ::exception(todo, "find replacement/fix for GetWindowDataByDlgCtrlID");
         //if(nullptr != (pData = GetWindowDataByDlgCtrlID((unsigned int) wID)))
         if (nullptr != (pData = GetWindowData(::audio_mixer::control_data::TypeUniformMute)))
         {
            if (pData->get_type() == ::audio_mixer::control_data::TypeUniformMute)
            {
               if (wNotifyCode == BN_CLICKED)
               {

                  ::pointer<::audio_mixer_mmsystem::source>source = m_pmixersource;
                     ::pointer<::audio_mixer_mmsystem::device>device = source->get_device();

                     m_mixercontroldetails.cChannels = (unsigned int)source->m_mixerline.cChannels;
                     if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
                        m_mixercontroldetails.cChannels = 1;


                  //::collection::index iSel = pmutecontrol->get_data()->m_iIndex;

                  ::collection::index iSel = mute_index();

                  //m_mixercontroldetails.cChannels      = cChannels;
                  m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
                  int cMultipleItems = m_mixercontrol.cMultipleItems;
                  PMIXERCONTROLDETAILS_BOOLEAN   pmxcd_f = (PMIXERCONTROLDETAILS_BOOLEAN)m_mixercontroldetails.paDetails;
                  for (int i = 0; i < m_usercontrola.get_size(); i++)
                  {
                     bool fValue = i == iSel ? 1 : 0;
                     pmxcd_f[cMultipleItems - i - 1].fValue = fValue;
                  }

                  MMRESULT mmresult = mixerSetControlDetails((HMIXEROBJ)device->m_hMixer, &m_mixercontroldetails, MIXER_GETCONTROLDETAILSF_VALUE);

                  auto estatus = mmresult_status(mmresult);

                  if (!estatus)
                  {

                     throw ::exception(estatus);

                  }

                  OnMixerControlChange();

                  //}
                  //else
                  //{

                  //   string strMessage;

                  //   strMessage.formatf("mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                  //                     m_mixercontrol.dwControlID, device->m_hMixer, mmrc);
                  //   //pmutecontrol->message_box(strMessage, nullptr, e_message_box_icon_exclamation);
                  //}
                  // 

                  return true;

               }

            }

         }

      }

      return false;

   }


   bool control::control_type(::audio_mixer::e_control econtrol) const
   {

      switch (econtrol)
      {
      case ::audio_mixer::control_boolean:
         return (m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN;
      case ::audio_mixer::control_volume:
         return m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME;
      case ::audio_mixer::control_mux:
         return m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_MUX;
      default:
         return ::audio_mixer::control::control_type(econtrol);
      };

   }


   iptr control::add(::audio_mixer::user_control * pusercontrol)
   {

      return ::audio_mixer::control::add(pusercontrol);
      //pinteraction->get_data()->m_iIndex = m_usercontrola.get_size();
      //auto im_usercontrola.add(pinteraction);
      //return control_ptr_array::get_upper_bound();
   }


   MIXERCONTROL & control::GetMixerControl()
   {
      return m_mixercontrol;
   }


   //unsigned int control::GetMixerControlId()
   //{

   //   return m_mixercontrol.dwControlID;

   //}


   MIXERCONTROLDETAILS & control::GetMixerControlDetails()
   {
      return m_mixercontroldetails;
   }


} // namespace audio_mixer_mmsystem
//
//
//} // namespace multimedia
//
//
//
//
