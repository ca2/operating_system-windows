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
      //::audio_mixer::control_data * GetWindowDataByDlgCtrlID(unsigned int nID);
      //::audio_mixer::user_control * GetControlByDlgCtrlID(unsigned int nID);
      //   bool OnNotify(unsigned int nID, LPNMHDR lpnmhdr);
      void OnVHScroll(unsigned int nSBCode, unsigned int nPos, ::pointer<::user::interaction>pScrollBar);
      //::audio_mixer::control_data * GetWindowData(int iType);
      void OnMixerControlChange();
      //::audio_mixer::user_control * GetControl(int iType);
      //::audio_mixer::user_control * GetControlByIndex(::collection::index iIndex);
      void Prepare();
      bool CreateWindowsVolumeV001(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID);

      //  bool _001CreateMuteControl(::pointer<::user::interaction>pParent, CRuntimeClass * pruntimeclassMuteControl, unsigned int nStartID, unsigned int * nNextID);
      bool _001CreateMuteControl(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID);

      bool CreateWindows(::pointer<::user::interaction>pParent, int iStyle);

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
