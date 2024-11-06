#include "framework.h"
#include "source.h"
#include "device.h"
#include "control.h"
#include "destination.h"
#include "acme/exception/exception.h"
#include "audio-system/audio_mixer/user_control.h"
#include "acme_windows/mmresult.h"



//
//
//namespace multimedia
//{


   namespace audio_mixer_mmsystem
   {


      source::source()
      {

         m_pdestination = nullptr;
         m_mixerlinecontrols.pamxctrl = nullptr;

      }

      source::~source()
      {

      }


      void source::GetLineControls()
      {

         MMRESULT mmresult;

         m_bHasV001Controls = false;
         int iControlCount = m_mixerline.cControls;
         if (0 == iControlCount)
         {
            //        message_box(nullptr, MB_OK | e_message_box_icon_exclamation,
            //"There are no controls associated with the selected line.");
            //        EndDialog(oswindow, false);
            //return ::success;

            return;

         }

         m_mixercontrola.set_size_create(this, iControlCount);

         if (m_mixerlinecontrols.pamxctrl != nullptr)
         {
             delete[](MIXERCONTROL*) m_mixerlinecontrols.pamxctrl;

         }

         m_mixerlinecontrols.cbStruct       = sizeof(MIXERLINECONTROLS);
         m_mixerlinecontrols.dwLineID       = m_mixerline.dwLineID;
         ////////////mxlc.dwControlID    = 0;
         ////////////mxlc.dwControlType  = 0;
         m_mixerlinecontrols.cControls      = iControlCount;
         m_mixerlinecontrols.cbmxctrl       = sizeof(*m_mixerlinecontrols.pamxctrl);
         m_mixerlinecontrols.pamxctrl       = ___new MIXERCONTROL[m_mixerline.cControls];

         for (int i = 0; i < iControlCount; i++)
         {
            m_mixerlinecontrols.pamxctrl[i].cbStruct = sizeof(MIXERCONTROL);
         }

         ::pointer<::audio_mixer_mmsystem::device>device = get_device();

         mmresult = mixerGetLineControls((HMIXEROBJ) device->m_hMixer, &m_mixerlinecontrols, MIXER_GETLINECONTROLSF_ALL);

         auto estatus = mmresult_status(mmresult);

         if (estatus.failed())
         {

            //string strMessage;

            //strMessage.formatf("mixerGetLineControls(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
            //                  m_mixerline.dwLineID, device->m_hMixer, mmrc);


            ////message_box(strMessage, nullptr, e_message_box_icon_exclamation);

            throw ::exception(estatus);

         }
         else
         {
            //        char       ach[128];
            //      char       szControlType[64];
            //        unsigned int        u;
            //    int         nIndex;
            PMIXERCONTROL       pamxctrl;
            //        LPMIXERCONTROLDETAILS lpmcd;
            ::pointer<::audio_mixer_mmsystem::control>    lpMixerControl;

            //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
            //          MixAppDebugLog(nullptr);

            for (int i = 0; (unsigned int) i < m_mixerlinecontrols.cControls; i++)
            {
               lpMixerControl = m_mixercontrola[i];
               lpMixerControl->m_pmixersource = this;
               pamxctrl = &lpMixerControl->GetMixerControl();
               //m_mixerlinecontrols.pamxctrl = pamxctrl;
               //*m_mixerlinecontrols.pamxctrl = m_mixerlinecontrols.pamxctrl[i];
               *pamxctrl = m_mixerlinecontrols.pamxctrl[i];
               lpMixerControl->Prepare();
               //            ::audio_mixer::audio_mixer::get_control_type_name(pamxctrl, lpMixerControl->m_strTypeName);

               switch (pamxctrl->dwControlType)
               {
               //            case MIXERCONTROL_CONTROLTYPE_FADER:
               case MIXERCONTROL_CONTROLTYPE_VOLUME:
               //          case MIXERCONTROL_CONTROLTYPE_BASS:
               //        case MIXERCONTROL_CONTROLTYPE_TREBLE:
               //      case MIXERCONTROL_CONTROLTYPE_EQUALIZER:

               //    case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
               //  case MIXERCONTROL_CONTROLTYPE_ONOFF:
               case MIXERCONTROL_CONTROLTYPE_MUTE:
                  //            case MIXERCONTROL_CONTROLTYPE_MONO:
                  //          case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
                  //        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
                  m_bHasV001Controls = true;
                  break;

               default:;
               }
               //
               //
               //
               //            wsprintf(ach, gszLineControlsFormatList,
               //                  u,
               //                (LPTSTR)szControlType,
               //              pamxctrl[u].dwControlID,
               //            pamxctrl[u].fdwControl,
               //          pamxctrl[u].cMultipleItems,
               //        (char *)pamxctrl[u].szName);

               //            if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
               //          {
               //            MixAppDebugLog(ach);
               //          MixAppDebugLog(gszCRLF);
               //    }

               //            nIndex = ListBox_AddString(ptlb->hlb, ach);
               //          ListBox_SetItemData(ptlb->hlb, nIndex, pamxctrl[u].dwControlID);
            }

            //    ListBox_SetCurSel(ptlb->hlb, 0);
            //  enable_window(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_INFO), true);
            //enable_window(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_SETTINGS), true);
         }

         //    SetWindowRedraw(ptlb->hlb, true);
         //  LocalFree((HLOCAL)pamxctrl);
         //return mmrc;

      }

      /*void     source::GetControl(unsigned int dwControlType, unsigned int dwControlFlags,  ::audio_mixer::control ** ppControl)
      {
      ::audio_mixer::control_array & controla = m_mixercontrola;
      if(controla.get_size() <= 0)
      GetLineControls();
      if(controla.get_size() <= 0)
      return MMSYSERR_ERROR;
      for(int i = 0; i < controla.get_size(); i++)
      {
      if((dwControlType != 0 && controla[i].GetControlType() == dwControlType)
      || (dwControlType == 0 && ((controla[i].GetControlType() & dwControlFlags) != 0)))
      {
      *ppControl = controla(i);
      return MMSYSERR_NOERROR;
      }
      }
      return MMSYSERR_ERROR;
      }*/

      /*void source::OnArrayReallocation(void *pNewPointer)
      {
      m_pmixerdestination = (::audio_mixer::destination *) pNewPointer;
      }*/

      void source::OnMixerLineChange()
      {

      }



      void source::update_all_controls()
      {
         ::audio_mixer::control_array & controla = get_control_array();
         for(int i = 0; i < controla.get_size(); i++)
         {
            controla[i]->OnMixerControlChange();
         }
      }


      string source::get_source_name()
      {

         return m_mixerline.szName;

      }


      string source::get_source_short_name()
      {

         return m_mixerline.szShortName;

      }


      ::atom source::GetLineID()
      {
         return (huge_integer) m_mixerline.dwLineID;
      }


      ::audio_mixer::device * source::get_device()
      {
         return m_pdestination->get_device();
      }

      void source::SetDestination(::audio_mixer::destination * pdestination)
      {
         m_pdestination = pdestination;
      }


      void source::get_line_info(unsigned int dwSource, unsigned int dwDestination, unsigned int fdwInfo)
      {

         m_mixerline.cbStruct       = sizeof(MIXERLINE);
         m_mixerline.dwDestination  = dwDestination;
         m_mixerline.dwSource       = dwSource;

         ::pointer<::audio_mixer_mmsystem::device>device = get_device();

         MMRESULT mmresult = ::mixerGetLineInfo((HMIXEROBJ)device->m_hMixer, &m_mixerline, fdwInfo);

         auto estatus = mmresult_status(mmresult);

         if (estatus.failed())
         {

            //string strMessage;

            //strMessage.formatf("mixerGetLineInfo(src=%u) failed on hmx=%.04Xh, mmr=%u!",
            //                  dwSource, device->m_hMixer, mmrc);
            ////message_box(strMessage, nullptr, e_message_box_icon_exclamation);

            throw ::exception(estatus);

         }

         //return mmrc;

      }


      void source::get_line_info(unsigned int dwSource, ::audio_mixer::destination * pdestination)
      {

         ::pointer<::audio_mixer_mmsystem::destination>destination = pdestination;

         get_line_info(dwSource, destination->m_mixerline.dwDestination, MIXER_GETLINEINFOF_SOURCE);

         SetDestination(pdestination);

         //return mmrc;

      }


      ::audio_mixer::destination * source::get_destination()
      {

         return m_pdestination;

      }


      bool source::HasV001Controls()
      {
         return m_bHasV001Controls;
      }

      ::audio_mixer::control_array & source::get_control_array()
      {
         return m_mixercontrola;
      }

      MIXERLINE & source::get_mixer_line()
      {
         return m_mixerline;
      }

      MIXERLINECONTROLS & source::get_mixer_line_controls()
      {
         return m_mixerlinecontrols;
      }


   } // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
//
