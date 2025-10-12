#pragma once


#include "acme/prototype/collection/string_map.h"
#include "aqua/audio/speaker.h"




namespace text_to_speech_streamelements
{


   //------------------------------------------------------------------------
   // Simple class to speak some text (using StreamElements).
   //------------------------------------------------------------------------
   class CLASS_DECL_TEXT_TO_SPEECH_STREAMELEMENTS speaker :
      virtual public ::text_to_speech::speaker
   {
   public:


      string                                       m_strDefaultLang;
      string_map_base < unsigned int >                         m_time;
      string_map_base < bool >                          m_tts;
      
      
      speaker();
      ~speaker() override;


      void on_initialize_particle() override;

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

      virtual void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous) override;

      virtual void speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity = e_synchronicity_asynchronous) override;

      virtual bool is_speaking(const ::scoped_string & scopedstrLang) override;

      virtual void stop(const ::scoped_string & scopedstrLang) override;


   };


} // namespace text_to_speech



