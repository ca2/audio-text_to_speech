#include "framework.h"
#include "form_handler.h"


__FACTORY_EXPORT void user_text_to_speech_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::user_text_to_speech::form_handler, ::user::form_handler >();

}



