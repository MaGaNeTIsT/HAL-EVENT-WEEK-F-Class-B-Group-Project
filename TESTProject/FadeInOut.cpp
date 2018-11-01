#include "FadeInOut.h"
#include "MyDirect.h"
#include "Common.h"
#include "GameFrame.h"

static double fAlpha = 0.0;
static double fAlphaSpeed = FADE_ALPHA_SPEED;
static FadeState eFadeState = EFS_NONE;

void FadeInOut_Init(void)
{
	fAlpha = 0.0;
	fAlphaSpeed = FADE_ALPHA_SPEED;
	eFadeState = EFS_NONE;
}

void FadeInOut_On(void)
{
	SquarePolygon aPolygon;
	Vertex2D Format[4];
	SquarePolygon Polygon;
	Vertex2D aFormat[4];

	switch (eFadeState)
	{
	case EFS_NONE:

		break;
	case EFS_IN:

		aPolygon.TextureFormat = &Format[0];
		aPolygon.CentrePoint = D3DXVECTOR4(0.0, 0.0, 1.0, 1.0);
		aPolygon.ImpactDistance.Top = 0;
		aPolygon.ImpactDistance.Bottom = 0;
		aPolygon.ImpactDistance.Left = 0;
		aPolygon.ImpactDistance.Right = 0;
		aPolygon.Index = FADE_INDEX;
		aPolygon.TextureSize.Height = WINDOW_HEIGHT;
		aPolygon.TextureSize.Width = WINDOW_WIDTH;

		while (1)
		{

			aPolygon.TextureFormat[0] = FormatData_Initialize(0, 0, 255, 255, 255, fAlpha, 0.0, 0.0);
			aPolygon.TextureFormat[1] = FormatData_Initialize(WINDOW_WIDTH, 0, 255, 255, 255, fAlpha, 1.0, 0.0);
			aPolygon.TextureFormat[2] = FormatData_Initialize(0, WINDOW_HEIGHT, 255, 255, 255, fAlpha, 0.0, 1.0);
			aPolygon.TextureFormat[3] = FormatData_Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 255, 255, 255, fAlpha, 1.0, 1.0);

			HRESULT hr;
			LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

			pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(1, 1, 1), 1.0f, 0);
			if (SUCCEEDED(pDevice->BeginScene()))
			{
				MyDirect3D_DeviceRenderTextureAlpha();
				//Draw Function (

				MyDirect3D_GetDevice()->SetFVF(FVF_FADEINOUT);
				MyDirect3D_GetDevice()->SetTexture(0, NULL);
				Draw(aPolygon.TextureFormat, D3DPT_TRIANGLESTRIP, 2);

				//Draw Function )
				MyDirect3D_DestoryRenderTextureAlpha();
			}
			pDevice->EndScene();
			hr = pDevice->Present(NULL, NULL, NULL, NULL);

			fAlpha += fAlphaSpeed;
			if (fAlpha > 255)
			{
				fAlpha = 255.0;
				eFadeState = EFS_NONE;
				break;
			}
		}
		break;
	case EFS_OUT:

		Polygon.TextureFormat = &aFormat[0];
		Polygon.CentrePoint = D3DXVECTOR4(0.0, 0.0, 1.0, 1.0);
		Polygon.ImpactDistance.Top = 0;
		Polygon.ImpactDistance.Bottom = 0;
		Polygon.ImpactDistance.Left = 0;
		Polygon.ImpactDistance.Right = 0;
		Polygon.Index = FADE_INDEX;
		Polygon.TextureSize.Height = WINDOW_HEIGHT;
		Polygon.TextureSize.Width = WINDOW_WIDTH;

		while (1)
		{

			Polygon.TextureFormat[0] = FormatData_Initialize(0, 0, 255, 255, 255, fAlpha, 0.0, 0.0);
			Polygon.TextureFormat[1] = FormatData_Initialize(WINDOW_WIDTH, 0, 255, 255, 255, fAlpha, 1.0, 0.0);
			Polygon.TextureFormat[2] = FormatData_Initialize(0, WINDOW_HEIGHT, 255, 255, 255, fAlpha, 0.0, 1.0);
			Polygon.TextureFormat[3] = FormatData_Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, 255, 255, 255, fAlpha, 1.0, 1.0);

			HRESULT hr;
			LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

			pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(1, 1, 1), 1.0f, 0);
			if (SUCCEEDED(pDevice->BeginScene()))
			{
				MyDirect3D_DeviceRenderTextureAlpha();
				//Draw Function (

				pDevice->SetFVF(FVF_FADEINOUT);
				pDevice->SetTexture(0, NULL);
				Draw(Polygon.TextureFormat, D3DPT_TRIANGLESTRIP, 2);

				//Draw Function )
				MyDirect3D_DestoryRenderTextureAlpha();
			}
			pDevice->EndScene();
			hr = pDevice->Present(NULL, NULL, NULL, NULL);

			GameStage_Render();

			fAlpha += fAlphaSpeed;
			if (fAlpha < 0)
			{
				fAlpha = 0.0;
				eFadeState = EFS_NONE;
				break;
			}
		}
		break;
	}
}

void OnFadeIn(void)
{
	fAlpha = 0.0;
	fAlphaSpeed = FADE_ALPHA_SPEED;
	eFadeState = EFS_IN;
}

void OnFadeOut(void)
{
	fAlpha = 255.0;
	fAlphaSpeed = 0 - FADE_ALPHA_SPEED;
	eFadeState = EFS_OUT;
}