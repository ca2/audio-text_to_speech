#pragma once


#include "app-interface/api_google/api.h"
#include "aqua/audio/speaker.h"


namespace text_to_speech_google
{


   class CLASS_DECL_TEXT_TO_SPEECH_GOOGLE speaker :
      virtual public ::text_to_speech::speaker,
      virtual public ::api_client
   {
   public:


      ::collection::index       m_iTranslatorFile;
      string      m_strTranslatorToken;


      speaker();
      ~speaker() override;


      //virtual void defer_api();


      void speak(const ::scoped_string & scopedstrText) override;

      void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous) override;

      void speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous) override;

      void stop(const ::scoped_string & scopedstrLang) override;

      bool is_speaking(const ::scoped_string & scopedstrLang) override;

      virtual string get_voice(::string& strLang, const ::scoped_string & scopedstrGender);


   };


} // namespace namespace text_to_speech_google



