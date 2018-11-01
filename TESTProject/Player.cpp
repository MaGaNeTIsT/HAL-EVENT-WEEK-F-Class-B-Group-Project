#include "Player.h"
#include "Polygon.h"
#include "sound.h"

PlayerData::PlayerData()
{
	spPlayerPolygon = NULL;
	pPlayerTexPtr = NULL;
	ePlayerState = PS_None;
	sPlayerMoveCoor.HorizontalWalkSpeed = PLAYER_MOVEX;
	sPlayerMoveCoor.RunSpeed = PLAYER_RUNSPEED;
	sPlayerMoveCoor.VerticalWalkSpeed = PLAYER_MOVEX;
	sPlayerMoveCoor.x = 0;
	sPlayerMoveCoor.y = 0;
	ePlayerShoot = PSh_None;
	ePlayerShootDirection = PSD_None;
	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		pBulletPool[i] = NULL;
	}
	sPlayerProperty.ATK = PLAYER_PROPERTY_ATK;
	sPlayerProperty.ATK_Max = PLAYER_PROPERTY_ATK;
	sPlayerProperty.fHP = PLAYER_PROPERTY_HP;
	sPlayerProperty.fHP_Max = PLAYER_PROPERTY_HP;
}

PlayerData::PlayerData(SquarePolygon* spPolygon, LPDIRECT3DTEXTURE9 pTex, PlayerProperty sProperty)
{
	spPlayerPolygon = spPolygon;
	pPlayerTexPtr = pTex;
	ePlayerState = PS_None;
	sPlayerMoveCoor.HorizontalWalkSpeed = PLAYER_MOVEX;
	sPlayerMoveCoor.RunSpeed = PLAYER_RUNSPEED;
	sPlayerMoveCoor.VerticalWalkSpeed = PLAYER_MOVEX;
	sPlayerMoveCoor.x = spPlayerPolygon->CentrePoint.x;
	sPlayerMoveCoor.y = spPlayerPolygon->CentrePoint.y;
	ePlayerShoot = PSh_None;
	ePlayerShootDirection = PSD_None;
	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		pBulletPool[i] = NULL;
	}
	sPlayerProperty.ATK = sProperty.ATK;
	sPlayerProperty.ATK_Max = sProperty.ATK_Max;
	sPlayerProperty.fHP = sProperty.fHP;
	sPlayerProperty.fHP_Max = sProperty.fHP_Max;
}

PlayerData::~PlayerData()
{
	DestoryPolygon(spPlayerPolygon);
	pPlayerTexPtr = NULL;
	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		if (pBulletPool[i] != NULL)
		{
			delete pBulletPool[i];
			pBulletPool[i] = NULL;
		}
	}
}

void PlayerData::Release(void)
{
	DestoryPolygon(spPlayerPolygon);
	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		if (pBulletPool[i] != NULL)
		{
			delete pBulletPool[i];
			pBulletPool[i] = NULL;
		}
	}
}

void PlayerData::Set_PlayerMoveCoor(PlayerMoveCoor* MoveCoor)
{
	sPlayerMoveCoor.HorizontalWalkSpeed = MoveCoor->HorizontalWalkSpeed;
	sPlayerMoveCoor.RunSpeed = MoveCoor->RunSpeed;
	sPlayerMoveCoor.VerticalWalkSpeed = MoveCoor->VerticalWalkSpeed;
	sPlayerMoveCoor.x = MoveCoor->x;
	sPlayerMoveCoor.y = MoveCoor->y;
}

void PlayerData::Set_TexturePos(TextureNumber Index, D3DXVECTOR2 TexPos)
{
	spPlayerPolygon->TextureFormat[Index].TextureCoor = TexPos;
}

void PlayerData::Set_PlayerCoorX(double x)
{
	sPlayerMoveCoor.x = x;
}

void PlayerData::Set_PlayerCoorY(double y)
{
	sPlayerMoveCoor.y = y;
}

void PlayerData::Set_PlayerHorizontalWalkSpeed(double SpeedX)
{
	sPlayerMoveCoor.HorizontalWalkSpeed = SpeedX;
}

void PlayerData::Set_PlayerVerticalWalkSpeed(double SpeedY)
{
	sPlayerMoveCoor.VerticalWalkSpeed = SpeedY;
}

void PlayerData::Set_PlayerRunSpeed(double SpeedRun)
{
	sPlayerMoveCoor.RunSpeed = SpeedRun;
}

void PlayerData::Set_PlayerState(PlayerState State)
{
	ePlayerState = State;
}

void PlayerData::Set_PlayerShoot(PlayerShoot Shoot)
{
	ePlayerShoot = Shoot;
}

void PlayerData::Set_PlayerDirection(PlayerShootDirection Direction)
{
	ePlayerShootDirection = Direction;
}

void PlayerData::Set_PlayerProperty(PlayerProperty sProperty)
{
	sPlayerProperty.ATK = sProperty.ATK;
	sPlayerProperty.ATK_Max = sProperty.ATK_Max;
	sPlayerProperty.fHP = sProperty.fHP;
	sPlayerProperty.fHP_Max = sProperty.fHP_Max;
}

SquarePolygon* PlayerData::Get_PlayerPolygon(void)
{
	return spPlayerPolygon;
}

LPDIRECT3DTEXTURE9 PlayerData::Get_PlayerTexPtr(void)
{
	return pPlayerTexPtr;
}

PlayerState PlayerData::Get_PlayerState(void)
{
	return ePlayerState;
}

PlayerShoot PlayerData::Get_PlayerShoot(void)
{
	return ePlayerShoot;
}

BulletData* PlayerData::Get_PlayerBullet(UINT Index)
{
	return pBulletPool[Index];
}

PlayerShootDirection PlayerData::Get_PlayerDirection(void)
{
	return ePlayerShootDirection;
}

PlayerMoveCoor PlayerData::Get_PlayerMoveCoor(void)
{
	return sPlayerMoveCoor;
}

double PlayerData::Get_PlayerCoorX(void)
{
	return sPlayerMoveCoor.x;
}

double PlayerData::Get_PlayerCoorY(void)
{
	return sPlayerMoveCoor.y;
}

double PlayerData::Get_PlayerCoorHorizontalWalkSpeed(void)
{
	return sPlayerMoveCoor.HorizontalWalkSpeed;
}

D3DXVECTOR2 PlayerData::Get_TexturePos(TextureNumber Index)
{
	return (spPlayerPolygon->TextureFormat[Index].TextureCoor);
}

PlayerProperty PlayerData::Get_PlayerProperty(void)
{
	return sPlayerProperty;
}

void PlayerData::UpdatePlayerState(PlayerData* pTarget)
{
	PlayerAction();

	spPlayerPolygon->CentrePoint.x = sPlayerMoveCoor.x;
	spPlayerPolygon->CentrePoint.y = sPlayerMoveCoor.y;

	UpdatePolygon(spPlayerPolygon);

	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		if (pBulletPool[i] != NULL)
		{
			if (pBulletPool[i]->Update() == FALSE)
			{
				if (pBulletPool[i] != NULL)
				{
					delete pBulletPool[i];
					pBulletPool[i] = NULL;
				}
			}
		}
	}

	///////////////////////////////////////////////////////////////////////
	if (ePlayerState == PS_None)
	{
		PlayerMoveAnimation();
	}
	for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	{
		if ((pBulletPool[i] != NULL))
		{
			if ((pBulletPool[i]->Get_Polygon()) != NULL)
			{
				switch (pBulletPool[i]->Get_BulletState())
				{
				case BS_Bomb:
					break;
				case BS_BombOver:
					delete pBulletPool[i];
					pBulletPool[i] = NULL;
					break;
				default:
					if (pTarget != NULL)
					{
						pBulletPool[i]->OnHit(pTarget);
					}
					break;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////

	ePlayerState = PS_None;
	ePlayerShoot = PSh_None;
	//ePlayerShootDirection = PSD_None;
}

void PlayerData::PlayerMoveAnimation(void)
{
	switch (ePlayerState)
	{
	case PS_None:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.0f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.8f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);

		break;
	case PS_MoveLeft:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.0f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.0f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);

		break;
	case PS_MoveRight:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(1.0f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(1.0f, 1.0f);

		break;
	case PS_MoveUp:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.0f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.8f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);

		break;
	case PS_MoveDown:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.0f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.8f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);

		break;
	case PS_MoveLeftUp:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.0f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.0f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);

		break;
	case PS_MoveRightUp:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(1.0f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(1.0f, 1.0f);

		break;
	case PS_MoveLeftDown:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.4f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.4f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.0f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.2f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.0f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.2f, 1.0f);

		break;
	case PS_MoveRightDown:

		if ((spPlayerPolygon->TextureFormat[0].TextureCoor) == D3DXVECTOR2(0.4f, 0.0f))
		{
			spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.6f, 0.0f);
			spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
			spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.6f, 1.0f);
			spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
			break;
		}
		spPlayerPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(0.8f, 0.0f);
		spPlayerPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(1.0f, 0.0f);
		spPlayerPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(0.8f, 1.0f);
		spPlayerPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(1.0f, 1.0f);

		break;
	}
}

void PlayerData::PlayerAction(void)
{
	switch (ePlayerState)
	{
	case PS_None:

		break;
	case PS_MoveLeft:
		sPlayerMoveCoor.x -= sPlayerMoveCoor.HorizontalWalkSpeed;
		break;
	case PS_MoveRight:
		sPlayerMoveCoor.x += sPlayerMoveCoor.HorizontalWalkSpeed;
		break;
	case PS_MoveUp:
		sPlayerMoveCoor.y -= sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	case PS_MoveDown:
		sPlayerMoveCoor.y += sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	case PS_MoveLeftUp:
		sPlayerMoveCoor.x -= sPlayerMoveCoor.HorizontalWalkSpeed;
		sPlayerMoveCoor.y -= sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	case PS_MoveRightUp:
		sPlayerMoveCoor.x += sPlayerMoveCoor.HorizontalWalkSpeed;
		sPlayerMoveCoor.y -= sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	case PS_MoveLeftDown:
		sPlayerMoveCoor.x -= sPlayerMoveCoor.HorizontalWalkSpeed;
		sPlayerMoveCoor.y += sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	case PS_MoveRightDown:
		sPlayerMoveCoor.x += sPlayerMoveCoor.HorizontalWalkSpeed;
		sPlayerMoveCoor.y += sPlayerMoveCoor.VerticalWalkSpeed;
		break;
	}
}

void PlayerData::OnPlayerShoot(PlayerData* pTarget_From)
{
	if (ePlayerShoot == PSh_Shoot)
	{
		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
		{
			if (pBulletPool[i] == NULL)
			{
				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(BULLETPLAYER), BULLET_WIDTH, BULLET_HEIGHT, 0, ((BULLET_MOVEY) * (-1)));
				pBulletPool[i]->Set_Target_From(pTarget_From);
				PlaySound(SOUND_LABEL_SE_SHOT);
				ePlayerShoot == PSh_None;
				return;
			}
		}
	}

		ePlayerShoot == PSh_None;
		return;

	//if (ePlayerShoot == PSh_Shoot)
	//{
	//	switch (ePlayerShootDirection)
	//	{
	//	case PSD_None:

	//		break;
	//	case PSD_Up:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, 0, ((BULLET_MOVEY) * (-1)));
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_Down:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, 0, BULLET_MOVEY);
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_Left:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, ((BULLET_MOVEX) * (-1)), 0);
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_Right:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, BULLET_MOVEX, 0);
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_LeftUp:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, ((BULLET_MOVEX) * (-1)), ((BULLET_MOVEY) * (-1)));
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_RightUp:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, BULLET_MOVEX, ((BULLET_MOVEY) * (-1)));
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_LeftDown:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, ((BULLET_MOVEX) * (-1)), BULLET_MOVEY);
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	case PSD_RightDown:

	//		for (int i = 0; i < PLAYER_BULLETPOOL_COUNT; i++)
	//		{
	//			if (pBulletPool[i] == NULL)
	//			{
	//				pBulletPool[i] = new BulletData(i, sPlayerMoveCoor.x, sPlayerMoveCoor.y, GetTexture(4), BULLET_WIDTH, BULLET_HEIGHT, BULLET_MOVEX, BULLET_MOVEY);
	//				ePlayerShoot == PSh_None;
	//				return;
	//			}
	//		}

	//		break;
	//	}

	//	ePlayerShoot == PSh_None;
	//	return;
	//}
}

void PlayerData::OnHurt_Bullet(PlayerData* pTarget_From)
{
	sPlayerProperty.fHP -= pTarget_From->Get_PlayerProperty().ATK;
	PlaySound(SOUND_LABEL_SE_HIT);
}