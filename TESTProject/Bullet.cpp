#include "Bullet.h"
#include "Common.h"
#include <math.h>
#include "Texture.h"
#include "Player.h"
#include "sound.h"

BulletData::BulletData()
{
	spBulletPolygon = CreateSquarePolygon(0, -50.0f, -50.0f, 16, 24);
	pBulletTexPtr = GetTexture(BULLETBOSS);
	eBulletState = BS_None;
	sBulletMoveCoor.x = spBulletPolygon->CentrePoint.x;
	sBulletMoveCoor.y = spBulletPolygon->CentrePoint.y;
	sBulletMoveCoor.HorizontalSpeed = BULLET_MOVEX;
	sBulletMoveCoor.VerticalSpeed = BULLET_MOVEY;
	sBulletDamage.Damage = BULLET_DAMAGE;
	sCircleBulletPos.Index = 0;
	sCircleBulletPos.pCircle = NULL;
	pTarget_From = NULL;
	pTarget_OnHit = NULL;
}

BulletData::BulletData(UINT Index, double x, double y, LPDIRECT3DTEXTURE9 pTex, UINT Width, UINT Height, double bx, double by)
{
	spBulletPolygon = CreateSquarePolygon(Index, x, y, Width, Height);
	pBulletTexPtr = pTex;
	eBulletState = BS_None;
	sBulletMoveCoor.x = spBulletPolygon->CentrePoint.x;
	sBulletMoveCoor.y = spBulletPolygon->CentrePoint.y;
	sBulletMoveCoor.HorizontalSpeed = bx;
	sBulletMoveCoor.VerticalSpeed = by;
	sBulletDamage.Damage = BULLET_DAMAGE;
	sCircleBulletPos.Index = 0;
	sCircleBulletPos.pCircle = NULL;
	pTarget_From = NULL;
	pTarget_OnHit = NULL;
}

BulletData::~BulletData()
{
	if (spBulletPolygon != NULL)
	{
		if (spBulletPolygon->TextureFormat != NULL)
		{
			delete[]spBulletPolygon->TextureFormat;
			spBulletPolygon->TextureFormat = NULL;
		}

		delete spBulletPolygon;
		spBulletPolygon = NULL;
	}
	pBulletTexPtr = NULL;
	sCircleBulletPos.Index = 0;
	sCircleBulletPos.pCircle = NULL;
	pTarget_From = NULL;
	pTarget_OnHit = NULL;
}

SquarePolygon* BulletData::Get_Polygon(void)
{
	return spBulletPolygon;
}

void BulletData::Reset(UINT Index, double x, double y, LPDIRECT3DTEXTURE9 pTex, UINT Width, UINT Height, double bx, double by)
{
	if (spBulletPolygon != NULL)
	{
		if (spBulletPolygon->TextureFormat != NULL)
		{
			delete[]spBulletPolygon->TextureFormat;
			spBulletPolygon->TextureFormat = NULL;
		}

		delete spBulletPolygon;
		spBulletPolygon = NULL;
	}

	spBulletPolygon = CreateSquarePolygon(Index, x, y, Width, Height);
	pBulletTexPtr = pTex;
	eBulletState = BS_None;
	sBulletMoveCoor.x = spBulletPolygon->CentrePoint.x;
	sBulletMoveCoor.y = spBulletPolygon->CentrePoint.y;
	sBulletMoveCoor.HorizontalSpeed = bx;
	sBulletMoveCoor.VerticalSpeed = by;
	sBulletDamage.Damage = BULLET_DAMAGE;
}

void BulletData::Move(void)
{
	sBulletMoveCoor.x += sBulletMoveCoor.HorizontalSpeed;
	sBulletMoveCoor.y += sBulletMoveCoor.VerticalSpeed;
}

void BulletData::OnHit(PlayerData* pTarget)
{
	int b = 0;
	switch (eBulletState)
	{
	case BS_None:
		if (spBulletPolygon != NULL)
		{
			if ((pTarget->Get_PlayerPolygon()) != NULL)
			{
				double dy = fabs((spBulletPolygon->CentrePoint.y) - (pTarget->Get_PlayerPolygon()->CentrePoint.y));
				double dx = fabs((spBulletPolygon->CentrePoint.x) - (pTarget->Get_PlayerPolygon()->CentrePoint.x));
				double rx = (spBulletPolygon->ImpactDistance.Left) + (pTarget->Get_PlayerPolygon()->ImpactDistance.Right);
				double ry = (spBulletPolygon->ImpactDistance.Top) + (pTarget->Get_PlayerPolygon()->ImpactDistance.Bottom);
				if ((dy <= ry) && (dx <= rx))
				{
					eBulletState = BS_PlayerImpact;
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
			}

		}
		break;
	case BS_PlayerImpact:
		pTarget->OnHurt_Bullet(pTarget_From);
		OnBomb();
		eBulletState = BS_Bomb;
		break;
	}
}

bool BulletData::Update(void)
{
	switch (eBulletState)
	{
	case BS_Bomb:

		break;
	default:
		if (spBulletPolygon != NULL)
		{
			Move();

			spBulletPolygon->CentrePoint.x = sBulletMoveCoor.x;
			spBulletPolygon->CentrePoint.y = sBulletMoveCoor.y;

			UpdatePolygon(spBulletPolygon);

			if ((spBulletPolygon->CentrePoint.y > WINDOW_HEIGHT) || (spBulletPolygon->CentrePoint.y < 0))
			{
				return FALSE;
			}
			if ((spBulletPolygon->CentrePoint.x > WINDOW_WIDTH) || (spBulletPolygon->CentrePoint.x < 0))
			{
				return FALSE;
			}
		}
		break;
	}
	return TRUE;
}

void BulletData::Release(void)
{
	if (spBulletPolygon != NULL)
	{
		if (spBulletPolygon->TextureFormat != NULL)
		{
			delete[]spBulletPolygon->TextureFormat;
			spBulletPolygon->TextureFormat = NULL;
		}

		delete spBulletPolygon;
		spBulletPolygon = NULL;
	}
}

void BulletData::Set_CircleIndex(VertexCircle* pCircle, UINT Index)
{
	sCircleBulletPos.Index = Index;
	sCircleBulletPos.pCircle = pCircle;
}

void BulletData::Set_Target_From(PlayerData* pTarget)
{
	pTarget_From = pTarget;
}

void BulletData::Set_Target_OnHit(PlayerData* pTarget)
{
	pTarget_OnHit = pTarget;
}

void BulletData::Set_BulletState(BulletState State)
{
	eBulletState = State;
}

void BulletData::Set_BulletMoveCoor(BulletMoveCoor Coor)
{
	sBulletMoveCoor = Coor;
}

void BulletData::Set_Texture(LPDIRECT3DTEXTURE9 Texture)
{
	pBulletTexPtr = Texture;
}

VertexCircle* BulletData::Get_Circle(void)
{
	return sCircleBulletPos.pCircle;
}

UINT BulletData::Get_CircleIndex(void)
{
	return sCircleBulletPos.Index;
}

PlayerData* BulletData::Get_Target_From(void)
{
	return pTarget_From;
}

PlayerData* BulletData::Get_Target_OnHit(void)
{
	return pTarget_OnHit;
}

BulletState BulletData::Get_BulletState(void)
{
	return eBulletState;
}

BulletMoveCoor BulletData::Get_BulletMoveCoor(void)
{
	return sBulletMoveCoor;
}

LPDIRECT3DTEXTURE9 BulletData::Get_Texture(void)
{
	return pBulletTexPtr;
}

bool BulletData::UpdateCircleBullet(void)
{
	if ((sCircleBulletPos.pCircle != NULL) && (spBulletPolygon != NULL))
	{
		sBulletMoveCoor.x = sCircleBulletPos.pCircle->sCircleFormat[sCircleBulletPos.Index].position.x;
		sBulletMoveCoor.y = sCircleBulletPos.pCircle->sCircleFormat[sCircleBulletPos.Index].position.y;
		spBulletPolygon->CentrePoint.x = sBulletMoveCoor.x;
		spBulletPolygon->CentrePoint.y = sBulletMoveCoor.y;

		UpdatePolygon(spBulletPolygon);

		if ((spBulletPolygon->CentrePoint.y > WINDOW_HEIGHT) || (spBulletPolygon->CentrePoint.y < 0))
		{
			return FALSE;
		}
		if ((spBulletPolygon->CentrePoint.x > WINDOW_WIDTH) || (spBulletPolygon->CentrePoint.x < 0))
		{
			return FALSE;
		}
		return TRUE;
	}
	return TRUE;
}

void BulletData::OnBomb(void)
{
	double x = spBulletPolygon->CentrePoint.x;
	double y = spBulletPolygon->CentrePoint.y;
	double Width = (GetTextureWidth(BULLETBOMB)) / GetTextureFPSCount(BULLETBOMB);
	double Height = (GetTextureHeight(BULLETBOMB)) / 2.0f;
	if (spBulletPolygon != NULL)
	{
		if (spBulletPolygon->TextureFormat != NULL)
		{
			delete[]spBulletPolygon->TextureFormat;
			spBulletPolygon->TextureFormat = NULL;
		}

		delete spBulletPolygon;
		spBulletPolygon = NULL;
	}
	spBulletPolygon = CreateSquarePolygon(0, x, y, Width, Height);
	pBulletTexPtr = GetTexture(BULLETBOMB);
	sBulletMoveCoor.x = spBulletPolygon->CentrePoint.x;
	sBulletMoveCoor.y = spBulletPolygon->CentrePoint.y;
	sBulletMoveCoor.HorizontalSpeed = 0;
	sBulletMoveCoor.VerticalSpeed = 0;
	pTarget_From = NULL;
	pTarget_OnHit = NULL;
	sCircleBulletPos.pCircle = NULL;
	sCircleBulletPos.Index = 0;
	spBulletPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.0f, 0.0f);
	spBulletPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.125f, 0.0f);
	spBulletPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.0f, 0.5f);
	spBulletPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.125f, 0.5f);
}

void BulletData::BombAnimation(void)
{
	UINT CountX = iOnAnimationCount % BULLET_TEXTURE_U;
	UINT CountY = iOnAnimationCount / BULLET_TEXTURE_U;
	switch (eBulletState)
	{
	case BS_Bomb:

		spBulletPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2((CountX * (0.125f)), (CountY * (0.5f)));
		spBulletPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(((CountX + 1) * (0.125f)), (CountY * (0.5f)));
		spBulletPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2((CountX * (0.125f)), ((CountY + 1) * (0.5f)));
		spBulletPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(((CountX + 1) * (0.125f)), ((CountY + 1) * (0.5f)));

		iOnAnimationCount = (iOnAnimationCount + 1) % iAnimationCount;
		if (iOnAnimationCount == ((BULLET_TEXTURE_U * BULLET_TEXTURE_V) - 1))
		{
			eBulletState = BS_BombOver;
			iOnAnimationCount = 0;
		}
		break;
	case BS_BombOver:
		Release();
		break;
	}
}