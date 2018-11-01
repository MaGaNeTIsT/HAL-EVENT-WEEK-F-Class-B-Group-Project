#include "BulletMap.h"
#include "Bullet.h"
#include "Time.h"
#include "Common.h"
#include "Circle.h"
#include "MyDirect.h"

static BulletData* pBulletCircle[BULLET_CIRCLE_POOL];
static VertexCircle* pCircle[BULLET_CIRCLE_POOL];
static StraightBulletData** ppStraightBullet = NULL;

BulletData* Get_BulletCircle(UINT Index)
{
	return pBulletCircle[Index];
}

VertexCircle* Get_Circle(UINT Index)
{
	return pCircle[Index];
}

BulletData** Get_ppBulletCircle(UINT Index)
{
	BulletData** ppBulletCircle = &(pBulletCircle[Index]);
	return ppBulletCircle;
}

VertexCircle** Get_ppCircle(UINT Index)
{
	VertexCircle** ppCircle = &(pCircle[Index]);
	return ppCircle;
}

void BulletCircle_Initialize(void)
{
	for (int i = 0; i < BULLET_CIRCLE_POOL; i++)
	{
		pBulletCircle[i] = NULL;
		pCircle[i] = NULL;
	}
}

VertexCircle* CreateCircleBullet(double X, double Y)
{
	VertexCircle* pCircleBullet = NULL;
	//srand((unsigned)time(NULL));
	//UINT iSeedX = (rand() % (CIRECLEBULLET_POS_X)) + ((WINDOW_WIDTH - CIRECLEBULLET_POS_X) / 2);
	//UINT iSeedY = (rand() % (CIRECLEBULLET_POS_Y)) + ((WINDOW_HEIGHT - CIRECLEBULLET_POS_Y) / 2);
	double fSeedRollSpeed = ((rand() % (BALL_ROLL_SEED)) / 10.0f) + BALL_ROLL_SPEED;
	pCircleBullet = CreateCircle(X, Y, 1.0f, BULLET_COUNT_CIRCLE, fSeedRollSpeed);

	return pCircleBullet;
}

void UpdateCircleBullet(VertexCircle* pCircleBullet, double fExpandSpeed)
{
	pCircleBullet->fCircleRadius += fExpandSpeed;

	DoRollCircle(pCircleBullet);
}

void RandomBullet_Initialize(PlayerData* pTarget_From, PlayerData* pTarget)
{
	for (int i = 0; i < BULLET_CIRCLE_POOL; i++)
	{
		if (pBulletCircle[i] == NULL)
		{
			if (pCircle[i] != NULL)
			{
				break;
			}
			pCircle[i] = CreateCircleBullet(10, 10);
			UpdateCircleBullet(pCircle[i], BULLET_CIRCLE_SPEED);
			pBulletCircle[i] = new BulletData[BULLET_COUNT_CIRCLE];
			for (int Index = 0; Index < BULLET_COUNT_CIRCLE; Index++)
			{
				pBulletCircle[i][Index].Set_CircleIndex(pCircle[i], (Index + 1));
				pBulletCircle[i][Index].UpdateCircleBullet();
				pBulletCircle[i][Index].Set_Target_From(pTarget_From);
				pBulletCircle[i][Index].Set_Target_OnHit(pTarget);
			}
			return;
		}
	}
}

void UpdateRandomBullet(PlayerData* pTarget)
{
	for (int i = 0; i < BULLET_CIRCLE_POOL; i++)
	{
		if (pCircle[i] != NULL)
		{
			if (pCircle[i]->fCircleRadius >= WINDOW_WIDTH)
			{
				DestoryCircle(pCircle[i]);
				delete[] pBulletCircle[i];
				pBulletCircle[i] = NULL;
			}
		}
		if (pCircle[i] != NULL)
		{
			UpdateCircleBullet(pCircle[i], BULLET_CIRCLE_SPEED);
			for (int Index = 0; Index < BULLET_COUNT_CIRCLE; Index++)
			{
				if ((pBulletCircle[i][Index].Get_Polygon()) != NULL)
				{
					pBulletCircle[i][Index].UpdateCircleBullet();
					pBulletCircle[i][Index].OnHit(pTarget);
				}
			}
		}
	}
}

void BulletStraight_Initialize(void)
{
	ppStraightBullet = new StraightBulletData*[STRAIGHT_BULLET_COUNT];
	for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
	{
		ppStraightBullet[i] = NULL;
	}
}

void BulletStraight_Create(int Interval, int OnLauncher, double X, double Y, double Distance, StraightBulletDirect Direct, double Speed, PlayerData* Target_From, PlayerData* Target_OnHit)
{
	for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
	{
		if (ppStraightBullet[i] == NULL)
		{
			ppStraightBullet[i] = new StraightBulletData;
			ppStraightBullet[i]->iLauncherTimeInterval = Interval;
			ppStraightBullet[i]->iOnLauncher = OnLauncher;
			ppStraightBullet[i]->fStartX = X;
			ppStraightBullet[i]->fStartY = Y;
			ppStraightBullet[i]->fDistance = Distance;
			ppStraightBullet[i]->eDirect = Direct;
			ppStraightBullet[i]->pStraightBullet = new BulletData[STRAIGHT_BULLET_MEMBER_COUNT];
			ppStraightBullet[i]->pExist = new int[STRAIGHT_BULLET_MEMBER_COUNT];
			for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
			{
				ppStraightBullet[i]->pExist[n] = 0;
				ppStraightBullet[i]->pStraightBullet[n].Set_Target_From(Target_From);
				ppStraightBullet[i]->pStraightBullet[n].Set_Target_OnHit(Target_OnHit);
				BulletMoveCoor Coor;
				Coor.x = X;
				Coor.y = Y;
				switch (Direct)
				{
				case ESBD_Horizontal:
					Coor.VerticalSpeed = 0;
					Coor.HorizontalSpeed = Speed;
					break;
				case ESBD_Vertical:
					Coor.VerticalSpeed = Speed;
					Coor.HorizontalSpeed = 0;
					break;
				}
				ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
			}
			return;
		}
	}
}

void BulletStraight_Update(PlayerData* pTarget)
{
	for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
	{
		if (ppStraightBullet[i] != NULL)
		{
			if (ppStraightBullet[i]->iOnLauncher == 0)
			{
				switch (ppStraightBullet[i]->eDirect)
				{
				case ESBD_Horizontal:
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed == 0)
					{
						for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
						{
							if (!ppStraightBullet[i]->pExist[n])
							{
								ppStraightBullet[i]->pExist[n] = 1;
								break;
							}
						}
					}
					break;
				case ESBD_Vertical:
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed == 0)
					{
						for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
						{
							if (!ppStraightBullet[i]->pExist[n])
							{
								ppStraightBullet[i]->pExist[n] = 1;
								break;
							}
						}
					}
					break;
				}

				if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed == 0) && (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed == 0))
				{
					BulletMoveCoor Coor;
					switch (ppStraightBullet[i]->eDirect)
					{
					case ESBD_Horizontal:
						if (ppStraightBullet[i]->fStartY > (WINDOW_HEIGHT / 2))
						{
							Coor.VerticalSpeed = 0 - STRAIGHT_BULLET_MEMBER_SPEED;
						}
						else
						{
							Coor.VerticalSpeed = STRAIGHT_BULLET_MEMBER_SPEED;
						}
						Coor.HorizontalSpeed = 0;
						for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
						{
							if (ppStraightBullet[i]->pExist[n])
							{
								Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
								Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
								ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
							}
						}
						break;
					case ESBD_Vertical:
						Coor.VerticalSpeed = 0;
						if (ppStraightBullet[i]->fStartX > (WINDOW_WIDTH / 2))
						{
							Coor.HorizontalSpeed = 0 - STRAIGHT_BULLET_MEMBER_SPEED;
						}
						else
						{
							Coor.HorizontalSpeed = STRAIGHT_BULLET_MEMBER_SPEED;
						}
						for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
						{
							if (ppStraightBullet[i]->pExist[n])
							{
								Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
								Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
								ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
							}
						}
						break;
					}
				}

				switch (ppStraightBullet[i]->eDirect)
				{
				case ESBD_Horizontal:
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed > 0)
					{
						if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().x > (ppStraightBullet[i]->fStartX + ppStraightBullet[i]->fDistance)) && (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed != 0))
						{
							BulletMoveCoor Coor;
							Coor.VerticalSpeed = 0;
							Coor.HorizontalSpeed = 0;
							for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
							{
								if (ppStraightBullet[i]->pExist[n])
								{
									Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
									Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
									ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
								}
							}
						}
					}
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed < 0)
					{
						if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().x < (ppStraightBullet[i]->fStartX + ppStraightBullet[i]->fDistance)) && (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().HorizontalSpeed != 0))
						{
							BulletMoveCoor Coor;
							Coor.VerticalSpeed = 0;
							Coor.HorizontalSpeed = 0;
							for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
							{
								if (ppStraightBullet[i]->pExist[n])
								{
									Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
									Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
									ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
								}
							}
						}
					}
					break;
				case ESBD_Vertical:
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed > 0)
					{
						if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().y > (ppStraightBullet[i]->fStartY + ppStraightBullet[i]->fDistance)) && (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed != 0))
						{
							BulletMoveCoor Coor;
							Coor.VerticalSpeed = 0;
							Coor.HorizontalSpeed = 0;
							for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
							{
								if (ppStraightBullet[i]->pExist[n])
								{
									Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
									Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
									ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
								}
							}
						}
					}
					if (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed < 0)
					{
						if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().y < (ppStraightBullet[i]->fStartY + ppStraightBullet[i]->fDistance)) && (ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().VerticalSpeed != 0))
						{
							BulletMoveCoor Coor;
							Coor.VerticalSpeed = 0;
							Coor.HorizontalSpeed = 0;
							for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
							{
								if (ppStraightBullet[i]->pExist[n])
								{
									Coor.x = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().x;
									Coor.y = ppStraightBullet[i]->pStraightBullet[n].Get_BulletMoveCoor().y;
									ppStraightBullet[i]->pStraightBullet[n].Set_BulletMoveCoor(Coor);
								}
							}
						}
					}
					break;
				}
			}

			ppStraightBullet[i]->iOnLauncher = (ppStraightBullet[i]->iOnLauncher + 1) % (ppStraightBullet[i]->iLauncherTimeInterval);

			for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
			{
				if (ppStraightBullet[i]->pExist[n])
				{
					ppStraightBullet[i]->pStraightBullet[n].Update();
					ppStraightBullet[i]->pStraightBullet[n].OnHit(pTarget);
				}
			}

			switch (ppStraightBullet[i]->eDirect)
			{
			case ESBD_Horizontal:
				if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().y > WINDOW_HEIGHT) || ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().y < 0)))
				{
					BulletStraight_Delete(ppStraightBullet[i]);
				}
				break;
			case ESBD_Vertical:
				if ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().x > WINDOW_WIDTH) || ((ppStraightBullet[i]->pStraightBullet[0].Get_BulletMoveCoor().x < 0)))
				{
					BulletStraight_Delete(ppStraightBullet[i]);
				}
				break;
			}
		}
	}
}

void BulletStraight_Delete(StraightBulletData* &pStraightBullet)
{
	if (pStraightBullet != NULL)
	{
		if (pStraightBullet->pStraightBullet != NULL)
		{
			delete[](pStraightBullet->pStraightBullet);
			pStraightBullet->pStraightBullet = NULL;
		}
		if (pStraightBullet->pExist != NULL)
		{
			delete[](pStraightBullet->pExist);
			pStraightBullet->pExist = NULL;
		}
		delete pStraightBullet;
		pStraightBullet = NULL;
	}
}

void BulletStraight_Render(void)
{
	for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
	{
		if (ppStraightBullet[i] != NULL)
		{
			for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
			{
				if (ppStraightBullet[i]->pExist[n])
				{
					if (ppStraightBullet[i]->pStraightBullet[n].Get_Polygon() != NULL)
					{
						if ((OnTexture(ppStraightBullet[i]->pStraightBullet[n].Get_Texture())) == TRUE)
						{
							Draw((ppStraightBullet[i]->pStraightBullet[n].Get_Polygon()->TextureFormat), D3DPT_TRIANGLESTRIP, 2);
						}
					}
				}
			}
		}
	}
}

void BulletStraight_BombAnimation(void)
{
	for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
	{
		if (ppStraightBullet[i] != NULL)
		{
			for (int n = 0; n < STRAIGHT_BULLET_MEMBER_COUNT; n++)
			{
				if (ppStraightBullet[i]->pExist[n])
				{
					ppStraightBullet[i]->pStraightBullet[n].BombAnimation();
				}
			}
		}
	}
}

void BulletStraight_Finalize(void)
{
	if (ppStraightBullet != NULL)
	{
		for (int i = 0; i < STRAIGHT_BULLET_COUNT; i++)
		{
			BulletStraight_Delete(ppStraightBullet[i]);
		}
		delete[]ppStraightBullet;
		ppStraightBullet = NULL;
	}
}