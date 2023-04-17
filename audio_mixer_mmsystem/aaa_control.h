#pragma once


#include "audio-system/audio_mixer/control.h"

//
//namespace multimedia
//{
//

namespace audio_mixer_mmsystem
{


   class CLASS_DECL_AUDIO_MIXER_MMSYSTEM control :
      virtual public ::audio_mixer::control
   {
   public:


      enum Styles
      {
         StyleV001 = 1
      };


      MIXERCONTROL                     m_mixercontrol;
      MIXERCONTROLDETAILS              m_mixercontroldetails;


      control();
      ~control() override;


      virtual iptr add(::audio_mixer::user_control * pinteraction);


      bool control_type(::audio_mixer::e_control econtrol) const;
      bool OnCommand(WPARAM wParam, LPARAM lParam);
      //::audio_mixer::control_data * GetWindowDataByDlgCtrlID(u32 nID);
      //::audio_mixer::user_control * GetControlByDlgCtrlID(u32 nID);
      //   bool OnNotify(u32 nID, LPNMHDR lpnmhdr);
      void OnVHScroll(u32 nSBCode, u32 nPos, ::pointer<::user::interaction>pScrollBar);
      //::audio_mixer::control_data * GetWindowData(i32 iType);
      void OnMixerControlChange();
      //::audio_mixer::user_control * GetControl(i32 iType);
      //::audio_mixer::user_control * GetControlByIndex(::index iIndex);
      void Prepare();
      bool CreateWindowsVolumeV001(::pointer<::user::interaction>pParent, u32 nStartID, u32 * nNextID);

      //  bool _001CreateMuteControl(::pointer<::user::interaction>pParent, CRuntimeClass * pruntimeclassMuteControl, u32 nStartID, u32 * nNextID);
      bool _001CreateMuteControl(::pointer<::user::interaction>pParent, u32 nStartID, u32 * nNextID);

      bool CreateWindows(::pointer<::user::interaction>pParent, i32 iStyle);

      MIXERCONTROL & GetMixerControl();
      MIXERCONTROLDETAILS & GetMixerControlDetails();


   };


} // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
//
