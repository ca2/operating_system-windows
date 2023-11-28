#include "framework.h"
#include "midi.h"
#include "sequencer.h"
#include "out.h"
#include "in.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"


#include <mmddk.h>

// http://blogs.msdn.com/b/matthew_van_eerde/archive/2012/09/21/enumerating-midi-devices.aspx
// Maurits [MSFT]
//21 Sep 2012 9:31 AM

////0
//// MSDN Blogs > Matthew van Eerde's web log > Enumerating MIDI devices
//#undef LOG
//#define log_information((format, ...) information(format, __VA_ARGS__)




namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         midi::midi()
         {

            m_pMidi = this;

            m_strName = "mmsystem";

         }


         midi::~midi()
         {

         }


         void midi::initialize(::particle* pparticle)
         {

            ::music::midi::midi::initialize(pparticle);

            defer_create_synchronization();

            m_pparticleMidiMutex = acmenode()->create_mutex();

         }


         //::pointer<::music::midi::sequence>midi::create_midi_sequence(const string& strDevice)
         //{

         //   string strEngine = device_engine(strDevice);

         //   if (strEngine.case_insensitive_order(m_strName) == 0)
         //   {

         //      return __allocate< sequence >(this, strDevice);

         //   }

         //   return nullptr;

         //}



         ::pointer<::music::midi::sequencer>midi::create_midi_sequencer(sequence* psequence, const string& strDevice)
         {

            string strEngine = device_engine(strDevice);

            if (strEngine.case_insensitive_equals(m_strName))
            {

               return __allocate< sequencer >(psequence, strDevice);

            }

            auto psequencer = ::music::midi::midi::create_midi_sequencer(psequence, strDevice);

            if (psequencer)
            {

               return psequencer;

            }

            return __allocate< sequencer >(psequence, strDevice);

         }


         //void     midi::enumerate_midi_devices()
         //{

         //   UINT_PTR devs = midiInGetNumDevs();

         //   information() << "midiIn devices: %u", devs;

         //   for (UINT_PTR dev = 0; dev < devs; dev++)
         //   {

         //      MIDIINCAPSW caps = {};

         //      MMRESULT mmr = midiInGetDevCapsW(dev, &caps, sizeof(caps));

         //      if (MMSYSERR_NOERROR != mmr)
         //      {

         //         return translate_os_result(mmr, "enumerate_midi_devices", "midiInGetDevCapsW");

         //      }

         //      m_uiaIn.add(dev);

         //      mmsystem_LogMidiInCaps(dev, caps);

         //      mmsystem_GetMidiInDeviceInterface(dev);

         //   }

         //   devs = midiOutGetNumDevs();

         //   information() << "midiOut devices: %u", devs;

         //   for (UINT dev = 0; dev < devs; dev++)
         //   {

         //      MIDIOUTCAPSW caps = {};

         //      MMRESULT mmr = midiOutGetDevCapsW(dev, &caps, sizeof(caps));

         //      if (MMSYSERR_NOERROR != mmr)
         //      {

         //         return translate_os_result(mmr, "enumerate_midi_devices", "midiOutGetDevCaps");

         //      }

         //      mmsystem_LogMidiOutCaps(dev, caps);

         //      mmsystem_GetMidiOutDeviceInterface(dev);

         //      m_varaMidiOutDevice.add(dev);

         //   }

         //   return ::success;

         //}




         void midi::mmsystem_GetMidiInDeviceInterface(UINT_PTR i)
         {

            // query the size_i32 of the device interface string
            HMIDIIN h = reinterpret_cast<HMIDIIN>(i);
            ULONG size = 0;
            MMRESULT mmr = midiInMessage(
                           h,
                           DRV_QUERYDEVICEINTERFACESIZE,
                           reinterpret_cast<DWORD_PTR>(&size),
                           0
                           );
            if (MMSYSERR_NOERROR != mmr)
            {
               information() << "midiInMessage(DRV_QUERYDEVICEINTERFACESIZE) failed: mmr = 0x%08x", mmr;
               return;
            }

            if (0 == size)
            {
               information() << "No device interface";
               return;
            }
            if (size % sizeof(WCHAR))
            {
               information() << "Device interface length in bytes (%u) should be a multiple of the size_i32 of a WCHAR!", size;
               return;
            }

            wstring wstr;
            wstr.get_buffer(size);




            mmr = midiInMessage(
                  h,
                  DRV_QUERYDEVICEINTERFACE,
                  reinterpret_cast<DWORD_PTR>((wchar_t *) wstr.c_str()),
                  size
                  );

            wstr.release_buffer();

            if (MMSYSERR_NOERROR != mmr)
            {
               information() << "midiInMessage(DRV_QUERYDEVICEINTERFACE) failed: mmr = 0x%08x", mmr;
               return;
            }

            string str(wstr);

            information() << "    Device interface: \"%s\"", str;
         }

         void midi::mmsystem_GetMidiOutDeviceInterface(UINT_PTR i)
         {

            // query the size_i32 of the device interface string
            HMIDIOUT h = reinterpret_cast<HMIDIOUT>(i);
            ULONG size = 0;
            MMRESULT mmr = midiOutMessage(
                           h,
                           DRV_QUERYDEVICEINTERFACESIZE,
                           reinterpret_cast<DWORD_PTR>(&size),
                           0
                           );
            if (MMSYSERR_NOERROR != mmr)
            {
               information() << "midiOutMessage(DRV_QUERYDEVICEINTERFACESIZE) failed: mmr = 0x%08x", mmr;
               return;
            }

            if (0 == size)
            {
               information() << "No device interface";
               return;
            }
            if (size % sizeof(WCHAR))
            {
               information() << "Device interface length in bytes (%u) should be a multiple of the size_i32 of a WCHAR!", size;
               return;
            }

            wstring wstr;
            wstr.get_buffer(size);

            mmr = midiOutMessage(
                  h,
                  DRV_QUERYDEVICEINTERFACE,
                  reinterpret_cast<DWORD_PTR>((wchar_t *) wstr.c_str()),
                  size
                  );

            wstr.release_buffer();
            if (MMSYSERR_NOERROR != mmr)
            {
               information() << "midiOutMessage(DRV_QUERYDEVICEINTERFACE) failed: mmr = 0x%08x", mmr;
               return;
            }

            string str(wstr);

            information() << "    Device interface: \"%s\"", str;
         }

         void midi::mmsystem_LogMidiInCaps(UINT_PTR i, MIDIINCAPSW caps)
         {
            informationf(
            "-- %u: %S --\n"
            "    Device ID: %u\n"
            "    Manufacturer identifier: %u\n"
            "    Product identifier: %u\n"
            "    Driver version: %u.%u\n"
            "    Product name: %S\n"
            "    Support: 0x%x"
            ,
            i,
            caps.szPname ? caps.szPname : L"(no name)",
            i,
            caps.wMid,
            caps.wPid,
            caps.vDriverVersion / 256, caps.vDriverVersion % 256,
            caps.szPname ? caps.szPname : L"(no name)",
            caps.dwSupport
            );

            string strName;

            if (caps.szPname != nullptr)
            {

               strName.formatf("%s (%d)", caps.szPname, i);

            }
            else
            {

               strName.formatf("(no name midi In device) (%d)", i);

            }

            //m_straIn.add(strName);

         }


         void midi::mmsystem_LogMidiOutCaps(UINT_PTR i, MIDIOUTCAPSW caps)
         {

            informationf(
            "-- %u: %S --\n"
            "    Device ID: %u\n"
            "    Manufacturer identifier: %u\n"
            "    Product identifier: %u\n"
            "    Driver version: %u.%u\n"
            "    Product name: %S\n"
            "    Technology: %u (%S)\n"
            "    Voices: %u\n"
            "    Notes: %u\n"
            "    Channel mask: 0x%x\n"
            "    Support: 0x%x"
            "%S%S%S%S"
            ,
            i,
            caps.szPname ? caps.szPname : L"(no name)",
            i,
            caps.wMid,
            caps.wPid,
            caps.vDriverVersion / 256, caps.vDriverVersion % 256,
            caps.szPname ? caps.szPname : L"(no name)",
            caps.wTechnology,
            caps.wTechnology == MOD_MIDIPORT ? L"MOD_MIDIPORT" :
            caps.wTechnology == MOD_SYNTH ? L"MOD_SYNTH" :
            caps.wTechnology == MOD_SQSYNTH ? L"MOD_SQSYNTH" :
            caps.wTechnology == MOD_FMSYNTH ? L"MOD_FMSYNTH" :
            caps.wTechnology == MOD_MAPPER ? L"MOD_MAPPER" :
            caps.wTechnology == MOD_WAVETABLE ? L"MOD_WAVETABLE" :
            caps.wTechnology == MOD_SWSYNTH ? L"MOD_SWSYNTH" :
            L"Unrecognized",
            caps.wVoices,
            caps.wNotes,
            caps.wChannelMask,
            caps.dwSupport,
            (caps.dwSupport & MIDICAPS_CACHE) ? L"\n        MIDICAPS_CACHE" : L"",
            (caps.dwSupport & MIDICAPS_LRVOLUME) ? L"\n        MIDICAPS_LRVOLUME" : L"",
            (caps.dwSupport & MIDICAPS_STREAM) ? L"\n        MIDICAPS_STREAM" : L"",
            (caps.dwSupport & MIDICAPS_VOLUME) ? L"\n        MIDICAPS_VOLUME" : L""
            );

            string strName;

            if (caps.szPname != nullptr)
            {

               strName.formatf("%S (%d)", caps.szPname, i);

               m_straMidiOutName.add(caps.szPname);

            }
            else
            {

               strName.formatf("(no name midi Out device) (%d)", i);

               m_straMidiOutName.add(strName);

            }

            //m_straOut.add(strName);

         }


         ::e_status midi::midi_in_translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pmidiobject, i64 iOsResult, const ::string & strContext, const ::string & strText)
         {

            auto estatus = midi_in_get_error_text((MMRESULT) iOsResult, strOsMessage, strMessage);

            return estatus;

         }


         static ::mutex * s_pmutex = nullptr;


         //::mutex & get_midi_mutex()
         //{

         //   if(s_pmutex == nullptr)
         //   {

         //      s_pmutex = new ::mutex();

         //      // TODO :
         //      // register s_pmutex in Sys(::get_thread_app()).register_static_system_object
         //      // for example, for deletion before alloc system is deleted.

         //   }

         //   return *s_pmutex;

         //}



         //::pointer<play_thread>midi::on_midi_sequence_start(::music::midi::sequence* psequence, const string& strDevice)
         //{

         //   string strEngine = device_engine(strDevice);

         //   if (strEngine.case_insensitive_order(m_strName) == 0)
         //   {

         //      //return __allocate< sequencer >(psequence, strDevice);
         //      return nullptr;

         //   }

         //   return ::music::midi::midi::on_midi_sequence_start(psequence, strDevice);

         //}


         ::pointer<::music::midi::message_out>midi::get_message_out(const string& strDeviceId)
         {

            auto & pmessageout = m_mapMessageOut[strDeviceId];

            if (!pmessageout)
            {

               auto pout = __allocate< out >();

               pout->initialize_message_out(this, strDeviceId);

               pout->open();

               pmessageout = pout;

            }

            return pmessageout;

         }


         ::pointer<::music::midi::message_in>midi::get_message_in(const string& strDevice)
         {

            if (strDevice.is_empty())
            {

               return nullptr;

            }

            string strMMSystemDevice = strDevice;

            auto& pmessagein = m_mapMessageIn[strMMSystemDevice];

            if (!pmessagein)
            {

               auto pin = __create_new<in>();

               pin->m_pmidi = this;

               auto iPort = get_midi_in_device_port(strMMSystemDevice);

               pin->open((int) iPort);

               pmessagein = pin;

            }

            return pmessagein;

         }


         ::index midi::get_os_out_device_id(const ::string & strDevice)
         {

            return m_straDeviceOut.find_first(strDevice);

         }


         ::index midi::get_os_in_device_id(const ::string & strDevice)
         {

            return m_straDeviceIn.find_first(strDevice);

         }


         void midi::enumerate_midi_out_devices()
         {

            synchronous_lock synchronouslock(synchronization());

            u32 uDeviceCount = midiOutGetNumDevs();

            MIDIOUTCAPSW midioutcaps;

            string str;

            for (u32 uDev = 0; uDev < uDeviceCount; uDev++)
            {

               if (MMSYSERR_NOERROR == midiOutGetDevCapsW(uDev, &midioutcaps, sizeof(midioutcaps)))
               {

                  string strDeviceName = midioutcaps.szPname;

                  string strDeviceId = m_strName + ":" + strDeviceName;

                  add_midi_out_device(strDeviceName, strDeviceId);

                  m_straDeviceOut.add(strDeviceId);

               }

            }

            ::music::midi::midi::enumerate_midi_out_devices();

         }


         void midi::enumerate_midi_in_devices()
         {

            synchronous_lock synchronouslock(synchronization());

            u32 uDeviceCount = midiInGetNumDevs();

            MIDIINCAPSW midiincaps;

            string str;

            for (u32 uDev = 0; uDev < uDeviceCount; uDev++)
            {

               if (MMSYSERR_NOERROR == midiInGetDevCapsW(uDev, &midiincaps, sizeof(midiincaps)))
               {

                  string strDeviceName = midiincaps.szPname;

                  string strDeviceId = m_strName + ":" + strDeviceName;

                  add_midi_in_device(strDeviceName, strDeviceId);

                  m_straDeviceIn.add(strDeviceId);

               }

            }

            ::music::midi::midi::enumerate_midi_in_devices();

         }


      } // namespace mmsystem


   } // namespace midi


} // namespace music



