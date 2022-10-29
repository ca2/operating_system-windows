#include "framework.h"
#include "audio_mixer.h"
#include "interaction.h"
#include "device.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      audio_mixer::audio_mixer()
      {

         //m_window.m_pmixer = this;

//         m_pdevice = new ::multimedia::audio_mixer::device(this);

      }


      audio_mixer::~audio_mixer()
      {

         if(m_pwindow->is_window())
         {

            m_pwindow->start_destroying_window();

         }

         /*         if(m_pdevice != nullptr)
                  {

                     delete m_pdevice;

                     m_pdevice = nullptr;

                  }*/

      }


      void audio_mixer::initialize(::particle * pparticle)
      {

         ::multimedia::audio_mixer::audio_mixer::initialize(pobject);

         __construct_new(m_pwindow);

         m_pwindow->m_paudiomixer = this;

         m_pwindow->create_message_queue("audio_mixer");

      }


      void audio_mixer::set_new_device(u32 uiMixerId)
      {

         m_paudiomixerdevice->open(uiMixerId, (UINT_PTR)m_pwindow->oswindow(), 0, CALLBACK_WINDOW);

      }


      bool audio_mixer::get_component_name(LPMIXERLINE pmxl, string & strComponent)
      {

         if (0 == (MIXERLINE_LINEF_SOURCE & pmxl->fdwLine))
         {
            switch (pmxl->dwComponentType)
            {
            case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED:
               strComponent = "Undefined";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_DIGITAL:
               strComponent = "Digital";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_LINE:
               strComponent = "Line Level";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_MONITOR:
               strComponent = "Monitor";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:
               strComponent = "Speakers";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES:
               strComponent = "Headphones";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE:
               strComponent = "Telephone";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_WAVEIN:
               strComponent = "Wave Input";
               break;

            case MIXERLINE_COMPONENTTYPE_DST_VOICEIN:
               strComponent = "Voice Recognition";
               break;

            default:
               strComponent = "NOT VALID";
               break;
            }
         }
         else
         {
            switch (pmxl->dwComponentType)
            {
            case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED:
               strComponent = "Undefined";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:
               strComponent = "Digital";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_LINE:
               strComponent = "Line Level";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:
               strComponent = "Microphone";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER:
               strComponent = "Synthesizer";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:
               strComponent = "Compact Disc";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE:
               strComponent = "Telephone";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER:
               strComponent = "PC Speaker";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:
               strComponent = "Wave Out";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:
               strComponent = "Auxiliary";
               break;

            case MIXERLINE_COMPONENTTYPE_SRC_ANALOG:
               strComponent = "Analog";
               break;

            default:
               strComponent = "NOT VALID";
               break;
            }
         }

         return true;

      }


      bool audio_mixer::get_control_type_name(LPMIXERCONTROL pmxctrl, string & strTypeName)
      {

         switch (pmxctrl->dwControlType)
         {
         case MIXERCONTROL_CONTROLTYPE_CUSTOM:
            strTypeName = "Custom!";
            break;

         case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER:
            strTypeName = "Boolean Meter";
            break;

         case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER:
            strTypeName = "Signed Meter";
            break;

         case MIXERCONTROL_CONTROLTYPE_PEAKMETER:
            strTypeName = "Peak Meter";
            break;

         case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER:
            strTypeName = "Unsigned Meter";
            break;

         case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
            strTypeName = "Boolean Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_ONOFF:
            strTypeName = "On/Off Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_MUTE:
            strTypeName = "Mute Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_MONO:
            strTypeName = "Mono Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
            strTypeName = "Loudness Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_STEREOENH:
            strTypeName = "Stereo Enh Switch";
            break;

         case MIXERCONTROL_CONTROLTYPE_BUTTON:
            strTypeName = "button";
            break;

         case MIXERCONTROL_CONTROLTYPE_DECIBELS:
            strTypeName = "Decibels Number";
            break;

         case MIXERCONTROL_CONTROLTYPE_SIGNED:
            strTypeName = "Signed Number";
            break;

         case MIXERCONTROL_CONTROLTYPE_PERCENT:
            strTypeName = "Percent Number";
            break;

         case MIXERCONTROL_CONTROLTYPE_UNSIGNED:
            strTypeName = "Unsigned Number";
            break;

         case MIXERCONTROL_CONTROLTYPE_SLIDER:
            strTypeName = "slider";
            break;

         case MIXERCONTROL_CONTROLTYPE_PAN:
            strTypeName = "Pan slider";
            break;

         case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN:
            strTypeName = "Q-Sound Pan slider";
            break;

         case MIXERCONTROL_CONTROLTYPE_FADER:
            strTypeName = "Fader";
            break;

         case MIXERCONTROL_CONTROLTYPE_VOLUME:
            strTypeName = "Volume Fader";
            break;

         case MIXERCONTROL_CONTROLTYPE_BASS:
            strTypeName = "Bass Fader";
            break;

         case MIXERCONTROL_CONTROLTYPE_TREBLE:
            strTypeName = "Treble Fader";
            break;

         case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
            strTypeName = "Equalizer Fader";
            break;

         case MIXERCONTROL_CONTROLTYPE_SINGLESELECT:
            strTypeName = "Single-Sel List";
            break;

         case MIXERCONTROL_CONTROLTYPE_MUX:
            strTypeName = "MUX List";
            break;

         case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT:
            strTypeName = "Multi-Sel List";
            break;

         case MIXERCONTROL_CONTROLTYPE_MIXER:
            strTypeName = "audio_mixer List";
            break;

         case MIXERCONTROL_CONTROLTYPE_MICROTIME:
            strTypeName = "Microsecond time";
            break;

         case MIXERCONTROL_CONTROLTYPE_MILLITIME:
            strTypeName = "::duration time";
            break;

         default:
            ASSERT(false);
            //            DPF(0, "!MixAppGetControlTypeName: invalid control type %.08lXh!", pmxctrl->dwControlType);
            strTypeName = "** NOT VALID **";
            return (false);
         }

         return true;

      }

      void audio_mixer::OnMixerLineChange(HMIXER hMixer, u32 dwLineID)
      {

         ::pointer<::multimedia::audio_mixer_mmsystem::device>device = m_paudiomixerdevice;

         if(hMixer == device->m_hMixer)
         {

            device->OnMixerLineChange(dwLineID);

         }
         else
         {

            ASSERT(false);

         }

      }


      void audio_mixer::OnMixerControlChange(HMIXER hMixer, u32 dwControlID)
      {

         ::pointer<::multimedia::audio_mixer_mmsystem::device>device = m_paudiomixerdevice;

         if(hMixer == device->m_hMixer)
         {

            device->OnMixerControlChange(dwControlID);

         }
         else
         {

            ASSERT(false);

         }

      }


      void audio_mixer::on_message(::message::message * pmessage)
      {

         ::pointer<::multimedia::audio_mixer_mmsystem::device>pdevice = m_paudiomixerdevice;

         if (::is_set(pdevice))
         {

            pdevice->on_message(pmessage);

         }

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia
