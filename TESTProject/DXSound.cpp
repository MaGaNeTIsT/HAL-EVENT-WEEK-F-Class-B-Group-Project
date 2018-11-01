//#include "Sound.h"
//#include "Common.h"
//#include <stdio.h>
//
//static LPDIRECTSOUND g_pSoundDevice = NULL;
//static LPDIRECTSOUNDBUFFER g_pSoundDeviceBuffer[SOUND_BUFFER_COUNT];
//static WaveHeader* pWaveHeader[SOUND_FILE_COUNT];
//static const SoundData sSoundFileData[SOUND_FILE_COUNT]=
//{
//	{"./BGM/01 - Nitro Fun - New Game.wav"}
//};
//
//bool SoundDevice_Initialize(HWND hWnd)
//{
//	for (int i = 0; i < SOUND_BUFFER_COUNT; i++)
//	{
//		g_pSoundDeviceBuffer[i] = NULL;
//	}
//
//	for (int i = 0; i < SOUND_FILE_COUNT; i++)
//	{
//		pWaveHeader[i] = NULL;
//	}
//
//	HRESULT hr = DirectSoundCreate(NULL, &g_pSoundDevice, NULL);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//
//	if (hWnd != GetForegroundWindow())
//	{
//		return FALSE;
//	}
//	hr = g_pSoundDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//
//	DSCAPS dscaps;
//	dscaps.dwSize = sizeof(DSCAPS);
//	hr = g_pSoundDevice->GetCaps(&dscaps);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//
//	DSBUFFERDESC SoundMainBufferInfo;
//	SoundMainBufferInfo.dwSize = sizeof(DSBUFFERDESC);
//	SoundMainBufferInfo.dwFlags = MY_SOUND_MAIN_FLAGS;
//	SoundMainBufferInfo.dwBufferBytes = 0;
//	SoundMainBufferInfo.lpwfxFormat = NULL;
//	SoundMainBufferInfo.dwReserved = 0;
//	hr = g_pSoundDevice->CreateSoundBuffer(&SoundMainBufferInfo, &g_pSoundDeviceBuffer[0], NULL);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//
//	return TRUE;
//}
//
//void SoundDevice_Finalize(void)
//{
//	for (int i = 0; i < SOUND_BUFFER_COUNT; i++)
//	{
//		SAFE_RELEASE(g_pSoundDeviceBuffer[i])
//	}
//
//	for (int i = 0; i < SOUND_FILE_COUNT; i++)
//	{
//		if (pWaveHeader[i] != NULL)
//		{
//			delete pWaveHeader[i];
//			pWaveHeader[i] = NULL;
//		}
//	}
//
//	SAFE_RELEASE(g_pSoundDevice)
//}
//
//bool SoundLoad(SoundIndex Index)
//{
//	FILE *fp;
//	if ((fp = fopen(sSoundFileData[Index].FilePath, "rb")) == NULL)
//	{
//		return FALSE;
//	}
//	
//	if (pWaveHeader[Index] != NULL)
//	{
//		return FALSE;
//	}
//	pWaveHeader[Index] = new WaveHeader;
//
//	fseek(fp, 0, SEEK_SET);
//	fread(pWaveHeader[Index], 1, sizeof(WaveHeader), fp);
//	if (memcmp(pWaveHeader[Index]->RiffID, "RIFF", 4) || memcmp(pWaveHeader[Index]->WaveID, "WAVE", 4) || memcmp(pWaveHeader[Index]->FormatID, "fmt ", 4) || memcmp(pWaveHeader[Index]->DataID, "data", 4))
//	{
//		return FALSE;
//	}
//
//	WAVEFORMATEX pWaveFormat;
//	ZeroMemory(&pWaveFormat, sizeof(WAVEFORMATEX));
//	//pWaveFormat.cbSize = ;
//	pWaveFormat.nChannels = pWaveHeader[Index]->Channels;
//	pWaveFormat.nSamplesPerSec = pWaveHeader[Index]->SampleRate;
//	pWaveFormat.wBitsPerSample = pWaveHeader[Index]->BitsPerSample;
//	pWaveFormat.wFormatTag = pWaveHeader[Index]->FormatTag;
//	pWaveFormat.nBlockAlign = (pWaveFormat.wBitsPerSample / 8) * pWaveFormat.nChannels;
//	pWaveFormat.nAvgBytesPerSec = pWaveFormat.nSamplesPerSec * pWaveFormat.nBlockAlign;
//
//	DSBUFFERDESC pBufferDesc;
//	ZeroMemory(&pBufferDesc, sizeof(DSBUFFERDESC));
//	pBufferDesc.dwSize = sizeof(DSBUFFERDESC);
//	pBufferDesc.dwFlags = MY_SOUND_FLAGS;
//	pBufferDesc.dwBufferBytes = pWaveHeader[Index]->DataSize;
//	pBufferDesc.lpwfxFormat = &pWaveFormat;
//	//pBufferDesc.dwReserved = ;
//	//pBufferDesc.guid3DAlgorithm = ;
//
//	HRESULT hr = g_pSoundDevice->CreateSoundBuffer(&pBufferDesc, &g_pSoundDeviceBuffer[(Index + 1)], NULL);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//	hr = g_pSoundDevice->QueryInterface(IID_IDirectSoundBuffer8, (void **)&g_pSoundDeviceBuffer[(Index + 1)]);
//	if (FAILED(hr))
//	{
//		g_pSoundDeviceBuffer[(Index + 1)]->Release();
//		return FALSE;
//	}
//
//	BYTE * pSoundPtr1 = NULL;
//	BYTE * pSoundPtr2 = NULL;
//	DWORD dwSoundSize1, dwSoundSize2;
//	hr = g_pSoundDeviceBuffer[(Index + 1)]->Lock(0, pWaveHeader[Index]->DataSize, (void **)&pSoundPtr1, &dwSoundSize1, (void **)&pSoundPtr2, &dwSoundSize2, 0);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//	fread(pSoundPtr1, 1, dwSoundSize1, fp);
//	if (pSoundPtr2 != NULL)
//	{
//		fread(pSoundPtr2, 1, dwSoundSize2, fp);
//	}
//	g_pSoundDeviceBuffer[(Index + 1)]->Unlock(pSoundPtr1, dwSoundSize1, pSoundPtr2, dwSoundSize2);
//
//	return TRUE;
//}
//
//bool OnPlaySound(SoundIndex Index)
//{
//	HRESULT hr = g_pSoundDeviceBuffer[(Index + 1)]->Play(0, 0, false);
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//	return TRUE;
//}
//
//bool OnStopSound(SoundIndex Index)
//{
//	HRESULT hr = g_pSoundDeviceBuffer[(Index + 1)]->Stop();
//	if (FAILED(hr))
//	{
//		return FALSE;
//	}
//	return TRUE;
//}
//
//bool OnSetVolume(SoundIndex Index, LONG lVolume)
//{
//	if ((lVolume >= DSBVOLUME_MIN) && (lVolume <= DSBVOLUME_MAX))
//	{
//		HRESULT hr = g_pSoundDeviceBuffer[(Index + 1)]->SetVolume(lVolume);
//		if (FAILED(hr))
//		{
//			return FALSE;
//		}
//		return TRUE;
//	}
//	return FALSE;
//}