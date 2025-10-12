#pragma once


#include "aqua/_.h"
#include "apex_windows_common/_.h"
#include "nano_speech_sapi/_.h"


#if defined(_text_to_speech_sapi_project)
#define CLASS_DECL_TEXT_TO_SPEECH_SAPI CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TEXT_TO_SPEECH_SAPI CLASS_DECL_IMPORT
#endif



