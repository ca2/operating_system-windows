#include "framework.h"


extern "C"
void audio_mmsystem_factory_exchange(::context_object * pcontextobject)
{

   create_factory < ::audio_mmsystem::in, ::wave::in >();

   create_factory < ::audio_mmsystem::out, ::wave::out >();

}









