#include "framework.h"
#include "device.h"
#include "destination.h"
#include "control.h"
#include "acme/exception/exception.h"
#include "aura/message/user.h"
#include "audio-system/audio_mixer/control.h"
#include "audio-system/audio_mixer/user_control.h"

//
//namespace multimedia
//{


namespace audio_mixer_mmsystem
{


   device::device()
   {

      m_hMixer = nullptr;

   }


   device::~device()
   {

      close();

   }


   void device::initialize_audio_mixer_device(::audio_mixer::audio_mixer * pmixer)
   {

      //auto estatus = 

      ::audio_mixer::device::initialize_audio_mixer_device(pmixer);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void device::open(u32 uiMixerId, UINT_PTR dwCallback, u32 dwInstance, u32 fdwOpen)
   {

      MMRESULT          mmresult;
      HMIXER            hmx;
      MIXERCAPS         mxcaps;


      if (m_hMixer != nullptr)
      {

         //MMRESULT mmresult;

         close();

         //if(::success != mmrct)
         //{

            //string strMessage;

            //strMessage.format("mixerClose() failed on hmx=%.04Xh, mmr=%u!", m_hMixer, mmrct);

            //message_box(this, strMessage, nullptr, e_message_box_icon_exclamation);

         //}

      }

      mmresult = mixerGetDevCaps(uiMixerId, &mxcaps, sizeof(mxcaps));

      auto estatus = mmresult_to_status(mmresult);

      if (::failed(estatus))
      {

         //string strMessage;

         //strMessage.format("mixerGetDevCaps() failed on uMxId=%u, mmr=%u!", uiMixerId, mmrc);

         ////message_box(strMessage, nullptr, e_message_box_icon_exclamation);

         //return mmrc;

         throw ::exception(estatus);

      }

      mmresult = mixerOpen(&hmx, uiMixerId, dwCallback, dwInstance, fdwOpen);

      estatus = mmresult_to_status(mmresult);

      if (::failed(estatus))
      {

         //string strMessage;

         //strMessage.format("mixerOpen() failed on uMxId=%u, mmr=%u!", uiMixerId, mmrc);

         //message_box(strMessage, nullptr, e_message_box_icon_exclamation);

         //return mmrc;

         throw ::exception(estatus);

      }

      m_hMixer = hmx;

      m_uiMixerID = uiMixerId;

      //    AppSetWindowText(oswindow, "::audio_mixer::audio_mixer Device: %s", (char *)mxcaps.szPname);

      //return mmrc;

   }


   void device::initialize_capabilities()
   {

      MMRESULT mmresult;

      mmresult = mixerGetDevCaps((UINT_PTR)m_hMixer, &m_mixercaps, sizeof(MIXERCAPS));

      auto estatus = mmresult_to_status(mmresult);

      if (::failed(estatus))
      {

         //string strMessage;

         //strMessage.format("mixerGetDevCaps() failed on uMxId=%u, mmr=%u!", m_uiMixerID, mmrc);

         ////message_box(strMessage, nullptr, e_message_box_icon_exclamation);

         //return mmrc;

         throw ::exception(estatus);

      }

      //return mmrc;

   }


   void device::initialize_destinations()
   {

      ::pointer<::audio_mixer_mmsystem::destination> lpDestination;

      m_mixerdestinationa.set_size_create(this, m_mixercaps.cDestinations);

      for (i32 i = 0; (u32)i < m_mixercaps.cDestinations; i++)
      {
         lpDestination = m_mixerdestinationa[i];
         lpDestination->set_device(this);
         lpDestination->get_line_info(0, i, MIXER_GETLINEINFOF_DESTINATION);
         //        ::audio_mixer::audio_mixer::get_component_name(lpmxl, lpDestination->m_strComponent);

         //        //
         //      //
         //    //
         //  wsprintf(ach, gszLineFormatList,
         //         (char *)szLineTypeDst,
         //       (MIXERLINE_LINEF_ACTIVE & mxl.fdwLine) ? '*' : ' ',
         //     (LPTSTR)szComponent,
         //   mxl.dwLineID,
         //   mxl.fdwLine,
         // mxl.cControls,
         // mxl.cConnections,
         //(char *)mxl.szName);

         //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
         //      {
         //        MixAppDebugLog(ach);
         //      MixAppDebugLog(gszCRLF);
         //  }

         //        nIndex = ListBox_AddString(ptlb->hlb, ach);
         //      ListBox_SetItemData(ptlb->hlb, nIndex, mxl.dwLineID);

      }


      //
      //
      //
      //    SetWindowRedraw(ptlb->hlb, true);
      //return ::success;

   }


   ::pointer<::audio_mixer::destination>device::get_destination(::audio_mixer::e_destination edestination)
   {

      u32 dwComponentType;

      switch (edestination)
      {
      case ::audio_mixer::destination_digital:
         dwComponentType = MIXERLINE_COMPONENTTYPE_DST_DIGITAL;
         break;

      case ::audio_mixer::destination_speakers:
         dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
         break;

      default:
         throw ::exception(error_bad_argument);
      };


      if (m_mixerdestinationa.get_size() <= 0)
         initialize_destinations();

      if (m_mixerdestinationa.get_size() <= 0)
         throw ::exception(error_wrong_state);

      for (i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
      {

         ::pointer<::audio_mixer_mmsystem::destination>destination = m_mixerdestinationa[i];

         u32 dw = destination->m_mixerline.dwComponentType;

         if (dw == dwComponentType)
         {

            return m_mixerdestinationa[i];

         }

      }

      return nullptr;

   }


   void device::map_controls()
   {

      m_mapIDToControl.erase_all();

      for (i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
      {

         ::pointer<::audio_mixer_mmsystem::destination>destination = m_mixerdestinationa[i];

         MapLineControls(destination);

         ::audio_mixer::source_array & sourcea = destination->get_source_info();

         for (i32 j = 0; j < sourcea.get_size(); j++)
         {

            ::pointer<::audio_mixer::source>source = sourcea[j];

            MapLineControls(source);

         }

      }

   }


   void device::map_lines()
   {

      m_mapIDToLine.erase_all();

      for (i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
      {

         ::pointer<::audio_mixer_mmsystem::destination>destination = m_mixerdestinationa[i];

         m_mapIDToLine.set_at(destination->get_mixer_line().dwLineID, destination);

         ::audio_mixer::source_array & sourcea = destination->get_source_info();

         for (i32 j = 0; j < sourcea.get_size(); j++)
         {

            ::pointer<::audio_mixer_mmsystem::source>source = sourcea[j];

            m_mapIDToLine.set_at(source->m_mixerline.dwLineID, source);

         }

      }

   }


   void device::OnMixerLineChange(u32 dwLineID)
   {

      auto psource = m_mapIDToLine[dwLineID];

      if (psource)
      {

         psource->OnMixerLineChange();

      }

   }


   void device::OnMixerControlChange(u32 dwControlID)
   {

      auto pcontrol = m_mapIDToControl[dwControlID];

      if (pcontrol)
      {

         pcontrol->OnMixerControlChange();

      }

   }


   void device::MapLineControls(::audio_mixer::source * psource)
   {

      ::audio_mixer::control_array & controla = psource->get_control_array();

      for (auto & pcontrol : controla)
      {

         ::pointer<control>pcontrolMMSystem = pcontrol;

         auto dwControlId = pcontrolMMSystem->GetMixerControl().dwControlID;

         m_mapIDToControl[dwControlId] = pcontrol;

         for (auto & pusercontrol : pcontrol->m_usercontrola)
         {

            m_mapDlgItemIDToControl.set_at(pusercontrol->get_dialog_control_id(), pcontrol);

         }

      }

   }


   void device::MapDlgCtrlIDToControls()
   {

      m_mapDlgItemIDToControl.erase_all();

      auto & destinationa = m_mixerdestinationa;

      for (auto & pdestination : destinationa)
      {

         MapDlgCtrlIDToLineControls(pdestination);

         auto & sourcea = pdestination->get_source_info();

         for (auto & psource : sourcea)
         {

            MapDlgCtrlIDToLineControls(psource);

         }

      }

   }


   void device::MapDlgCtrlIDToLineControls(::audio_mixer::source * psource)
   {

      auto & controla = psource->get_control_array();

      for (auto & pcontrol : controla)
      {

         for (auto & pusercontrol : pcontrol->m_usercontrola)
         {

            m_mapDlgItemIDToControl[pusercontrol->get_dialog_control_id()] = pcontrol;

         }

      }

   }


   void device::close()
   {

      if (m_hMixer != nullptr)
      {

         MMRESULT mmresult = mixerClose(m_hMixer);

         auto estatus = mmresult_to_status(mmresult);

         if (!estatus)
         {

            throw ::exception(estatus);

         }

         m_mixerdestinationa.erase_all();

         m_mapIDToControl.erase_all();

         m_mapDlgItemIDToControl.erase_all();

         m_mapIDToLine.erase_all();

         m_hMixer = nullptr;

      }

   }


   void device::on_message(::message::message * pmessage)
   {

      ::atom uiID = LOWORD(pmessage->m_wparam);

      auto pcontrol = m_mapDlgItemIDToControl[uiID];

      if (::is_set(pcontrol))
      {

         pcontrol->on_message(pmessage);

      }

   }


   string device::get_product_name()
   {

      return m_mixercaps.szPname;

   }


   ::audio_mixer::audio_mixer * device::get_mixer()
   {

      return m_paudiomixer;

   }


} // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//

