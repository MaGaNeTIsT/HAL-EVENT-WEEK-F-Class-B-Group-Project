//#ifndef _DXSOUND_H
//#define _DXSOUND_H
//
//
//#pragma comment(lib,"dxguid.lib")
//#pragma comment(lib,"dsound.lib")
//#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"dxguid.lib")
//
//#include <Windows.h>
//#include <mmsystem.h>
//#include <dsound.h>
//#include <mmreg.h>
////#include <SDKwavefile.h>
//
//typedef enum ESoundIndex {
//	BATTELMUSIC_STAGE01 = 0
//}SoundIndex;
//
//typedef struct SSoundData {
//	char* FilePath;
//}SoundData;
//
//typedef struct SWaveHeader{
//	char RiffID[4];
//	long WaveformChunkSize;
//	char WaveID[4];
//	char FormatID[4];
//	long FormatChunkSize;
//	short FormatTag;
//	short Channels;
//	long SampleRate;
//	long BytesPerSec;
//	short BlockAlign;
//	short BitsPerSample;
//	char DataID[4];
//	long DataSize;
//}WaveHeader;
//
//bool SoundDevice_Initialize(HWND hWnd);
//
//void SoundDevice_Finalize(void);
//
//bool SoundLoad(SoundIndex Index);
//
//bool OnPlaySound(SoundIndex Index);
//
//bool OnStopSound(SoundIndex Index);
//
//bool OnSetVolume(SoundIndex Index, LONG lVolume);
//
//#endif // !_DXSOUND_H