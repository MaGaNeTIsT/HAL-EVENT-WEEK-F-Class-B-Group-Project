#ifndef _TEXTURE_H
#define _TEXTURE_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif
#include <d3dx9.h>
#include <Windows.h>
#include "Common.h"

typedef enum ETextureIndex {
	MIRACLE01 = 0,
	MIRACLE02,
	NUMBER,
	HP
}TextureIndex;

typedef struct sDoubleData {
	double x;
	double y;
}DoubleData;

typedef struct sTexturePosition {
	UINT NextIndex;
	DoubleData Position[4];
}TexturePosition;

typedef struct sTextureFileData_tag {
	LPCSTR pSrcFile;
	UINT Width;
	UINT Height;
	int TextureFPSCount;
	TexturePosition TexturePos[TEXTURE_FPS_COUNT];
}TextureFileData;

int TextureLoad(void);
bool TextureSampler(void);
bool OnTexture(LPDIRECT3DTEXTURE9 Texture);
void ReleaseTexture(void);

LPDIRECT3DTEXTURE9 GetTexture(TextureIndex Index);
UINT GetTextureWidth(TextureIndex Index);
UINT GetTextureHeight(TextureIndex Index);
UINT GetTextureFPSCount(TextureIndex Index);

int Get_Num(void);
void Set_Num(int a);

#endif