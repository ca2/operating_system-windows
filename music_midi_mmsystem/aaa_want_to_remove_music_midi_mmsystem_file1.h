#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM file :
            virtual public ::music::midi::file
         {
         public:


            ::duration m_tkLastOp;


            file(::object * pobject);
            virtual ~file();


            void     WorkStreamRender(LPMIDIHDR lpmh, ::duration tkMax, u32 cbPrerollNomimalMax);

            using ::music::midi::file::WorkSeek;

            void     WorkSeek(::duration tkPosition, LPMIDIHDR lpmh);

            void     StreamEvent(::duration tkDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, ::duration tkMax, u32 cbPrerollNomimalMax);

            void     StreamEventF1(::duration tkDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, ::duration tkMax, u32 cbPrerollNomimalMax);

            void     InsertParmData(::duration tkDelta, LPMIDIHDR lpmh);

            void     InsertPadEvent(::duration tkDelta, LPMIDIHDR lpmh);


         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music





