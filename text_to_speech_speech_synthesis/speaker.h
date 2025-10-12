#pragma once


#include "aqua/audio/speaker.h"
#include <winrt/Windows.Media.SpeechSynthesis.h>


namespace text_to_speech_speech_synthesis
{


   class CLASS_DECL_TEXT_TO_SPEECH_SPEECH_SYNTHESIS speaker :
      virtual public ::text_to_speech::speaker
   {
   public:


      string                                                                  m_strDefaultLang;
      ::winrt::Windows::Media::SpeechSynthesis::SpeechSynthesizer             m_synthesizer;
      
      
      speaker();
      ~speaker() override;


      virtual bool initialize(const ::scoped_string & scopedstrLang);
      virtual bool initialize_translator(const ::scoped_string & scopedstrLang);
      virtual bool destroy(const ::scoped_string & scopedstrLang);
      virtual bool finalize_translator(const ::scoped_string & scopedstrLang);

      virtual bool is_lang_ok(const ::scoped_string & scopedstrLang);

      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      virtual void speak(const ::scoped_string & scopedstrText) override;

      virtual void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSync = false) override;

      virtual void speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSync = false) override;

      virtual bool is_speaking(const ::scoped_string & scopedstrLang) override;

      virtual void stop(const ::scoped_string & scopedstrLang) override;


   };


} // namespace text_to_speech_speech_synthesis



