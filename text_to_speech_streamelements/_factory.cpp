#include "framework.h"
#include "speaker.h"


__FACTORY_EXPORT void text_to_speech_streamelements_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::text_to_speech_streamelements::speaker, ::text_to_speech::speaker >();

}



