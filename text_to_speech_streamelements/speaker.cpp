#include "framework.h"
#include "speaker.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/nano/nano.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/international.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/application.h"
#include "aqua/audio/audio.h"
#include "aqua/platform/system.h"





namespace text_to_speech_streamelements
{



   speaker::speaker()
   {

      m_strDefaultLang = "en"_ansi;

   }


   speaker::~speaker()
   {

   }


   void speaker::on_initialize_particle()
   {

      ::text_to_speech::speaker::on_initialize_particle();

      defer_create_synchronization();



   }

   //--------------------------------------------------------------------
   // Initializes the text speaker.
   //--------------------------------------------------------------------
   bool speaker::initialize(const ::scoped_string & scopedstrLang)
   {

      //destroy(strLang);

      //bool bOk = false;

      //fork([&]()
      //{

      //   defer_co_initialize_ex(true);


      ////
      //// Create text to speech engine
      ////
      //HRESULT hr = m_voice[strLang].CoCreateInstance(CLSID_SpVoice);
      //if (FAILED(hr))
      //{

      //   return;

      //}

      //if (strLang.is_empty())
      //{

      //   //
      //   // Get token corresponding to default voice
      //   //
      //   hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &m_token[strLang], false);

      //   if (FAILED(hr))
      //   {

      //      return;

      //   }

      //}
      //else
      //{

      //   //
      //   // Get token corresponding to default voice
      //   //
      //   hr = SpGetDefaultTokenFromCategoryIdAndLang(get_app(), L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices"_ansi, &m_token[strLang], strLang, false);

      //   if (FAILED(hr))
      //   {

      //      return;

      //   }

      //}


      //
      // Set default voice
      //
      //   hr = m_voice[strLang]->SetVoice(m_token[strLang]);

      //   if (FAILED(hr))
      //   {

      //      return;

      //   }

      //   bOk = true;

      //})->wait();

      //return bOk;
      return true;

   }


   bool speaker::initialize_translator(const ::scoped_string & scopedstrLang)
   {

      return false;

   }


   bool speaker::destroy(const ::scoped_string & scopedstrLang)
   {

      //fork([&]()
      //{

      //   defer_co_initialize_ex(true);


      //   if (m_voice[strLang].is_set())
      //   {

      //      m_voice[strLang]->Pause();

      //   }

      //   m_token[strLang].Release();

      //   m_voice[strLang].Release();

      //})->wait();


      return true;

   }


   bool speaker::finalize_translator(const ::scoped_string & scopedstrLang)
   {

      return false;

   }


   //--------------------------------------------------------------------
   // Speaks some text.
   // (The input text must not be empty.)
   //--------------------------------------------------------------------
   void speaker::speak(const ::scoped_string & scopedstrText)
   {

      return speak(m_strDefaultLang, scopedstrText);

   }


   bool speaker::is_lang_ok(const ::scoped_string & scopedstrLang)
   {

      //bool bTts = false;

      //if((!m_tts.find(strLang, bTts) || bTts) && m_voice[strLang].is_set() || (!is_speaking(strLang) && m_time.elapsed()[strLang] > 30 * 1000))
      //if (!m_tts.find(strLang, bTts))
      //{

      //   if (initialize(strLang))
      //   {

      //      bTts = true;

      //   }
      //   else
      //   {

      //      bTts = false;

      //   }

      //   m_tts[strLang] = bTts;

      //}

      return true;

   }


   //--------------------------------------------------------------------
   // Speaks some text.
   // (The input text must not be empty.)
   //--------------------------------------------------------------------
   void speaker::speak(const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, enum_synchronicity esynchronicity)
   {

      string strLang(scopedstrLangParam);

      string strText(scopedstrTextParam);

      //
      // Input text must not be empty
      //
      if (strText.is_empty())
      {

         // nothing to speak?!?!
         //return false;

         throw ::exception(error_invalid_empty_argument);

      }

      //if (!is_lang_ok(strLang))
      //{

      //   return ::tts::speaker::speak(strLang, strText, bSync);

      //}


      auto pfile = create_memory_file();

      ::property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      ::string strEncode;

      strEncode = ::url::encode(scopedstrTextParam);

      ::string strVoice;

      if (strLang.case_insensitive_equals("dk"_ansi)
         || strLang.case_insensitive_equals("da"_ansi))
      {

         strVoice = "Mads"_ansi;

      }
      else if (strLang.case_insensitive_equals("jp"_ansi)
         || strLang.case_insensitive_equals("ja"_ansi))
      {

         strVoice = "Takumi"_ansi;

      }
      else if (strLang.case_insensitive_equals("pt-br"_ansi)
         || strLang.case_insensitive_equals("br"_ansi))
      {

         strVoice = "Ricardo"_ansi;

      }
      else
      {

         strVoice = "Joey"_ansi;

      }

      http()->download(pfile, "https://api.streamelements.com/kappa/v2/speech?voice="_ansi + strVoice + "&text="_ansi + strEncode, set);

      auto paudio = system()->audio();

      paudio->play_audio(pfile, esynchronicity);
   
   }


   //--------------------------------------------------------------------
   // Speaks some text.
   // (The input text must not be empty.)
   //--------------------------------------------------------------------
   void speaker::speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, enum_synchronicity esynchronicity)
   {

      string strLang(scopedstrLangParam);

      string strText(scopedstrTextParam);

      //
      // Input text must not be empty
      //
      if (strText.is_empty())
      {

         // nothing to speak?!?!
         // return false;

         throw ::exception(error_invalid_empty_argument);

      }


      auto pfile = create_memory_file();

      ::property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      ::string strEncode;

      strEncode = ::url::encode(scopedstrTextParam);

      http()->download(pfile, "https://api.streamelements.com/kappa/v2/speech?voice=Joey&text="_ansi + strEncode, set);

      auto paudio = system()->audio();

      paudio->play_audio(pfile, esynchronicity);

   }


   bool speaker::is_speaking(const ::scoped_string & scopedstrLang)
   {

      return false;

   }


   void speaker::stop(const ::scoped_string & scopedstrLang)
   {

      if (!is_lang_ok(scopedstrLang))
      {

         return ::text_to_speech::speaker::stop(scopedstrLang);

      }

      //if (m_tts[strLang])
      //{

      //   destroy(strLang);

      //}
      //else
      //{

      //   finalize_translator(strLang);

      //}

      //return true;

   }


} // namespace text_to_speech_streamelements



