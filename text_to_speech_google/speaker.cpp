#include "framework.h"
#include "speaker.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/string/base64.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/crypto/crypto.h"
#include "aqua/audio/audio.h"
#include "aqua/platform/system.h"


CLASS_DECL_ACME string file_friendly_transform(const ::scoped_string & scopedstr, bool bTransformSlashes = true);


namespace text_to_speech_google
{


   speaker::speaker()
   {

      m_iTranslatorFile = 1;
      m_strImplementation = "google"_ansi;
      //m_strBrowserAccount = "speaker"_ansi;
      //m_strApiClientConfig = "camilothomas"_ansi;

   }


   speaker::~speaker()
   {

   }




   void speaker::speak(const ::scoped_string & scopedstrText)
   {

      //bool bOk = 
      
      speak("en"_ansi, scopedstrText);

      //return bOk;

   }


   void speaker::speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity)
   {

      //auto estatus = 
      
      speak(""_ansi, scopedstrLang, scopedstrText, esynchronicity);

      //return estatus;

   }


   void speaker::speak(const ::scoped_string & scopedstrAttrParam, const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, enum_synchronicity esynchronicity)
   {

      //::e_status estatus = ::error_failed;

      string strAttr(scopedstrAttrParam);

      string strLang(scopedstrLangParam);

      string strText(scopedstrTextParam);

      ::payload payloadResponse;

      // ::xml::document d;

      // d.load("<root>"_ansi + strText + "</root>"_ansi);

      // strText = d.get_text();

      strText.trim();

      //throw ::exception(todo("html"_ansi));

      //strText = puser->html()->resolve_entities(strText);

      //bool bRetry = false;

      if (strLang == "cn"_ansi)
      {

         strLang = "zh-cn"_ansi;

      }
      else if (strLang == "se"_ansi)
      {

         strLang = "sv"_ansi;

      }
      else if (strLang == "en-uk"_ansi)
      {

         strLang = "en"_ansi;

      }
      else if (strLang == "uk-ua"_ansi)
      {

         strLang = "uk"_ansi;

      }
      //else if (strLang == "tr"_ansi)
      //{

      //   // TRICKY : Phantom exists: BOO... it is mee-eee!
      //   strLang = "en"_ansi;

      //}
      else if (strLang.is_empty())
      {

         strLang = "en"_ansi;

      }

      int i1, i2;

      i1 = (int)(mathematics()->random(1, 2));

      i2 = (int)(mathematics()->random(1, 2));

      string strGender = i1 == 1 ? "male"_ansi : "female"_ansi;

      string strQuality = i2 == 1 ? "MaxQuality"_ansi : "MinSize"_ansi;

      string strFileRel = file_friendly_transform(strText);

      string strMd5 = system()->crypto()->md5(strText);

      if (strFileRel.length() > 30)
      {

         strFileRel = strFileRel.substr(24) + "_-_-_-"_ansi;

      }
      else
      {

         while (strFileRel.length() < 30)
         {

            strFileRel += "_"_ansi;

         }

      }

      strFileRel += strMd5;

      ::file::path pathMp3;

      ::file::path pathTxt;

      auto pdirectorysystem = directory_system();

      ::file::path pathFolder = pdirectorysystem->userconfig() / "speech"_ansi;

      pathMp3 = pathFolder / "google"_ansi / strLang / strQuality / strGender / strFileRel + ".mp3"_ansi;

      pathTxt = pathFolder / "google"_ansi / strLang / strQuality / strGender / strFileRel + ".txt"_ansi;

      //::e_status estatus = ::success;

      auto pfile = create_memory_file();

      // todo... fastly check if file is mp3 file...
      if (file()->safe_get_string(pathTxt) != strText || file()->length(pathMp3) < 100)
      {




         if (case_insensitive_string_begins(strText, "ca2 "_ansi) || case_insensitive_string_begins(strText, "ca2\n"_ansi))
         {
            strText = "c a 2"_ansi + strText.substr(3);
         }
         if (case_insensitive_string_ends(strText, " ca2"_ansi) || case_insensitive_string_ends(strText, "\nca2"_ansi))
         {
            strText = strText.left(strText.length() - 3) + "c a 2"_ansi;
         }
         //strText.utf8_replace(" ca2 "_ansi, " c a 2 "_ansi);
         //strText.utf8_replace(" ca2\n"_ansi, " c a 2\n"_ansi);
         //strText.utf8_replace("\nca2 "_ansi, "\nc a 2 "_ansi);
         //strText.utf8_replace("\nca2\n"_ansi, "\nc a 2\n"_ansi);


         //auto psystem = system();

         //auto purl = psystem->url();

         string strVoiceName;

         if (strGender == "female"_ansi)
         {

            strGender = "Female"_ansi;

         }
         else
         {

            strGender = "Male"_ansi;

         }

         strVoiceName = get_voice(strLang, strGender);

         string strUrl = "https://texttospeech.googleapis.com/v1/text:synthesize?key=AIzaSyDKPp-OZtrTb9K775SPG8uT4hMbfNybC_o"_ansi;

         string strResponse;

         ::property_set set;

         string strVoiceLanguageCode = strLang;
         string strVoiceGender = strGender.uppered();
         string strAudioEncoding = "MP3"_ansi;

         if (strVoiceLanguageCode.case_insensitive_equals("da"_ansi))
         {

            strVoiceLanguageCode = "da-DK"_ansi;

            strVoiceName = "da-DK-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("fr"_ansi))
         {

            strVoiceLanguageCode = "fr-FR"_ansi;

            strVoiceName = "fr-FR-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("it"_ansi))
         {

            strVoiceLanguageCode = "it-IT"_ansi;

            strVoiceName = "it-IT-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("de"_ansi))
         {

            strVoiceLanguageCode = "de-DE"_ansi;

            strVoiceName = "de-DE-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("es"_ansi))
         {

            strVoiceLanguageCode = "es-ES"_ansi;

            strVoiceName = "es-ES-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("nl"_ansi))
         {

            strVoiceLanguageCode = "nl-NL"_ansi;

            strVoiceName = "nl-NL-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("tr"_ansi))
         {

            strVoiceLanguageCode = "tr-TR"_ansi;

            strVoiceName = "tr-TR-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("pt-br"_ansi))
         {

            strVoiceLanguageCode = "pt-BR"_ansi;

            strVoiceName = "pt-BR-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("br"_ansi))
         {

            strVoiceLanguageCode = "pt-BR"_ansi;

            strVoiceName = "pt-BR-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("en-uk"_ansi))
         {

            strVoiceLanguageCode = "en-UK"_ansi;

            strVoiceName = "en-UK-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("uk"_ansi))
         {

            strVoiceLanguageCode = "en-UK"_ansi;

            strVoiceName = "en-UK-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("ru"_ansi))
         {

            strVoiceLanguageCode = "ru-RU"_ansi;

            strVoiceName = "ru-RU-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("ja"_ansi))
         {

            strVoiceLanguageCode = "ja-JP"_ansi;

            strVoiceName = "ja-JP-Standard-A"_ansi;

         }
         else if (strVoiceLanguageCode.case_insensitive_equals("ja"_ansi))
         {

            strVoiceLanguageCode = "ja-JP"_ansi;

            strVoiceName = "ja-JP-Standard-A"_ansi;

            }
         else
         {

            strVoiceLanguageCode = "en-US"_ansi;

            strVoiceName = "en-US-Standard-A"_ansi;

         }


         {

            ::property_set payload;

            //payload.curl - H "Authorization: Bearer "_ansi$(gcloud auth application - default print - access - token) - H "Content-Type: application/json; charset=utf-8"_ansi --data "{
            payload["input"]["text"] = strText;
            payload["voice"]["languageCode"] = strVoiceLanguageCode;
            payload["voice"]["name"] = strVoiceName;
            payload["voice"]["ssmlGender"] = strVoiceGender;
            payload["audioConfig"]["audioEncoding"] = strAudioEncoding;


            set["post"]["network_payload"] = payload;


         }

         //estatus = 
         
         payloadResponse = api_get(strUrl, set);

         string strAudioContent = payloadResponse["audioContent"];

         if (strAudioContent.is_empty())
         {

            throw ::exception(error_failed);

         }

         system()->base64()->decode(pfile->memory(), strAudioContent);

         file()->put_memory(pathMp3, pfile->memory());

         if (pfile->size() > 1000)
         {

            file()->put_text(pathTxt, strText);

         }

         pfile->seek_to_begin();

      }
      else
      {

         pfile->memory() = file()->as_memory(pathMp3);

      }

      informationf("speak: %s"_ansi, pathMp3.c_str());

      auto paudio = system()->audio();

      paudio->play_audio(pfile, esynchronicity);

      //return true;

   }


   void speaker::stop(const ::scoped_string & scopedstrLang)
   {

      //return true;

   }


   bool speaker::is_speaking(const ::scoped_string & scopedstrLang)
   {

      return false;

   }


   string speaker::get_voice(::string & strLang, const ::scoped_string & scopedstrGender)
   {

      string strVoice;

      if (strLang == "en"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "en-US-ChristopherNeural"_ansi;

         }
         else
         {

            strVoice = "en-US-ElizabethNeural"_ansi;

         }

      }
      else if (strLang == "de"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "de-DE-ConradNeural"_ansi;

         }
         else
         {

            strVoice = "de-DE-KatjaNeural"_ansi;

         }

      }
      else if (strLang == "fr"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "fr-FR-HenriNeural"_ansi;

         }
         else
         {

            strVoice = "fr-FR-DeniseNeural"_ansi;

         }

      }
      else if (strLang == "it"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "it-IT-DiegoNeural"_ansi;


         }
         else
         {

            strVoice = "it-IT-IsabellaNeural"_ansi;

         }

      }
      else if (strLang == "ja"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "ja-JP-KeitaNeural"_ansi;

         }
         else
         {

            strVoice = "ja-JP-NanamiNeural"_ansi;

         }

      }
      else if (strLang == "da"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "da-DK-JeppeNeural"_ansi;

         }
         else
         {

            strVoice = "da-DK-ChristelNeural"_ansi;

         }

      }
      else if (strLang == "sv"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "sv-SE-MattiasNeural"_ansi;

         }
         else
         {

            strVoice = "sv-SE-HilleviNeural"_ansi;

         }

      }
      else if (strLang == "tr"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "tr-TR-AhmetNeural"_ansi;

         }
         else
         {

            strVoice = "tr-TR-EmelNeural"_ansi;

         }

      }
      else if (strLang == "in"_ansi)
      {

         strLang = "hi"_ansi;

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "hi-IN-MadhurNeural"_ansi;

         }
         else
         {

            strVoice = "en-US-ElizabethNeural"_ansi;

         }

      }
      else if (strLang == "nl"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "nl-NL-MaartenNeural"_ansi;

         }
         else
         {

            strVoice = "nl-NL-ColetteNeural"_ansi;

         }

      }
      else if (strLang == "zh"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "zh-CN-YunyeNeural"_ansi;

         }
         else
         {

            strVoice = "zh-CN-XiaohanNeural"_ansi;

         }

      }
      else if (strLang == "ru"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "ru-RU-DmitryNeural"_ansi;

         }
         else
         {

            strVoice = "ru-RU-DariyaNeural"_ansi;

         }

      }
      else if (strLang == "ua"_ansi)
      {

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "uk-UA-OstapNeural"_ansi;

         }
         else
         {

            strVoice = "uk-UA-PolinaNeural"_ansi;

         }

      }
      else if (strLang == "uk"_ansi)
      {

         strLang = "en-GB"_ansi;

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "en-GB-RyanNeural"_ansi;

         }
         else
         {

            strVoice = "en-GB-LibbyNeural"_ansi;

         }

      }
      else if (strLang == "pt"_ansi)
      {

         strLang = "pt-BR"_ansi;

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "pt-BR-AntonioNeural"_ansi;

         }
         else
         {

            strVoice = "pt-BR-FranciscaNeural"_ansi;

         }

      }
      else
      {

         strLang = "en"_ansi;

         if (scopedstrGender == "Male"_ansi)
         {

            strVoice = "en-US-ChristopherNeural"_ansi;

         }
         else
         {

            strVoice = "en-US-ElizabethNeural"_ansi;

         }

      }

      return strVoice;

   }


} // namespace text_to_speech_google



