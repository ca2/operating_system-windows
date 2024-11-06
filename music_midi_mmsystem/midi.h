#pragma once


#include "app-veriwell/multimedia/music/midi/midi.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM midi :
            virtual public ::music::midi::midi
         {
         public:


            string_array         m_straDeviceOut;
            string_array         m_straDeviceIn;

            ::particle_pointer      m_pparticleMidiMutex;


            midi();
            ~midi() override;


            void initialize(::particle* pparticle) override;


            ::particle* get_midi_mutex() { return m_pparticleMidiMutex; }





            ::collection::index get_os_out_device_id(const ::string & strDevice);

            ::collection::index get_os_in_device_id(const ::string & strDevice);


            virtual ::pointer<::music::midi::sequencer>create_midi_sequencer(sequence * psequence, const string& strDevice) override;
            //virtual ::pointer<::music::midi::sequence_thread>create_midi_sequence_thread(::music::midi::sequence* psequence, const string& strDevice) override;

            //virtual ::pointer<play_thread>on_midi_sequence_start(::music::midi::sequence* psequence, const string& strDevice) override;


            void mmsystem_LogMidiInCaps(UINT_PTR i, MIDIINCAPSW caps);
            void mmsystem_GetMidiInDeviceInterface(UINT_PTR i);
            void mmsystem_LogMidiOutCaps(UINT_PTR i, MIDIOUTCAPSW caps);
            void mmsystem_GetMidiOutDeviceInterface(UINT_PTR i);

            using ::music::midi::midi::translate_os_result;
            virtual ::e_status midi_in_translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pmidiobject, huge_integer iOsResult, const ::string & strContext, const ::string & strText);


            virtual void enumerate_midi_out_devices() override;
            virtual void enumerate_midi_in_devices() override;


            virtual ::pointer<::music::midi::message_out>get_message_out(const string& strDevice) override;

            virtual ::pointer<::music::midi::message_in>get_message_in(const string& strDevice) override;

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




