#ifndef _BULLET_H
#define _BULLET_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <Windows.h>
#include <d3dx9.h>
#include "Polygon.h"
#include "Circle.h"
#include "Common.h"

class PlayerData;

typedef enum EBulletState {
	BS_None = 0,
	BS_PlayerImpact,
	BS_Bomb,
	BS_BombOver
}BulletState;

typedef struct SBulletMoveCoor {
	double x;
	double y;
	double HorizontalSpeed;
	double VerticalSpeed;
}BulletMoveCoor;

typedef struct SBulletDamage {
	double Damage;
}BulletDamage;

typedef struct SCircleBulletPos {
	VertexCircle* pCircle;
	UINT Index;
}CircleBulletPos;

class BulletData {

public:
	BulletData();
	BulletData::BulletData(UINT Index, double x, double y, LPDIRECT3DTEXTURE9 pTex, UINT Width, UINT Height, double bx, double by);
	~BulletData();

	SquarePolygon* Get_Polygon(void);

	void BulletData::Reset(UINT Index, double x, double y, LPDIRECT3DTEXTURE9 pTex, UINT Width, UINT Height, double bx, double by);

	void Move(void);
	void OnHit(PlayerData* pTarget);
	bool Update(void);
	
	void Release(void);

	void Set_CircleIndex(VertexCircle* pCircle, UINT Index);
	void Set_Target_From(PlayerData* pTarget);
	void Set_Target_OnHit(PlayerData* pTarget);
	void Set_BulletState(BulletState State);
	void Set_BulletMoveCoor(BulletMoveCoor Coor);
	void Set_Texture(LPDIRECT3DTEXTURE9 Texture);

	VertexCircle* Get_Circle(void);
	UINT Get_CircleIndex(void);
	PlayerData* Get_Target_From(void);
	PlayerData* Get_Target_OnHit(void);
	BulletState Get_BulletState(void);
	BulletMoveCoor Get_BulletMoveCoor(void);
	LPDIRECT3DTEXTURE9 Get_Texture(void);

	bool UpdateCircleBullet(void);
	void OnBomb(void);
	void BombAnimation(void);

protected:
	SquarePolygon* spBulletPolygon;
	LPDIRECT3DTEXTURE9 pBulletTexPtr;

	BulletState eBulletState;
	BulletMoveCoor sBulletMoveCoor;
	BulletDamage sBulletDamage;

	PlayerData* pTarget_From;
	PlayerData* pTarget_OnHit;

	CircleBulletPos sCircleBulletPos;

	UINT iOnAnimationCount = 0;
	UINT iAnimationCount = BULLET_TEXTURE_U * BULLET_TEXTURE_V;
};


#endif // !_BULLET_H