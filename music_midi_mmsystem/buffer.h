#pragma once




namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM midi_callback_data
         {
         public:


            __pointer(sequence)     m_psequence;


         };

         class buffer_array;


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM buffer :
             virtual public matter
         {
         public:


            MIDIHDR              m_midihdr;
            memory               m_storage;
            bool                 m_bPrepared;
            buffer_array* m_pbuffera;


            buffer();
            virtual ~buffer();

            bool IsPrepared();
            void Reset();
            void Initialize(i32 iSize, buffer_array* pbuffera);

            ::e_status     midiStreamOut(HMIDISTRM hmidiout);
            ::e_status     midiOutPrepareHeader(HMIDIOUT hmidiout);
            ::e_status     midiOutUnprepareHeader(HMIDIOUT hmidiout);


            inline LPMIDIHDR GetMidiHdr()
            {
               return &m_midihdr;
            }

            //void SetNextMidiHdr(LPMIDIHDR lpNext);

            midi_callback_data* get_midi_callback_data();

            static buffer* get(LPMIDIHDR lpmidihdr);

            static sequence* get_sequence(LPMIDIHDR lpmidihdr);

         };


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM buffer_array :
            virtual public ::music::midi::object
         {
         public:


            __pointer(sequencer)     m_psequencer;

            midi_callback_data * m_pcallbackdata;

            HAVE_ARRAY_OF(buffer, m_buffera, buffer);


            buffer_array();
            virtual ~buffer_array();

            void Reset();
            void Initialize(i32 iCount, i32 iSize, midi_callback_data* pcallbackdata);


            ::e_status     midiStreamOut(HMIDISTRM hmidiout);
            ::e_status     midiOutPrepareHeader(HMIDIOUT hmidiout);
            ::e_status     midiOutUnprepareHeader(HMIDIOUT hmidiout);

         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





