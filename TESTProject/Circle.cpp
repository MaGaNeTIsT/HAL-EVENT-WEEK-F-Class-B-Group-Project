#include "Circle.h"
#include "Common.h"

VertexCircle* CreateCircle(double CircleX, double CircleY, double CircleRadius, double FormatCount, double RollSpeed)
{
	VertexCircle* Circle;
	double fAngle = (PI / 180.0f);
	double rad = (360.0f / FormatCount);
	double fFormatRad = 0.0f;
	double fAngleFormat = 0.0f;
	double Cx = 0.0f;
	double Cy = 0.0f;

	Circle = new VertexCircle;

	Circle->fCircleRadius = CircleRadius;
	Circle->fAngle = BALL_ANGLE;
	Circle->fRollSpeed = RollSpeed;
	Circle->fCircleFormatCount = FormatCount;
	Circle->fMoveSpeedX = BALL_SPEEDX;
	Circle->fMoveSpeedY = BALL_SPEEDY;
	Circle->bImpactState = CIS_NONE;
	Circle->bImpact = FALSE;
	Circle->bCircleImapct = CCIS_NONE;
	Circle->fMass = (0.1f) * CircleRadius;

	Circle->sCircleFormat = new Vertex2D[((int)(FormatCount + 2.0f))];

	Circle->sCircleFormat[0].position = D3DXVECTOR4(CircleX, CircleY, 1.0f, 1.0f);
	Circle->sCircleFormat[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	for (int iFormatCnt = 0; iFormatCnt < ((int)(Circle->fCircleFormatCount)); iFormatCnt++)
	{
		fAngleFormat = (Circle->fAngle + (((double)(iFormatCnt)) * rad));
		if (fAngleFormat >= 360.0f)
		{
			fAngleFormat -= 360.0f;
		}
		fFormatRad = fAngleFormat * fAngle;
		Cx = (CircleX + ((sin(fFormatRad)) * Circle->fCircleRadius));
		Cy = (CircleY - ((cos(fFormatRad)) * Circle->fCircleRadius));
		Circle->sCircleFormat[(iFormatCnt + 1)].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		Circle->sCircleFormat[(iFormatCnt + 1)].position = D3DXVECTOR4(Cx, Cy, 1.0f, 1.0f);
	}

	Circle->sCircleFormat[(((int)(Circle->fCircleFormatCount)) + 1)].position = Circle->sCircleFormat[1].position;
	Circle->sCircleFormat[(((int)(Circle->fCircleFormatCount)) + 1)].color = D3DCOLOR_RGBA(255, 0, 0, 255);

	return Circle;
}

void DestoryCircle(VertexCircle* &Circle)
{
	if (Circle->sCircleFormat != NULL)
	{
		delete[]Circle->sCircleFormat;
		Circle->sCircleFormat = NULL;
	}
	if (Circle != NULL)
	{
		delete Circle;
		Circle = NULL;
	}
}

void DoRollCircle(VertexCircle* Circle)
{
	double fAngle = (PI / 180.0f);
	double rad = (360.0f / Circle->fCircleFormatCount);
	double fFormatRad = 0.0f;
	double fAngleFormat = 0.0f;
	double Cx = 0.0f;
	double Cy = 0.0f;

	Circle->fAngle += Circle->fRollSpeed;

	for (int iFormatCnt = 0; iFormatCnt < ((int)(Circle->fCircleFormatCount)); iFormatCnt++)
	{
		fAngleFormat = (Circle->fAngle + (((double)(iFormatCnt)) *  rad));
		if (fAngleFormat >= 360.0f)
		{
			fAngleFormat -= 360.0f;
		}
		fFormatRad = fAngleFormat * fAngle;
		Cx = ((Circle->sCircleFormat[0].position.x) + ((sin(fFormatRad)) * Circle->fCircleRadius));
		Cy = ((Circle->sCircleFormat[0].position.y) - ((cos(fFormatRad)) * Circle->fCircleRadius));

		Circle->sCircleFormat[(iFormatCnt + 1)].position = D3DXVECTOR4(Cx, Cy, 1.0f, 1.0f);
	}

	Circle->sCircleFormat[(((int)(Circle->fCircleFormatCount)) + 1)].position = Circle->sCircleFormat[1].position;

	return;
}

CircleImpact CircleImapctScreen(VertexCircle* Circle)
{
	double Cx = 0.0f;
	double Cy = 0.0f;

	Circle->bImpactState = CIS_NONE;

	if (Circle->sCircleFormat[0].position.x <= (0.0f + Circle->fCircleRadius))
	{
		Circle->sCircleFormat[0].position.x = (0.0f + Circle->fCircleRadius);
		Circle->bImpactState = CIS_LEFT;
	}
	if (Circle->sCircleFormat[0].position.x >= (((double)(WINDOW_WIDTH)) - Circle->fCircleRadius))
	{
		Circle->sCircleFormat[0].position.x = (((double)(WINDOW_WIDTH)) - Circle->fCircleRadius);
		Circle->bImpactState = CIS_RIGHT;
	}
	if (Circle->sCircleFormat[0].position.y <= (0.0f + Circle->fCircleRadius))
	{
		Circle->sCircleFormat[0].position.y = (0.0f + Circle->fCircleRadius);
		Circle->bImpactState = CIS_TOP;
	}
	if (Circle->sCircleFormat[0].position.y >= (((double)(WINDOW_HEIGHT)) - Circle->fCircleRadius))
	{
		Circle->sCircleFormat[0].position.y = (((double)(WINDOW_HEIGHT)) - Circle->fCircleRadius);
		Circle->bImpactState = CIS_BUTTOM;
	}
	return Circle->bImpactState;
}

void CircleImapctEffect(VertexCircle* Circle1, VertexCircle* Circle2)
{
	double fRadtoAngel = (180.0f / PI);
	double fAngeltoRad = (PI / 180.0f);
	double fV1, fV2, fTheta01, fTheta02, fTheta1, fTheta2;
	double fVx1, fVy1, fVx2, fVy2;
	double fVminx1, fVminy1, fVminx2, fVminy2;
	double fBeta1, fBeta2, fV01, fV02, fAlpha1, fAlpha2;

	if ((Circle1->bCircleImapct == CCIS_IMPACTSTART) && (Circle2->bCircleImapct == CCIS_IMPACTSTART))
	{
		fV1 = sqrt(((Circle1->fMoveSpeedX) * (Circle1->fMoveSpeedX)) + ((Circle1->fMoveSpeedY) * (Circle1->fMoveSpeedY)));
		fV2 = sqrt(((Circle2->fMoveSpeedX) * (Circle2->fMoveSpeedX)) + ((Circle2->fMoveSpeedY) * (Circle2->fMoveSpeedY)));

		fTheta01 = (atan(((Circle2->sCircleFormat[0].position.y) - (Circle1->sCircleFormat[0].position.y)) / ((Circle2->sCircleFormat[0].position.x) - (Circle1->sCircleFormat[0].position.x))) * fRadtoAngel) + 90;
		fTheta1 = (atan((Circle1->fMoveSpeedX) / (Circle1->fMoveSpeedY))) * fRadtoAngel;
		fTheta2 = (atan((Circle2->fMoveSpeedX) / (Circle2->fMoveSpeedY))) * fRadtoAngel;

		fVx1 = fV1 * sin((90 - fTheta01 + fTheta1)   *  fAngeltoRad);
		fVy1 = fV1 * cos((90 - fTheta01 + fTheta1)   *  fAngeltoRad);
		fVx2 = fV2 * cos((fTheta01 - fTheta2)   *  fAngeltoRad);
		fVy2 = fV2 * sin((fTheta01 - fTheta2)   *  fAngeltoRad);

		fVminx1 = ((Circle2->fMass) * fVx2) / (Circle1->fMass);
		fVminy1 = fVy1;

		fBeta1 = (atan((fVminy1) / (fVminx1))) * fRadtoAngel;
		fAlpha1 = (180.0 + fTheta01 + fBeta1);
		fV01 = sqrt((fVminx1 * fVminx1) + (fVminy1 * fVminy1));

		fV1 = sqrt(((Circle2->fMoveSpeedX) * (Circle2->fMoveSpeedX)) + ((Circle2->fMoveSpeedY) * (Circle2->fMoveSpeedY)));
		fV2 = sqrt(((Circle1->fMoveSpeedX) * (Circle1->fMoveSpeedX)) + ((Circle1->fMoveSpeedY) * (Circle1->fMoveSpeedY)));

		fTheta02 = (atan(((Circle1->sCircleFormat[0].position.y) - (Circle2->sCircleFormat[0].position.y)) / ((Circle1->sCircleFormat[0].position.x) - (Circle2->sCircleFormat[0].position.x))) * fRadtoAngel) + 90;
		fTheta1 = (atan((Circle2->fMoveSpeedX) / (Circle2->fMoveSpeedY))) * fRadtoAngel;
		fTheta2 = (atan((Circle1->fMoveSpeedX) / (Circle1->fMoveSpeedY))) * fRadtoAngel;

		fVx1 = fV1 * sin((90 - fTheta02 + fTheta1)   *  fAngeltoRad);
		fVy1 = fV1 * cos((90 - fTheta02 + fTheta1)   *  fAngeltoRad);
		fVx2 = fV2 * cos((fTheta02 - fTheta2)   *  fAngeltoRad);
		fVy2 = fV2 * sin((fTheta02 - fTheta2)   *  fAngeltoRad);

		fVminx2 = ((Circle1->fMass) * fVx2) / (Circle2->fMass);
		fVminy2 = fVy1;

		fBeta2 = (atan((fVminy2) / (fVminx2))) * fRadtoAngel;
		fAlpha2 = (180.0 + fTheta02 + fBeta2);
		fV02 = sqrt((fVminx2 * fVminx2) + (fVminy2 * fVminy2));

		if (fAlpha1 < 0)
		{
			fAlpha1 += 360.0;
		}
		if (fAlpha2 < 0)
		{
			fAlpha2 += 360.0;
		}
		if (fAlpha1 > 360)
		{
			fAlpha1 -= 360.0;
		}
		if (fAlpha2 > 360)
		{
			fAlpha2 -= 360.0;
		}

		Circle1->fMoveSpeedX = (fV01 * sin((fAlpha1)* fAngeltoRad));
		Circle1->fMoveSpeedY = (fV01 * cos((fAlpha1)* fAngeltoRad));
		Circle2->fMoveSpeedX = 0.0 - (fV02 * sin((fAlpha2)* fAngeltoRad));
		Circle2->fMoveSpeedY = (fV02 * cos((fAlpha2)* fAngeltoRad));

		/*
		if ((fAlpha1 >= 90) && (fAlpha1 < 180))
		{
		Circle1->fMoveSpeedX = fV01 * cos((fAlpha1) * fAngeltoRad);
		Circle1->fMoveSpeedY = fV01 * sin((fAlpha1) * fAngeltoRad) * (-1.0f);
		}
		if ((fAlpha1 >= 180) && (fAlpha1 < 270))
		{
		Circle1->fMoveSpeedX = fV01 * cos((fAlpha1) * fAngeltoRad) * (-1.0f);
		Circle1->fMoveSpeedY = fV01 * sin((fAlpha1) * fAngeltoRad) * (-1.0f);
		}
		if ((fAlpha1 >= 270) && (fAlpha1 < 360))
		{
		Circle1->fMoveSpeedX = fV01 * cos((fAlpha1) * fAngeltoRad) * (-1.0f);
		Circle1->fMoveSpeedY = fV01 * sin((fAlpha1) * fAngeltoRad) * (-1.0f);
		}
		if ((fAlpha1 >= 0) && (fAlpha1 < 90))
		{
		Circle1->fMoveSpeedX = fV01 * cos((fAlpha1) * fAngeltoRad);
		Circle1->fMoveSpeedY = fV01 * sin((fAlpha1) * fAngeltoRad) * (-1.0f);
		}


		if ((fAlpha2 >= 90) && (fAlpha2 < 180))
		{
		Circle2->fMoveSpeedX = fV02 * cos((fAlpha2) * fAngeltoRad);
		Circle2->fMoveSpeedY = fV02 * sin((fAlpha2) * fAngeltoRad);
		}
		if ((fAlpha2 >= 180) && (fAlpha2 < 270))
		{
		Circle2->fMoveSpeedX = fV02 * cos((fAlpha2) * fAngeltoRad) * (-1.0f);
		Circle2->fMoveSpeedY = fV02 * sin((fAlpha2) * fAngeltoRad);
		}
		if ((fAlpha2 >= 270) && (fAlpha2 < 360))
		{
		Circle2->fMoveSpeedX = fV02 * cos((fAlpha2) * fAngeltoRad) * (-1.0f);
		Circle2->fMoveSpeedY = fV02 * sin((fAlpha2) * fAngeltoRad) * (-1.0f);
		}
		if ((fAlpha2 >= 0) && (fAlpha2 < 90))
		{
		Circle2->fMoveSpeedX = fV02 * cos((fAlpha2) * fAngeltoRad);
		Circle2->fMoveSpeedY = fV02 * sin((fAlpha2) * fAngeltoRad) * (-1.0f);
		}
		*/

		Circle1->bCircleImapct = CCIS_IMPACTEND;
		Circle2->bCircleImapct = CCIS_IMPACTEND;
	}
}

BOOL DoCircleImapct(VertexCircle* Circle1, VertexCircle* Circle2)
{
	double fRadtoAngel = (180.0f / PI);
	double fAngeltoRad = (PI / 180.0f);
	double fVx1, fVy1, fVx2, fVy2, f1, f2;
	double fDistance, dx, dy, fRDistance, fe, fTheta, fex, fey;
	dx = fabs((Circle2->sCircleFormat[0].position.x) - (Circle1->sCircleFormat[0].position.x));
	dy = fabs((Circle2->sCircleFormat[0].position.y) - (Circle1->sCircleFormat[0].position.y));
	fDistance = sqrt((dx * dx) + (dy * dy));
	fRDistance = (Circle1->fCircleRadius) + (Circle2->fCircleRadius);
	if ((fRDistance > fDistance) && ((Circle2->bCircleImapct == CCIS_NONE) && (Circle1->bCircleImapct == CCIS_NONE)))
	{
		fe = fRDistance - fDistance;
		fVx1 = fabs(Circle1->fMoveSpeedX);
		fVy1 = fabs(Circle1->fMoveSpeedY);
		fVx2 = fabs(Circle2->fMoveSpeedX);
		fVy2 = fabs(Circle2->fMoveSpeedY);
		f1 = ((fVx1) / (fVx1 + fVx2));
		f2 = ((fVx2) / (fVx1 + fVx2));
		fTheta = (atan(fe / (fabs((Circle1->fMoveSpeedX) + (Circle2->fMoveSpeedX)))));
		fex = fe * cos(fTheta);
		fey = fe * sin(fTheta);

		if (((Circle1->fMoveSpeedX) * (Circle2->fMoveSpeedX)) > 0)
		{
			if (fabs(Circle1->fMoveSpeedX) > fabs(Circle2->fMoveSpeedX))
			{
				if ((Circle1->fMoveSpeedX) > 0)
				{
					Circle1->sCircleFormat[0].position.x -= fex * f2 + fex + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.x -= fex * f2 + EFFECT_DISTANCE;
				}
				else
				{
					Circle1->sCircleFormat[0].position.x += fex * f2 + fex + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.x += fex * f2 + EFFECT_DISTANCE;
				}
			}
			else
			{
				if ((Circle1->fMoveSpeedX) > 0)
				{
					Circle1->sCircleFormat[0].position.x -= fex * f1 + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.x -= fex * f1 + fex + EFFECT_DISTANCE;
				}
				else
				{
					Circle1->sCircleFormat[0].position.x += fex * f1 + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.x += fex * f1 + fex + EFFECT_DISTANCE;
				}
			}
		}
		else
		{
			if (Circle1->fMoveSpeedX > 0)
			{
				Circle1->sCircleFormat[0].position.x -= fex * f1 + EFFECT_DISTANCE;
				Circle2->sCircleFormat[0].position.x += fex * f2 + EFFECT_DISTANCE;
			}
			else
			{
				Circle1->sCircleFormat[0].position.x += fex * f1 + EFFECT_DISTANCE;
				Circle2->sCircleFormat[0].position.x -= fex * f2 + EFFECT_DISTANCE;
			}
		}

		if (((Circle1->fMoveSpeedY) * (Circle2->fMoveSpeedY)) > 0)
		{
			if (fabs(Circle1->fMoveSpeedY) > fabs(Circle2->fMoveSpeedY))
			{
				if ((Circle1->fMoveSpeedY) > 0)
				{
					Circle1->sCircleFormat[0].position.y -= fey * f2 + fey + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.y -= fey * f2 + EFFECT_DISTANCE;
				}
				else
				{
					Circle1->sCircleFormat[0].position.y += fey * f2 + fey + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.y += fey * f2 + EFFECT_DISTANCE;
				}
			}
			else
			{
				if ((Circle1->fMoveSpeedY) > 0)
				{
					Circle1->sCircleFormat[0].position.y -= fey * f1 + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.y -= fey * f1 + fey + EFFECT_DISTANCE;
				}
				else
				{
					Circle1->sCircleFormat[0].position.y += fey * f1 + EFFECT_DISTANCE;
					Circle2->sCircleFormat[0].position.y += fey * f1 + fey + EFFECT_DISTANCE;
				}
			}
		}
		else
		{
			if (Circle1->fMoveSpeedY > 0)
			{
				Circle1->sCircleFormat[0].position.y -= fey * f1 + EFFECT_DISTANCE;
				Circle2->sCircleFormat[0].position.y += fey * f2 + EFFECT_DISTANCE;
			}
			else
			{
				Circle1->sCircleFormat[0].position.y += fey * f1 + EFFECT_DISTANCE;
				Circle2->sCircleFormat[0].position.y -= fey * f2 + EFFECT_DISTANCE;
			}
		}

		Circle1->bCircleImapct = CCIS_IMPACTSTART;
		Circle2->bCircleImapct = CCIS_IMPACTSTART;
		return TRUE;
	}
	return FALSE;
}

INT CircleImapct(VertexCircle* Circle1, VertexCircle* Circle2)
{
	FLOAT dx = fabs((Circle2->sCircleFormat[0].position.x) - (Circle1->sCircleFormat[0].position.x));
	FLOAT dy = fabs((Circle2->sCircleFormat[0].position.y) - (Circle1->sCircleFormat[0].position.y));
	FLOAT fDistance = sqrt((dx * dx) + (dy * dy));
	FLOAT fRDistance = (Circle1->fCircleRadius) + (Circle2->fCircleRadius);
	return (fDistance <= fRDistance);
}