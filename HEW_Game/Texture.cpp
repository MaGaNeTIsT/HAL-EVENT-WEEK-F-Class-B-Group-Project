#include "Texture.h"
#include "MyDirect.h"

static const TextureFileData Texture[TEXTURE_COUNT] =
{
	{ "./Texture/Miracle01.jpg", 662, 662, -1 },
	{ "./Texture/Miracle02.jpg", 662, 662, 5 },
	{ "./Texture/number.tga",320,32,10 },
	{ "./Texture/Red.png", 20, 20, -1 }
};
static LPDIRECT3DTEXTURE9 g_pTexture[TEXTURE_COUNT];
static int Num = 0;


int TextureLoad(void)
{
	HRESULT hr;
	int iLoadFailCount = 0;

	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		g_pTexture[i] = NULL;
	}
	
	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		hr = D3DXCreateTextureFromFile(MyDirect3D_GetDevice(), Texture[i].pSrcFile, &g_pTexture[i]);
		if (FAILED(hr))
		{
			iLoadFailCount++;
		}
	}

	return iLoadFailCount;
}

bool TextureSampler(void)
{
	HRESULT hr;

	//hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 4);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	//hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	//hr = MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 255));
	if (FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;
}

bool OnTexture(LPDIRECT3DTEXTURE9 Texture)
{
	HRESULT hr;

	hr = MyDirect3D_GetDevice()->SetTexture(0, Texture);
	if (FAILED(hr))
	{
		return FALSE;
	}
	return TRUE;
}

void ReleaseTexture()
{
	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 GetTexture(TextureIndex Index)
{
	return g_pTexture[Index];
}
UINT GetTextureWidth(TextureIndex Index)
{
	return Texture[Index].Width;
}
UINT GetTextureHeight(TextureIndex Index)
{
	return Texture[Index].Height;
}
UINT GetTextureFPSCount(TextureIndex Index)
{
	return Texture[Index].TextureFPSCount;
}

int Get_Num(void)
{
	return Num;
}
void Set_Num(int a)
{
	Num = a;
}