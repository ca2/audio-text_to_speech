// From audio (ms_translator_speaker) by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/api_client.h"
#include "aqua/audio/speaker.h"


namespace text_to_speech_azure
{


   class CLASS_DECL_TEXT_TO_SPEECH_AZURE speaker :
      virtual public ::text_to_speech::speaker,
      virtual public ::api_client
   {
   public:


      ::collection::index       m_iTranslatorFile;
      //string      m_strTranslatorToken;


      speaker();
      ~speaker() override;


      //virtual void defer_api();


      void speak(const ::scoped_string & scopedstrText) override;

      void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity= e_synchronicity_asynchronous) override;

      void speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity= e_synchronicity_asynchronous) override;

      void stop(const ::scoped_string & scopedstrLang) override;

      bool is_speaking(const ::scoped_string & scopedstrLang) override;


   };


} // namespace text_to_speech_azure



