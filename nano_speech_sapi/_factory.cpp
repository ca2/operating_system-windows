#include "framework.h"
#include "speech.h"


IMPLEMENT_FACTORY(nano_speech_sapi)
{

   pfactory->add_factory_item < ::sapi::nano::speech::speech, ::nano::speech::speech >();

}



