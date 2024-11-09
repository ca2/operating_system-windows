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


            file(::particle * pparticle);
            virtual ~file();


            void     WorkStreamRender(LPMIDIHDR lpmh, ::duration tickMax, unsigned int cbPrerollNomimalMax);

            using ::music::midi::file::WorkSeek;

            void     WorkSeek(::duration tickPosition, LPMIDIHDR lpmh);

            void     StreamEvent(::duration tickDelta, ::music::midi::happening * Event, LPMIDIHDR lpmh, ::duration tickMax, unsigned int cbPrerollNomimalMax);

            void     StreamEventF1(::duration tickDelta, array < ::music::midi::happening *, ::music::midi::happening * > & eventptra, LPMIDIHDR lpmh, ::duration tickMax, unsigned int cbPrerollNomimalMax);

            void     InsertParmData(::duration tickDelta, LPMIDIHDR lpmh);

            void     InsertPadEvent(::duration tickDelta, LPMIDIHDR lpmh);


         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music





