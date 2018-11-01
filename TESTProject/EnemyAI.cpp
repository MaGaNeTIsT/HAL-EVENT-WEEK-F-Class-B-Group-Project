#include "EnemyAI.h"
#include "Texture.h"

static UINT iOnAnimationCount = 0;
static const UINT iAnimationCount = BOSS_TEXTURE_U * BOSS_TEXTURE_V;

bool InitBoss(PlayerData* Chara)
{
	PlayerMoveCoor* Coor = NULL;
	Coor = new PlayerMoveCoor;
	Coor->HorizontalWalkSpeed = BOSS_MOVEX;
	Coor->RunSpeed = Chara->Get_PlayerMoveCoor().RunSpeed;
	Coor->VerticalWalkSpeed = BOSS_MOVEY;
	Coor->x = Chara->Get_PlayerMoveCoor().x;
	Coor->y = Chara->Get_PlayerMoveCoor().y;
	Chara->Set_PlayerMoveCoor(Coor);
	delete Coor;
	Coor = NULL;

	Chara->Set_PlayerState(PS_MoveLeft);
	Chara->Set_PlayerDirection(PSD_Left);

	return TRUE;
}

void UpdateBoss(PlayerData* Chara, PlayerData* pTarget)
{
	double x = Chara->Get_PlayerCoorX();
	switch (Chara->Get_PlayerDirection())
	{
	case PSD_Left:
		Chara->Set_PlayerState(PS_MoveLeft);
		break;
	case PSD_Right:
		Chara->Set_PlayerState(PS_MoveRight);
		break;
	}
	if ((x <= 0) || (x >= WINDOW_WIDTH))
	{
		switch (Chara->Get_PlayerState())
		{
		case PS_MoveLeft:
			Chara->Set_PlayerDirection(PSD_Right);
			Chara->Set_PlayerState(PS_MoveRight);
			break;
		case PS_MoveRight:
			Chara->Set_PlayerDirection(PSD_Left);
			Chara->Set_PlayerState(PS_MoveLeft);
			break;
		}
	}
	Chara->UpdatePlayerState(pTarget);
}

void AnimationBoss(PlayerData* Chara)
{
	UINT CountX = iOnAnimationCount % BOSS_TEXTURE_U;
	UINT CountY = iOnAnimationCount / BOSS_TEXTURE_U;

	Chara->Set_TexturePos(TN_01, D3DXVECTOR2((CountX * (0.2f)), (CountY * (0.5f))));
	Chara->Set_TexturePos(TN_02, D3DXVECTOR2(((CountX + 1) * (0.2f)), (CountY * (0.5f))));
	Chara->Set_TexturePos(TN_03, D3DXVECTOR2((CountX * (0.2f)), ((CountY + 1) * (0.5f))));
	Chara->Set_TexturePos(TN_04, D3DXVECTOR2(((CountX + 1) * (0.2f)), ((CountY + 1) * (0.5f))));

	iOnAnimationCount = (iOnAnimationCount + 1) % iAnimationCount;

	switch (Chara->Get_PlayerDirection())
	{
	case PSD_Left:

		break;
	case PSD_Right:
		D3DXVECTOR2 Buffer = Chara->Get_PlayerPolygon()->TextureFormat[0].TextureCoor;
		Chara->Set_TexturePos(TN_01, Chara->Get_PlayerPolygon()->TextureFormat[1].TextureCoor);
		Chara->Set_TexturePos(TN_02, Buffer);
		Buffer = Chara->Get_PlayerPolygon()->TextureFormat[2].TextureCoor;
		Chara->Set_TexturePos(TN_03, Chara->Get_PlayerPolygon()->TextureFormat[3].TextureCoor);
		Chara->Set_TexturePos(TN_04, Buffer);
		break;
	}
}