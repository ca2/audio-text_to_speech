#include "framework.h"
#include "form_handler.h"
#include "acme/constant/id.h"
#include "aura/platform/system.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/still.h"
#include "axis/user/user/line_layout.h"
#include "berg/user/form/document.h"
#include "audio/audio/audio.h"


namespace user_text_to_speech
{


   form_handler::form_handler()
   {


   }


   form_handler::~form_handler()
   {

   }


   //void handler::handle(::userex::pane_tab_impact * ppanetabimpact, ::topic * ptopic, ::handler_context * phandlercontext)
   //{


   //   if (ptopic->user_interaction() && 
   //      ptopic->user_interaction()->is_ascendant(ppanetabimpact->m_pformdocumentMenu, true))
   //   {

   //      if (ptopic->id() == ::id_load_form_data)
   //      {

   //         ::pointer < ::user::impact > pimpact = ppanetabimpact->m_pformdocumentMenu->get_impact(0);

   //         system()->defer_audio();

   //         auto paudio = system()->audio();

   //         if (paudio)
   //         {

   //            string str;

   //            string_array_base straTts;

   //            straTts.add("azure"_ansi);
   //            straTts.add("google"_ansi);
   //            straTts.add("sapi"_ansi);
   //            straTts.add("speech_synthesis"_ansi);

   //            for (auto & strTtsImplementation : straTts)
   //            {

   //               string strId;

   //               strId = "text_to_speech_"_ansi + strTtsImplementation + ".checkbox"_ansi;

   //               ::pointer<::user::check_box>pcheck = pimpact->get_child_by_id(strId);

   //               if (pcheck)
   //               {

   //                  pcheck->add_handler(this);

   //                  ::user::interaction * puserinteraction = pimpact;

   //                  m_mapcheckboxTextToSpeech[puserinteraction][strTtsImplementation] = pcheck;

   //                  pcheck->set_check(paudio->text_to_speech_implementation() == strTtsImplementation ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

   //                  pcheck->add_handler(ppanetabimpact);

   //               }

   //            }

   //         }

   //         ptopic->m_bOk = true;

   //         ptopic->m_bRet = true;

   //         return;

   //      }
   //      else if (ptopic->id() == ::id_set_check && ptopic->user_interaction() != nullptr)
   //      {

   //         string strTtsImplementation = ptopic->user_interaction_id();

   //         if (strTtsImplementation.case_insensitive_begins_eat("text_to_speech_"_ansi) && strTtsImplementation.case_insensitive_ends_eat(".checkbox"_ansi))
   //         {

   //            if (ptopic->user_interaction() && ptopic->m_actioncontext.is_user_source())
   //            {

   //               ::pointer<::user::interaction>pcheck = ptopic->user_interaction();

   //               if (pcheck.is_set())
   //               {

   //                  ::user::impact * pimpact = ppanetabimpact->m_pformdocumentMenu->get_impact(0);

   //                  auto paudio = system()->audio()->m_paudio;

   //                  paudio->text_to_speech_implementation(strTtsImplementation);

   //                  ::user::interaction * puserinteraction = pimpact;

   //                  for (auto & pcheckOther : m_mapcheckboxTextToSpeech[puserinteraction].payloads())
   //                  {

   //                     if (pcheckOther != pcheck)
   //                     {

   //                        pcheckOther->set_check(false, ::e_source_sync);

   //                        pcheckOther->enable_window(true);

   //                     }

   //                  }

   //                  pcheck->enable_window(false);

   //               }

   //               ptopic->m_bRet = true;

   //               return;

   //            }

   //         }

   //      }

   //   }

   //}


   void form_handler::design_form(::user::interaction * puserinteraction)
   {

      system()->defer_audio();

      auto paudio = system()->audio();

      if (paudio)
      {

         auto playoutLineTop = create_line_layout(puserinteraction, e_orientation_vertical);

         string str;

         string_array_base straTts;

         straTts.add("azure"_ansi);
         straTts.add("google"_ansi);
#ifdef WINDOWS
         straTts.add("sapi"_ansi);
#endif
#ifdef UNIVERSAL_WINDOWS
         straTts.add("speech_synthesis"_ansi);
#endif
         straTts.add("streamelements"_ansi);

         for (auto & strTtsImplementation : straTts)
         {

            auto playoutLine = create_line_layout(playoutLineTop, e_orientation_horizontal);

            string strId;

            strId = "text_to_speech_"_ansi + strTtsImplementation + ".checkbox"_ansi;

            auto pcheckbox = create_check_box<::user::check_box>(playoutLine, strId);

            create_label<::user::still>(playoutLine, strTtsImplementation);

            m_mapcheckboxTextToSpeech[puserinteraction][strTtsImplementation] = pcheckbox;

            pcheckbox->set_check(paudio->text_to_speech_implementation() == strTtsImplementation ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

            pcheckbox->enable_window(paudio->text_to_speech_implementation() != strTtsImplementation);

            //                  pcheck->add_handler(ppanetabimpact);

            pcheckbox->check_changed(this) += [this, pcheckbox, strTtsImplementation, puserinteraction](auto & check)
               {

                  auto bCheck = check.payload().as_bool();

                  if (bCheck)
                  {

                     auto paudio = system()->audio()->m_paudio;

                     paudio->text_to_speech_implementation(strTtsImplementation);

                     for (auto & pcheckboxOther : m_mapcheckboxTextToSpeech[puserinteraction].payloads())
                     {

                        if (pcheckboxOther->check_property() != check)
                        {

                           pcheckboxOther->set_check(false, ::e_source_sync);

                           pcheckboxOther->enable_window(true);

                        }

                     }

                     //::pointer < ::user::check_box > pcheckbox = pcheck;

                     pcheckbox->enable_window(false);

                  }

                  //                  pcheck->add_handler(this);

                  //                  ::user::interaction * puserinteraction = pimpact;

                  //                  m_mapcheckboxTextToSpeech[puserinteraction][strTtsImplementation] = pcheck;

                  //                  pcheck->set_check(paudio->text_to_speech_implementation() == strTtsImplementation ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

                  //                  pcheck->add_handler(ppanetabimpact);

                  //               }

                  //            }

                  //         }

               };

         }

      }

      //bool bCheck = false;

      //auto papplication = application();

      //bool bUserAutoStart = node()->is_user_auto_start(papplication->get_executable_appid());

      //pcheckbox->set_check(bUserAutoStart, ::e_source_initialize);

      //pcheckbox->m_callbackOnCheck = [this](auto pcheck)
      //   {

      //      bool bCheck = pcheck->bcheck();

      //      auto papplication = application();

      //      node()->register_user_auto_start(
      //         papplication->get_executable_appid(),
      //         papplication->get_executable_path(),
      //         "--auto_start=1"_ansi,
      //         bCheck);

      //   };

      //create_label<::user::still>(playoutLine, "Enable Auto Start"_ansi);

   }


} // namespace user_text_to_speech



