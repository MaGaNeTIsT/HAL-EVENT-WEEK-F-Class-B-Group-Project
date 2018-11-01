#ifndef _BULLETMAP_H
#define _BULLETMAP_H

#include "Circle.h"
#include "Player.h"
#include "Bullet.h"

class BulletData;

typedef enum EStraightBulletDirect {
	ESBD_Horizontal = 0,
	ESBD_Vertical
}StraightBulletDirect;

typedef struct SStraightBulletData {
	int iLauncherTimeInterval;
	int iOnLauncher;
	BulletData* pStraightBullet;
	int* pExist;
	double fStartX;
	double fStartY;
	double fDistance;
	StraightBulletDirect eDirect;
}StraightBulletData;


VertexCircle* CreateCircleBullet(double X, double Y);
void UpdateCircleBullet(VertexCircle* pCircleBullet, double fExpandSpeed);
void RandomBullet_Initialize(PlayerData* pTarget_From, PlayerData* pTarget);
void UpdateRandomBullet(PlayerData* pTarget);
BulletData* Get_BulletCircle(UINT Index);
VertexCircle* Get_Circle(UINT Index);
BulletData** Get_ppBulletCircle(UINT Index);
VertexCircle** Get_ppCircle(UINT Index);
void BulletCircle_Initialize(void);

void BulletStraight_Initialize(void);
void BulletStraight_Create(int Interval, int OnLauncher, double X, double Y, double Distance, StraightBulletDirect Direct, double Speed, PlayerData* pTarget_From, PlayerData* pTarget_OnHit);
void BulletStraight_Update(PlayerData* pTarget);
void BulletStraight_Delete(StraightBulletData* &pStraightBullet);
void BulletStraight_Render(void);
void BulletStraight_BombAnimation(void);
void BulletStraight_Finalize(void);

#endif // !_BULLETMAP_H