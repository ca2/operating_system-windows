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


            string_array_base         m_straDeviceOut;
            string_array_base         m_straDeviceIn;

            ::particle_pointer      m_pparticleMidiMutex;


            midi();
            ~midi() override;


            void initialize(::particle* pparticle) override;


            ::particle* get_midi_mutex() { return m_pparticleMidiMutex; }





            ::collection::index get_os_out_device_id(const ::scoped_string & scopedstrDevice);

            ::collection::index get_os_in_device_id(const ::scoped_string & scopedstrDevice);


            virtual ::pointer<::music::midi::sequencer>create_midi_sequencer(sequence * psequence, const ::scoped_string & scopedstrDevice) override;
            //virtual ::pointer<::music::midi::sequence_thread>create_midi_sequence_thread(::music::midi::sequence* psequence, const ::scoped_string & scopedstrDevice) override;

            //virtual ::pointer<play_thread>on_midi_sequence_start(::music::midi::sequence* psequence, const ::scoped_string & scopedstrDevice) override;


            void mmsystem_LogMidiInCaps(UINT_PTR i, MIDIINCAPSW caps);
            void mmsystem_GetMidiInDeviceInterface(UINT_PTR i);
            void mmsystem_LogMidiOutCaps(UINT_PTR i, MIDIOUTCAPSW caps);
            void mmsystem_GetMidiOutDeviceInterface(UINT_PTR i);

            using ::music::midi::midi::translate_os_result;
            virtual ::e_status midi_in_translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pmidiobject, long long iOsResult, const ::scoped_string & scopedstrContext, const ::scoped_string & scopedstrText);


            virtual void enumerate_midi_out_devices() override;
            virtual void enumerate_midi_in_devices() override;


            virtual ::pointer<::music::midi::message_out>get_message_out(const ::scoped_string & scopedstrDevice) override;

            virtual ::pointer<::music::midi::message_in>get_message_in(const ::scoped_string & scopedstrDevice) override;

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




