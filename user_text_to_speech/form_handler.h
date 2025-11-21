#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/collection/string_map.h"
#include "axis/user/user/form_handler.h"


namespace user_text_to_speech
{


   class CLASS_DECL_APP_CORE_USER_TEXT_TO_SPEECH form_handler :
      virtual public ::axis::form_handler
   {
   public:


      map_base < ::user::interaction *, string_map_base < ::pointer<::user::check_box >>>  m_mapcheckboxTextToSpeech;


      
      form_handler();
      ~form_handler() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //void handle(::userex::pane_tab_impact * ppanetabimpact, ::topic * ptopic, ::handler_context * phandlercontext) override;

      void design_form(::user::interaction * puserinteraction) override;

   };


} // namespace userex

