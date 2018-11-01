#ifndef _PLAYER_H
#define _PLAYER_H

#include <Windows.h>
#include "Animation.h"
#include "Common.h"
#include "Polygon.h"
#include "Texture.h"
#include "Bullet.h"


typedef enum ETextureNumber {
	TN_01 = 0,
	TN_02,
	TN_03,
	TN_04
}TextureNumber;

typedef enum EPlayerState {
	PS_None = 0,
	PS_MoveLeft = 1,
	PS_MoveRight,
	PS_MoveUp,
	PS_MoveDown,
	PS_MoveLeftUp,
	PS_MoveRightUp,
	PS_MoveLeftDown,
	PS_MoveRightDown
}PlayerState;

typedef enum EPlayerShoot {
	PSh_None = 0,
	PSh_Shoot
}PlayerShoot;

typedef enum EPlayerShootDirection {
	PSD_None = 0,
	PSD_Up,
	PSD_Down,
	PSD_Left,
	PSD_Right,
	PSD_LeftUp,
	PSD_RightUp,
	PSD_LeftDown,
	PSD_RightDown
}PlayerShootDirection;

typedef struct SPlayerMoveCoorData {
	double x;
	double y;
	double HorizontalWalkSpeed;
	double VerticalWalkSpeed;
	double RunSpeed;
}PlayerMoveCoor;

typedef struct SPlayerProperty {
	double fHP;
	double fHP_Max;
	double ATK;
	double ATK_Max;
}PlayerProperty;

class PlayerData {

public:
	PlayerData();
	PlayerData(SquarePolygon* spPolygon, LPDIRECT3DTEXTURE9 pTex, PlayerProperty sProperty);
	~PlayerData();

	void PlayerMoveAnimation(void);
	void UpdatePlayerState(PlayerData* pTarget);
	void PlayerAction(void);
	void OnPlayerShoot(PlayerData* pTarget_From);
	void OnHurt_Bullet(PlayerData* pTarget_From);

	void Release(void);

	void Set_PlayerMoveCoor(PlayerMoveCoor* MoveCoor);
	void Set_PlayerState(PlayerState State);
	void Set_PlayerShoot(PlayerShoot Shoot);
	void Set_PlayerDirection(PlayerShootDirection Direction);
	void Set_PlayerCoorX(double x);
	void Set_PlayerCoorY(double y);
	void Set_PlayerHorizontalWalkSpeed(double SpeedX);
	void Set_PlayerVerticalWalkSpeed(double SpeedY);
	void Set_PlayerRunSpeed(double SpeedRun);
	void Set_TexturePos(TextureNumber Index, D3DXVECTOR2 TexPos);
	void Set_PlayerProperty(PlayerProperty sProperty);

	SquarePolygon* Get_PlayerPolygon(void);
	LPDIRECT3DTEXTURE9 Get_PlayerTexPtr(void);
	BulletData* Get_PlayerBullet(UINT Index);
	PlayerState Get_PlayerState(void);
	PlayerShoot Get_PlayerShoot(void);
	PlayerShootDirection Get_PlayerDirection(void);
	PlayerMoveCoor Get_PlayerMoveCoor(void);
	D3DXVECTOR2 Get_TexturePos(TextureNumber Index);
	PlayerProperty Get_PlayerProperty(void);
	double Get_PlayerCoorX(void);
	double Get_PlayerCoorY(void);
	double Get_PlayerCoorHorizontalWalkSpeed(void);

private:
	SquarePolygon* spPlayerPolygon;
	LPDIRECT3DTEXTURE9 pPlayerTexPtr;

	PlayerState ePlayerState;
	PlayerMoveCoor sPlayerMoveCoor;
	PlayerProperty sPlayerProperty;
	PlayerShoot ePlayerShoot;
	PlayerShootDirection ePlayerShootDirection;

	BulletData* pBulletPool[PLAYER_BULLETPOOL_COUNT];
};


#endif // !_PLAYER_H