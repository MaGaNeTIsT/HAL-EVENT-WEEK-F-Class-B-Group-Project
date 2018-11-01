#include "GameFrame.h"
#include "debugPrintf.h"
#include "Common.h"
#include "Polygon.h"
#include "MyDirect.h"
#include "Texture.h"
#include "Polygon.h"
#include "Animation.h"
#include "Input.h"
#include "Player.h"
#include "EnemyAI.h"
#include "Bullet.h"
#include "Circle.h"
#include "BulletMap.h"
#include "Sound.h"
#include <time.h>
#include "TextPrint.h"
#include "score.h"
#include "FadeInOut.h"
#include "GameTimer.h"

static VertexCircle* spScene_BackGround = NULL;
static SquarePolygon* pPointer = NULL;
static VertexCircle* pCursor = NULL;
static VertexCircle** ppBrush = NULL;
static UINT iBrushIndex = 0;
static VertexCircle* pMiracleCenter = NULL;
static VertexCircle* pMiracle[6] = { NULL ,NULL ,NULL ,NULL ,NULL ,NULL };
static UINT pMiracleIndex[6] = { 0,0,0,0,0,0 };
static PlayerData* pPlayer = NULL;
static PlayerData* pBoss = NULL;
static DrawNumData Score = Create_NumData(0, 0, 0, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT);
static int iStraightBulletMemberIndex = 0;
static int iStraightBulletIndex = 0;
GameState eGameState = EGS_TITLE;

#define BRUSH_COUNT (250)

void SetRewardData(int Number)
{
	Score.iNum += Number;
}

void UpdateGameLogic(HINSTANCE hInstance, HWND hWnd)
{
	DIMOUSESTATE* pMousePer = MouseInputDeviceAuthorization();
	//DIJOYSTATE* pJoyPer = JoyInputDeviceAuthorization();
	if (pMousePer != NULL)
	{
		if (UpdateInput(hInstance, hWnd) == Com_Sp)
		{
			pCursor->sCircleFormat[0].position.x += pMousePer->lX * 0.30f;
			pCursor->sCircleFormat[0].position.y += pMousePer->lY * 0.30f;
			if (pCursor->sCircleFormat[0].position.x <= 0)
			{
				pCursor->sCircleFormat[0].position.x = 0;
			}
			if (pCursor->sCircleFormat[0].position.x >= WINDOW_WIDTH)
			{
				pCursor->sCircleFormat[0].position.x = WINDOW_WIDTH;
			}
			if (pCursor->sCircleFormat[0].position.y <= 0)
			{
				pCursor->sCircleFormat[0].position.y = 0;
			}
			if (pCursor->sCircleFormat[0].position.y >= WINDOW_HEIGHT)
			{
				pCursor->sCircleFormat[0].position.y = WINDOW_HEIGHT;
			}

			if (ppBrush[iBrushIndex] != NULL)
			{
				DestoryCircle(ppBrush[iBrushIndex]);
				ppBrush[iBrushIndex] = CreateCircle(pCursor->sCircleFormat[0].position.x, pCursor->sCircleFormat[0].position.y, 10.0f, 16, 0.0f);
				iBrushIndex = (iBrushIndex + 1) % BRUSH_COUNT;
			}
			else
			{
				ppBrush[iBrushIndex] = CreateCircle(pCursor->sCircleFormat[0].position.x, pCursor->sCircleFormat[0].position.y, 10.0f, 16, 0.0f);
				iBrushIndex = (iBrushIndex + 1) % BRUSH_COUNT;
			}
		}
	}

	DoRollCircle(pCursor);

	for (DWORD i = 0; i < 6; i++)
	{
		if (!pMiracleIndex[i])
		{
			if (CircleImapct(pCursor, pMiracle[i]))
			{
				pMiracleIndex[i] = 1;
				break;
			}
			break;
		}
		if (pMiracleIndex[i])
		{
			if ((i + 1) < 6)
			{
				if (!pMiracleIndex[i + 1])
				{
					if (CircleImapct(pCursor, pMiracle[i + 1]))
					{
						pMiracleIndex[i + 1] = 1;
						break;
					}
					break;
				}
			}
		}
	}
	Score.iNum = pMiracleIndex[0] + pMiracleIndex[1] + pMiracleIndex[2] + pMiracleIndex[3] + pMiracleIndex[4] + pMiracleIndex[5];
	if (Score.iNum == 6)
	{
		DoRollCircle(spScene_BackGround);
	}
}

void EnterGameStage(GameState State, HINSTANCE hInstance, HWND hWnd)
{
	OnFadeIn();
	FadeInOut_On();
	GameStage_Final(hInstance,hWnd);
	eGameState = State;
	GameStage_Init(hInstance, hWnd);
	UpdateGameLogic(hInstance, hWnd);
	OnFadeOut();
}

void GameStage_Init(HINSTANCE hInstance, HWND hWnd)
{
	FLOAT R = GetTextureWidth(MIRACLE01) * GetTextureWidth(MIRACLE01) + GetTextureHeight(MIRACLE01) * GetTextureHeight(MIRACLE01);
	R = sqrtf(R) / 2;
	spScene_BackGround = CreateCircle((WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f), R, 4, 0.0f);
	spScene_BackGround->fAngle = -45.0f;
	DoRollCircle(spScene_BackGround);
	spScene_BackGround->fRollSpeed = 5.0f;
	spScene_BackGround->sCircleFormat[1].TextureCoor = D3DXVECTOR2(0.0f, 0.0f);
	spScene_BackGround->sCircleFormat[2].TextureCoor = D3DXVECTOR2(1.0f, 0.0f);
	spScene_BackGround->sCircleFormat[4].TextureCoor = D3DXVECTOR2(0.0f, 1.0f);
	spScene_BackGround->sCircleFormat[3].TextureCoor = D3DXVECTOR2(1.0f, 1.0f);

	//pPointer = CreateSquarePolygon(1, (WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f), 80, 80);
	//pPointer->TextureFormat[0].color = D3DCOLOR_RGBA(255, 1, 1, 255);
	//pPointer->TextureFormat[1].color = D3DCOLOR_RGBA(255, 1, 1, 255);
	//pPointer->TextureFormat[2].color = D3DCOLOR_RGBA(255, 1, 1, 255);
	//pPointer->TextureFormat[3].color = D3DCOLOR_RGBA(255, 1, 1, 255);
	//pPointer->TextureFormat[0].TextureCoor = D3DXVECTOR2(0, 0);
	//pPointer->TextureFormat[1].TextureCoor = D3DXVECTOR2(1, 0);
	//pPointer->TextureFormat[2].TextureCoor = D3DXVECTOR2(0, 1);
	//pPointer->TextureFormat[3].TextureCoor = D3DXVECTOR2(1, 1);

	pCursor = CreateCircle((WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f), 10.0f, 16, 0.0f);
	pMiracleCenter = CreateCircle((WINDOW_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f), 180.0f, 6, 0.0f);
	pMiracleCenter->fAngle = -30.0f;
	DoRollCircle(pMiracleCenter);

	for (DWORD i = 0; i < 6; i++)
	{
		pMiracle[i] = CreateCircle(pMiracleCenter->sCircleFormat[i + 1].position.x, pMiracleCenter->sCircleFormat[i + 1].position.y, 50.0f, 16, 0.0f);
	}

	ppBrush = new VertexCircle*[BRUSH_COUNT];
	for (DWORD i = 0; i < BRUSH_COUNT; i++)
	{
		ppBrush[i] = NULL;
	}

	Score = Create_NumData(0, 0, 0, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT);
}

void GameStage_Final(HINSTANCE hInstance, HWND hWnd)
{
	DestoryCircle(spScene_BackGround);
	for (DWORD i = 0; i < BRUSH_COUNT; i++)
	{
		if (ppBrush[i] != NULL)
		{
			DestoryCircle(ppBrush[i]);
		}
	}
	delete[]ppBrush;

	for (DWORD i = 0; i < 6; i++)
	{
		DestoryCircle(pMiracle[i]);
	}
	DestoryCircle(pMiracleCenter);
	DestoryCircle(pCursor);
}

void GameStage_Render(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetFVF(FVF_VERTEX2D);

	if (Score.iNum == 6)
	{
		if ((OnTexture(GetTexture(MIRACLE02))) == TRUE)
		{
			Vertex2D Format[4];
			Format[0].color = spScene_BackGround->sCircleFormat[1].color;
			Format[0].position = spScene_BackGround->sCircleFormat[1].position;
			Format[0].TextureCoor = spScene_BackGround->sCircleFormat[1].TextureCoor;
			Format[1].color = spScene_BackGround->sCircleFormat[2].color;
			Format[1].position = spScene_BackGround->sCircleFormat[2].position;
			Format[1].TextureCoor = spScene_BackGround->sCircleFormat[2].TextureCoor;
			Format[2].color = spScene_BackGround->sCircleFormat[4].color;
			Format[2].position = spScene_BackGround->sCircleFormat[4].position;
			Format[2].TextureCoor = spScene_BackGround->sCircleFormat[4].TextureCoor;
			Format[3].color = spScene_BackGround->sCircleFormat[3].color;
			Format[3].position = spScene_BackGround->sCircleFormat[3].position;
			Format[3].TextureCoor = spScene_BackGround->sCircleFormat[3].TextureCoor;
			Draw(Format, D3DPT_TRIANGLESTRIP, 2);
		}
	}
	else
	{
		if ((OnTexture(GetTexture(MIRACLE01))) == TRUE)
		{
			Vertex2D Format[4];
			Format[0].color = spScene_BackGround->sCircleFormat[1].color;
			Format[0].position = spScene_BackGround->sCircleFormat[1].position;
			Format[0].TextureCoor = spScene_BackGround->sCircleFormat[1].TextureCoor;
			Format[1].color = spScene_BackGround->sCircleFormat[2].color;
			Format[1].position = spScene_BackGround->sCircleFormat[2].position;
			Format[1].TextureCoor = spScene_BackGround->sCircleFormat[2].TextureCoor;
			Format[2].color = spScene_BackGround->sCircleFormat[4].color;
			Format[2].position = spScene_BackGround->sCircleFormat[4].position;
			Format[2].TextureCoor = spScene_BackGround->sCircleFormat[4].TextureCoor;
			Format[3].color = spScene_BackGround->sCircleFormat[3].color;
			Format[3].position = spScene_BackGround->sCircleFormat[3].position;
			Format[3].TextureCoor = spScene_BackGround->sCircleFormat[3].TextureCoor;
			Draw(Format, D3DPT_TRIANGLESTRIP, 2);
		}
	}

	if ((OnTexture(GetTexture(HP))) == TRUE)
	{
		for (DWORD i = 0; i < 5; i++)
		{
			if (pMiracleIndex[i + 1])
			{
				Vertex2D Line[] =
				{
					{ D3DXVECTOR4(pMiracle[i]->sCircleFormat[0].position.x, pMiracle[i]->sCircleFormat[0].position.y, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },
					{ D3DXVECTOR4(pMiracle[i + 1]->sCircleFormat[0].position.x, pMiracle[i + 1]->sCircleFormat[0].position.y, 1.0f, 0.0f), D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) }
				};
				pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, Line, sizeof(Vertex2D));
			}
		}
	}
	//if ((OnTexture(GetTexture(HP))) == TRUE)
	//{
	//	for (DWORD i = 0; i < 6; i++)
	//	{
	//		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, pMiracle[i]->fCircleFormatCount, pMiracle[i]->sCircleFormat, sizeof(Vertex2D));
	//	}
	//}
	if ((OnTexture(GetTexture(HP))) == TRUE)
	{
		for (DWORD i = 0; i < BRUSH_COUNT; i++)
		{
			if (ppBrush[i] != NULL)
			{
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, ppBrush[i]->fCircleFormatCount, ppBrush[i]->sCircleFormat, sizeof(Vertex2D));
			}
		}
	}
	if ((OnTexture(GetTexture(HP))) == TRUE)
	{
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, pCursor->fCircleFormatCount, pCursor->sCircleFormat, sizeof(Vertex2D));
	}

	Draw_Num(Score);

	//if ((OnTexture(GetTexture(HP))) == TRUE)
	//{
	//	Draw(pPointer->TextureFormat, D3DPT_TRIANGLESTRIP, 2);
	//}
}

void GameStage_Timer(WPARAM wParam)
{
	switch (wParam)
	{
	case TC_TIMER01:

		pPlayer->PlayerMoveAnimation();

		break;
	case TC_TIMER02:

		switch (pPlayer->Get_PlayerShoot())
		{
		case PSh_None:
			break;
		case PSh_Shoot:
			pPlayer->OnPlayerShoot(pPlayer);
			break;
		}

		break;
	case TC_TIMER03:

		BulletStraight_BombAnimation();

		for (int i = 0; i < BULLET_CIRCLE_POOL; i++)
		{
			if (Get_Circle(i) != NULL)
			{
				for (int Index = 0; Index < BULLET_COUNT_CIRCLE; Index++)
				{
					if ((Get_BulletCircle(i)[Index].Get_Polygon()) != NULL)
					{
						Get_BulletCircle(i)[Index].BombAnimation();
					}
				}
			}
		}
		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
		{
			if ((pPlayer->Get_PlayerBullet(i) != NULL))
			{
				if ((pPlayer->Get_PlayerBullet(i)->Get_Polygon()) != NULL)
				{
					switch (pPlayer->Get_PlayerBullet(i)->Get_BulletState())
					{
					case BS_Bomb:
						pPlayer->Get_PlayerBullet(i)->BombAnimation();
						break;
					}
				}
			}
		}

		break;
	case TC_TIMER04:

		//RandomBullet_Initialize(pBoss, pPlayer);

		//BulletStraight_Create(60, 0, 50, 0, 700, ESBD_Vertical, 5.0, pBoss, pPlayer);
		//BulletStraight_Create(60, 0, 350, 100, 650, ESBD_Vertical, 5.0, pBoss, pPlayer);
		//BulletStraight_Create(60, 0, 650, 0, 700, ESBD_Vertical, 5.0, pBoss, pPlayer);
		//BulletStraight_Create(60, 0, 950, 100, 650, ESBD_Vertical, 5.0, pBoss, pPlayer);
		//BulletStraight_Create(60, 0, 1250, 0, 700, ESBD_Vertical, 5.0, pBoss, pPlayer);
		//BulletStraight_Create(60, 0, 1550, 100, 650, ESBD_Vertical, 5.0, pBoss, pPlayer);

		break;
	case TC_TIMER05:

		break;
	}
}

GameState GameStage_Get(void)
{
	return eGameState;
}