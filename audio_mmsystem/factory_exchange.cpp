#include "framework.h"


extern "C"
void audio_mmsystem_factory_exchange(::object * pobject)
{

   create_factory < ::audio_mmsystem::in, ::wave::in >();

   create_factory < ::audio_mmsystem::out, ::wave::out >();

}









