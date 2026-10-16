// MinGW's SAPI library omits this format GUID, declared by sapi.h.
// Value matches SpeechAudioFormatGUIDWave in the Windows SDK's sapi51.h.
#include <guiddef.h>

extern "C" const GUID SPDFID_WaveFormatEx =
   {0xc31adbae, 0x527f, 0x4ff5, {0xa2, 0x30, 0xf6, 0x2b, 0xb6, 0x1f, 0xf7, 0x0c}};