#include "framework.h"
#include "speaker.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/operating_system/universal_windows/_winrt_foundation.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "aqua/multimedia/_.h"
#include "aqua/audio/audio.h"
#include "aqua/platform/system.h"
#include "acme_universal_windows/_winrt_stream.h"
#include <winrt/Windows.Foundation.Collections.h>


namespace text_to_speech_speech_synthesis
{



   speaker::speaker()
   {

      defer_create_synchronization();

      m_strDefaultLang = "en"_ansi;

   }


   speaker::~speaker()
   {

   }

   //--------------------------------------------------------------------
   // Initializes the text speaker.
   //--------------------------------------------------------------------
   bool speaker::initialize(const ::scoped_string & scopedstrLang)
   {

      auto voices = m_synthesizer.AllVoices();

      for (UINT i = 0; i < voices.Size(); i++)
      {

         auto voice = voices.GetAt(i);

         string strVoiceLanguage = voice.Language().begin();

         if (strVoiceLanguage.case_insensitive_begins(strLang))
         {

            m_synthesizer.Voice(voice);

            break;

         }

      }

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

      return speak(m_strDefaultLang, text);

   }


   bool speaker::is_lang_ok(const ::scoped_string & scopedstrLang)
   {

      bool bTts = false;

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
   void speaker::speak(const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, bool bSync)
   {

      string strLang(strLangParam);

      string strText(strTextParam);

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

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      initialize(strLang);

      auto stream = m_synthesizer.SynthesizeTextToStreamAsync(as_hstring(strText)).get();

      auto inputstream = stream.GetInputStreamAt(0);

      int nCount = 1024 * 1024;

      auto pfile = create_memory_file();

      ::collection::index pos = 0;

      ::collection::index count = 0;

      while (true)
      {

         ::winrt::Windows::Storage::Streams::Buffer buffer(nCount);

         auto buffer2 = inputstream.ReadAsync(buffer, (unsigned int)nCount, ::winrt::Windows::Storage::Streams::InputStreamOptions::None).get();

         auto read = buffer2.Length();

         if (read <= 0)
         {

            break;

         }
         
         count += read;

         pfile->memory().set_size(count);

         auto totalRead = windows_runtime_read_buffer(pfile->memory().data() + pos, nCount, buffer);

         pos += read;

      }

      auto paudio = system()->audio();

      paudio->play_audio(pfile, bSync);

      //return true;

   }


   //--------------------------------------------------------------------
   // Speaks some text.
   // (The input text must not be empty.)
   //--------------------------------------------------------------------
   void speaker::speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, bool bSync)
   {

      string strLang(strLangParam);

      string strText(strTextParam);

      //
      // Input text must not be empty
      //
      if (strText.is_empty())
      {

         // nothing to speak?!?!
         // return false;

         throw ::exception(error_invalid_empty_argument);

      }

      //if (!is_lang_ok(strLang))
      //{

      //   return ::tts::speaker::speak(strLang, strText, bSync);

      //}

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      speak(strLang, strTextParam, bSync);

   }


   bool speaker::is_speaking(const ::scoped_string & scopedstrLang)
   {

     return ::text_to_speech::speaker::is_speaking(strLang);
   }


   void speaker::stop(const ::scoped_string & scopedstrLang)
   {

      if (!is_lang_ok(strLang))
      {

         return ::text_to_speech::speaker::stop(strLang);

      }


   }


} // namespace text_to_speech_speech_synthesis



