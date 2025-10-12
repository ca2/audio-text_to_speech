#include "framework.h"
#include "speaker.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/nano/nano.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/international.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aqua/audio/audio.h"
#include "aqua/platform/system.h"
#include "acme/operating_system/windows_common/com/cotaskptr.h"


#pragma comment(lib, "Shlwapi")

//inline bool SpGetDefaultTokenFromCategoryIdAndLang(
//   ::platform::application * papp,
//   const WCHAR * pszCategoryId,
//   ISpObjectToken ** ppToken,
//   const_char_pointer pszLang,
//   const_char_pointer pszAttributes,
//   BOOL fCreateCategoryIfNotExist = true);
//

//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////

HRESULT out_file(::memory_file * f, WAVEFORMATEX & fmt, IStream * pStream)
{

   // Write the file headers
   f->write("RIFF----WAVEfmt "_ansi, 16);     // (chunk int_size to be filled in later)
   unsigned int dw = fmt.cbSize;
   f->write(&dw, sizeof(dw));
   f->write(&fmt, fmt.cbSize);
   // Write the data chunk header
   size_t data_chunk_pos = (size_t)f->get_position();
   f->write("data----"_ansi, 8);  // (chunk int_size to be filled in later)




   // SAPI wrote to the stream and filled it up
   // but the position is still at the end
   // so we need to rewind back to the beginning
   // before we can read it
   ULARGE_INTEGER end;
   LARGE_INTEGER zero = {};
   HRESULT hr = pStream->Seek(zero, STREAM_SEEK_END, &end);
   if (FAILED(hr))
   {
      return hr;
   }
   hr = pStream->Seek(zero, STREAM_SEEK_SET, nullptr);
   if (FAILED(hr))
   {
      return hr;
   }
   auto iPos = f->size();
   f->set_size(f->size() + end.QuadPart);
   ULONG read = 0;
   hr = pStream->Read(f->data_begin()+iPos, (ULONG)f->size(), &read);

   size_t file_length = (size_t)f->size();

   // Fix the data chunk header to contain the data int_size
   f->set_position(data_chunk_pos + 4);
   dw = (unsigned int)(file_length - data_chunk_pos + 8);
   f->write(&dw, sizeof(unsigned int));


   // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
   f->set_position(0 + 4);
   dw = (unsigned int)(file_length - 8);
   f->write(&dw, sizeof(unsigned int));
   return S_OK;
}



namespace text_to_speech_sapi
{



   speaker::speaker()
   {

      defer_create_synchronization();

      m_strDefaultLang = "en"_ansi;

   }


   speaker::~speaker()
   {

   }

   ::sapi::nano::speech::speech* speaker::get_sapi_speech()
   {

      if (m_psapispeech)
      {

         return m_psapispeech;

      }

      m_psapispeech = nano()->speech();

      if (m_psapispeech)
      {

         return m_psapispeech;

      }

      auto pfactory = system()->factory("nano_speech"_ansi, "sapi"_ansi);

      øconstruct(m_psapispeech, pfactory);

      return m_psapispeech;

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

      auto psapispeech = get_sapi_speech();

      if(!psapispeech)
      {

         throw ::exception(error_not_found);

      }
   
      auto pvoice = psapispeech->SpGetVoiceByLangAndGender(strLang, e_gender_male);

      comptr < ISpStream > pSpStream;

      HRESULT hr = pSpStream.CoCreateInstance(CLSID_SpStream);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      comptr < IStream > pStream;

      pStream = SHCreateMemStream(nullptr, 0);

      if (pStream.is_null())
      {

         throw ::exception(error_failed);

      }

      WAVEFORMATEX fmt;

      fmt.cbSize = sizeof(WAVEFORMATEX);
      fmt.wBitsPerSample = 16;
      fmt.nChannels = 2;
      fmt.nBlockAlign = fmt.nChannels * fmt.wBitsPerSample / 8;
      fmt.wFormatTag = WAVE_FORMAT_PCM;
      fmt.nSamplesPerSec = 44100;
      fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nChannels * fmt.wBitsPerSample / 8;

      hr = pSpStream->SetBaseStream(
         pStream,
         SPDFID_WaveFormatEx,
         &fmt
      );

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      hr = pvoice->SetOutput(pSpStream, true);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      string strT(strText);

      unsigned int uFlag = 0;

      strT.trim();

      //if (strT.case_insensitive_begins_eat("xml:"_ansi))
      {

         uFlag |= SPF_IS_XML;

      }
      //else
      //{

      // uiFlag |= SPF_IS_NOT_XML;

      //}

      wstring wstr(strT);


      //
      // Speak input text
      //
      ULONG streamNumber;

      //pvoice->WaitUntilDone(5 * 60 * 60 * 1000);

      hr = pvoice->Speak(
         wstr,
         //SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
         uFlag,
         &streamNumber);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      auto pfile = create_memory_file();

      hr = out_file(pfile, fmt, pStream);

      if (FAILED(hr))
      {

         //return false;

         throw ::exception(error_failed);

      }

      auto paudio = system()->audio();

      paudio->play_audio(pfile, esynchronicity);

      //return true;

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

      //if (!is_lang_ok(strLang))
      //{

      //   return ::tts::speaker::speak(strLang, strText, bSync);

      //}

      //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //node()->defer_co_initialize_ex(false);

      //comptr < ISpVoice > & pvoice = m_voice[strLang];

      //HRESULT hr = S_OK;

      //if (pvoice.is_null())
      //{

      //   pvoice.CoCreateInstance(CLSID_SpVoice);

      //}

      //comptr < ISpObjectToken > & ptoken = m_token[strLang];

      //if (ptoken.is_null())
      //{

      //   if (strLang.is_empty())
      //   {

      //      hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &ptoken, false);

      //      if (FAILED(hr))
      //      {

      //         throw ::exception(error_failed);

      //      }

      //   }
      //   else
      //   {

      //      hr = SpGetDefaultTokenFromCategoryIdAndLang(get_app(), L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices"_ansi, &ptoken, strLang, strAttributes, false);

      //      if (FAILED(hr))
      //      {

      //         throw ::exception(error_failed);

      //      }

      //   }

      //   hr = pvoice->SetVoice(ptoken);

      //   if (FAILED(hr))
      //   {

      //      throw ::exception(error_failed);

      //   }

      //}

      auto psapispeech = get_sapi_speech();

      if (!psapispeech)
      {

         throw ::exception(error_not_found);

      }

      auto pvoice = psapispeech->SpGetVoiceByLangAndGender(strLang, e_gender_male);

      comptr < ISpStream > pSpStream;

      HRESULT hr = pSpStream.CoCreateInstance(CLSID_SpStream);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      comptr < IStream > pStream;

      pStream = SHCreateMemStream(nullptr, 0);

      if (pStream.is_null())
      {

         throw ::exception(error_failed);

      }

      WAVEFORMATEX fmt;

      fmt.cbSize = sizeof(WAVEFORMATEX);
      fmt.wBitsPerSample = 16;
      fmt.nChannels = 2;
      fmt.nBlockAlign = fmt.nChannels * fmt.wBitsPerSample / 8;
      fmt.wFormatTag = WAVE_FORMAT_PCM;
      fmt.nSamplesPerSec = 44100;
      fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nChannels * fmt.wBitsPerSample / 8;

      hr = pSpStream->SetBaseStream(
         pStream,
         SPDFID_WaveFormatEx,
         &fmt
      );

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      hr = pvoice->SetOutput(pSpStream, true);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      string strT(strText);

      unsigned int uFlag = 0;

      strT.trim();

      //if (strT.case_insensitive_begins_eat("xml:"_ansi))
      {

         uFlag |= SPF_IS_XML;

      }
      //else
      //{

      // uiFlag |= SPF_IS_NOT_XML;

      //}

      wstring wstr(strT);


      //
      // Speak input text
      //
      ULONG streamNumber;

      //pvoice->WaitUntilDone(5 * 60 * 60 * 1000);

      hr = pvoice->Speak(
         wstr,
         //SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
         uFlag,
         &streamNumber);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      auto pfile = create_memory_file();

      hr = out_file(pfile, fmt, pStream);

      if (FAILED(hr))
      {

         throw ::exception(error_failed);

      }

      auto paudio = system()->audio();

      paudio->play_audio(pfile, esynchronicity);

      //return true;

   }


   bool speaker::is_speaking(const ::scoped_string & scopedstrLang)
   {

      if (!is_lang_ok(scopedstrLang))
      {

         return ::text_to_speech::speaker::is_speaking(scopedstrLang);

      }

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto psapispeech = get_sapi_speech();

      if (!psapispeech)
      {

         throw ::exception(error_not_found);

      }

      auto pvoice = psapispeech->SpGetVoiceByLangAndGender(scopedstrLang, e_gender_male);

      if (pvoice.is_null())
      {

         return false;

      }

      SPVOICESTATUS status = {};

      HRESULT hr = pvoice->GetStatus(&status, nullptr);

      if (FAILED(hr))
      {

         return false;

      }

      return (status.dwRunningState & SPRS_IS_SPEAKING) != false;

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


} // namespace text_to_speech_sapi



