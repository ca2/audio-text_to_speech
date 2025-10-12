#include "framework.h"
#include "speaker.h"


__FACTORY_EXPORT void text_to_speech_google_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::text_to_speech_google::speaker, ::text_to_speech::speaker >();

}



