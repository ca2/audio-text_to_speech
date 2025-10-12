#include "framework.h"
#include "speaker.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/application.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/crypto/crypto.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/system.h"
#include "aqua/audio/audio.h"
#include "aqua/platform/system.h"


CLASS_DECL_ACME string file_friendly_transform(const ::scoped_string & scopedstr, bool bTransformSlashes = true);


namespace text_to_speech_azure
{


   speaker::speaker()
   {

      m_iTranslatorFile = 1;
      m_strImplementation = "azure"_ansi;
//      m_strBrowserAccount = "speaker"_ansi;
      m_strService = "cognitive_services"_ansi;

   }


   speaker::~speaker()
   {

   }


   //void speaker::defer_api()
   //{

   //   if (!m_papi)
   //   {

   //      auto plibrary = system()->factory("api"_ansi, "azure"_ansi);

   //      if (!plibrary)
   //      {

   //         return false;

   //      }

   //      m_papi = plibrary->create < ::api >();

   //      if (!m_papi)
   //      {

   //         return false;

   //      }

   //      ::file::path pathProfile;

   //      pathProfile = directory()->appdata() / "speaker.network_payload"_ansi;

   //      auto estatus = m_papi->initialize_api(this, pathProfile);

   //      if (!estatus)
   //      {

   //         m_papi.release();

   //         return false;

   //      }

   //      estatus = m_papi->api_login("cognitive_services"_ansi, ""_ansi);

   //      if (!estatus)
   //      {

   //         m_papi.release();

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   void speaker::speak(const ::scoped_string & scopedstrText)
   {

      //auto estatus = 
      
      speak("en"_ansi, scopedstrText);

      //return estatus;

   }


   void speaker::speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, enum_synchronicity esynchronicity)
   {

      //auto estatus = 
      
      speak(""_ansi, scopedstrLang, scopedstrText, esynchronicity);

      //return estatus;

   }


   void speaker::speak(const ::scoped_string & scopedstrAttrParam, const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, enum_synchronicity esynchronicity)
   {

      if(!application()->m_bAudio)
      {

         return;

      }

      string strAttr(scopedstrAttrParam);

      string strLang(scopedstrLangParam);

      string strText(scopedstrTextParam);

   // ::xml::document d;

   // d.load("<root>"_ansi + strText + "</root>"_ansi);

   // strText = d.get_text();

      strText.trim();

      //throw ::exception(todo("html"_ansi));

      //strText = puser->html()->resolve_entities(strText);

      bool bRetry = false;

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
      else if(strLang.is_empty())
      {

         strLang = "en"_ansi;

      }

      int i1, i2;

      i1 = (int) (mathematics()->random(1, 2));

      i2 = (int) (mathematics()->random(1, 2));

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

      pathMp3 = pathFolder / strLang / strQuality / strGender / strFileRel + ".mp3"_ansi;

      pathTxt = pathFolder / strLang / strQuality / strGender / strFileRel + ".txt"_ansi;

      // todo... fastly check if file is mp3 file...
      if (file()->safe_get_string(pathTxt) == strText && file()->length(pathMp3) > 100)
      {

         goto play;

      }

   retry:

      //if (!defer_api())
      //{

      //   return false;

      //}


      //if (m_strTranslatorToken.is_empty())
      //{

         //if (!bRetry)
         //{

         //   bRetry = true;

         //   goto retry;

         //}

      //   return false;

      //}

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

         int iOld = 0;

         if(!iOld)
         {

            string strVoice;

            if(strGender == "male"_ansi)
            {

               strGender = "Male"_ansi;

            }
            else
            {

               strGender = "Female"_ansi;

            }

            if(strLang == "en"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "en-US-ChristopherNeural"_ansi;

               }
               else
               {

                  strVoice = "en-US-ElizabethNeural"_ansi;

               }

            }
            else if(strLang == "de"_ansi)
            {


               if(strGender == "Male"_ansi)
               {

                  strVoice = "de-DE-ConradNeural"_ansi;

               }
               else
               {

                  strVoice = "de-DE-KatjaNeural"_ansi;

               }


            }
            else if(strLang == "fr"_ansi)
            {


               if(strGender == "Male"_ansi)
               {

                  strVoice = "fr-FR-HenriNeural"_ansi;

               }
               else
               {

                  strVoice = "fr-FR-DeniseNeural"_ansi;

               }


            }
            else if(strLang == "it"_ansi)
            {


               if(strGender == "Male"_ansi)
               {

                  strVoice = "it-IT-DiegoNeural"_ansi;


               }
               else
               {

                  strVoice = "it-IT-IsabellaNeural"_ansi;

               }

            }
            else if(strLang == "ja"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "ja-JP-KeitaNeural"_ansi;

               }
               else
               {

                  strVoice = "ja-JP-NanamiNeural"_ansi;

               }

            }
            else if(strLang == "da"_ansi)
            {

               if(strGender == "Male"_ansi)
               {


                  strVoice = "da-DK-JeppeNeural"_ansi;

               }
               else
               {

                  strVoice = "da-DK-ChristelNeural"_ansi;

               }

            }
            else if(strLang == "sv"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "sv-SE-MattiasNeural"_ansi;

               }
               else
               {

                  strVoice = "sv-SE-HilleviNeural"_ansi;

               }

            }
            else if(strLang =="tr"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "tr-TR-AhmetNeural"_ansi;

               }
               else
               {

                  strVoice = "tr-TR-EmelNeural"_ansi;

               }

            }
            else if(strLang == "in"_ansi)
            {

               strLang = "hi"_ansi;

               if(strGender == "Male"_ansi)
               {

                  strVoice = "hi-IN-MadhurNeural"_ansi;

               }
               else
               {

                  strVoice = "en-US-ElizabethNeural"_ansi;

               }

            }
            else if(strLang == "nl"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "nl-NL-MaartenNeural"_ansi;

               }
               else
               {

                  strVoice = "nl-NL-ColetteNeural"_ansi;

               }

            }
            else if(strLang == "zh"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "zh-CN-YunyeNeural"_ansi;

               }
               else
               {

                  strVoice = "zh-CN-XiaohanNeural"_ansi;

               }

            }
            else if(strLang == "ru"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "ru-RU-DmitryNeural"_ansi;

               }
               else
               {

                  strVoice = "ru-RU-DariyaNeural"_ansi;

               }

            }
            else if(strLang == "ua"_ansi)
            {

               if(strGender == "Male"_ansi)
               {

                  strVoice = "uk-UA-OstapNeural"_ansi;

               }
               else
               {

                  strVoice = "uk-UA-PolinaNeural"_ansi;

               }

            }
            else if(strLang == "uk"_ansi)
            {

               strLang = "en-GB"_ansi;

               if(strGender == "Male"_ansi)
               {

                  strVoice = "en-GB-RyanNeural"_ansi;

               }
               else
               {

                  strVoice = "en-GB-LibbyNeural"_ansi;

               }

            }
            else if(strLang == "pt"_ansi)
            {

               strLang = "pt-BR"_ansi;

               if(strGender == "Male"_ansi)
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

               if(strGender == "Male"_ansi)
               {

                  strVoice = "en-US-ChristopherNeural"_ansi;

               }
               else
               {

                  strVoice = "en-US-ElizabethNeural"_ansi;

               }


            }

            ::property_set set;



            //set["headers"]["accept"] = "application/ssml+xml"_ansi;
            set["headers"]["X-Microsoft-OutputFormat"]= "audio-24khz-160kbitrate-mono-mp3"_ansi;
            set["headers"]["User-Agent"]= get_app()->m_strAppId;
            string strSsml="<speak version='1.0' xml:lang='en-US'>"_ansi;
            //strSsml+="<voice xml:lang='"_ansi+strLang+"' xml:gender='Male' name='en-US-ChristopherNeura'>"_ansi;
            strSsml+="<voice xml:lang='"_ansi+strLang+"' xml:gender='"_ansi+strGender+"' name='"_ansi+strVoice+"'>"_ansi;
            strSsml+=strText;
            strSsml += "</voice>"_ansi;
            strSsml +="</speak>"_ansi;
            set["post"]["raw_text_content_type"] = "application/ssml+xml"_ansi;
            set["post"]["raw_text"]= strSsml;

            string strEncode = ::url::encode(strText);

            string strDecode = ::url::decode(strEncode);

            string strUrl = "tts.speech.microsoft.com/cognitiveservices/v1"_ansi;

            auto memory = api_memory(strUrl, set);

            //auto strMp3 = file()->as_string(pathMp3);
            string strStatus;
            set["http_status"].as(strStatus);
            int iStatusCode;

            iStatusCode = set["http_status_code"];

            if (iStatusCode >= 400 && iStatusCode < 500)
            {
               
               string strMp3 = memory.get_string();

               if (strMp3.case_insensitive_contains("The incoming token has expired"_ansi))
               {

                  //m_strTranslatorToken.empty();

                  if (!bRetry)
                  {

                     bRetry = true;

                     goto retry;

                  }

                  //return false;

                  throw ::exception(error_authentication);

               }
               else if (strMp3.case_insensitive_contains("'language' must be a valid language"_ansi))
               {

                  auto path = pdirectorysystem->userconfig() / "translators/missing.txt"_ansi;

                  file_system()->append(path, ::string(strLang + "\n"_ansi));

                  throw ::exception(error_failed);

               }
               else if (strMp3.case_insensitive_contains("Language name is not supported"_ansi))
               {

                  auto path = pdirectorysystem->userconfig() / "translators/missing2.txt"_ansi;

                  file_system()->append(path, ::string(strLang + "\n"_ansi));

                  throw ::exception(error_failed);

               }
               else
               {

                  throw ::exception(error_failed);

               }

            }

            file()->put_text(pathTxt, strText);

            file()->put_memory(pathMp3, memory);

         }

      }

   play:

      informationf("speak: %s"_ansi, pathMp3.c_str());

      auto paudio = system()->audio();

      auto pfile = fully_shared_reader(pathMp3);

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


} // namespace text_to_speech_azure




