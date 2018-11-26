#include "Magic_Circle.h"

int DoImpact(float x1, float y1, float r1, float x2, float y2, float r2);

MagicCircle::MagicCircle()
{
	spPointInfo = NULL;
	uipPointIdx = NULL;
	uiPointCount = 0;
	bPointTouch = NULL;
	bFinish = FALSE;
}

MagicCircle::~MagicCircle()
{
	//SAFE_DELETE(spPointInfo);
	//SAFE_DELETE(uipPointIdx);
	SAFE_DELETE(bPointTouch);
}

BOOL MagicCircle::Create(D3DXVECTOR3* Info, UINT* Index, INT Num)
{
	if (Info == NULL || Index == NULL || Num <= 0)
	{
		return FALSE;
	}

	Clear();

	spPointInfo = Info;
	uipPointIdx = Index;
	uiPointCount = Num;

	bPointTouch = new BOOL[uiPointCount];
	for (INT Idx = 0; Idx < uiPointCount; Idx++)
	{
		bPointTouch[Idx] = FALSE;
	}

	return TRUE;
}

BOOL MagicCircle::Clear(void)
{
	//SAFE_DELETE(spPointInfo);
	//SAFE_DELETE(uipPointIdx);
	SAFE_DELETE(bPointTouch);
	spPointInfo = NULL;
	uipPointIdx = NULL;
	bPointTouch = NULL;
	uiPointCount = 0;
	bFinish = FALSE;
	return TRUE;
}

BOOL MagicCircle::Update(FLOAT X, FLOAT Y, FLOAT Radius)
{
	if (bFinish == TRUE)
	{
		return FALSE;
	}
	INT Idx = 0;
	for (Idx = 0; Idx < uiPointCount; Idx++)
	{
		if (bPointTouch[Idx] == FALSE) { break; }
		if (Idx == (uiPointCount - 1) && bPointTouch[Idx] == TRUE)
		{
			bFinish = TRUE;
			return FALSE;
		}
	}

	if (DoImpact(X, Y, Radius,
		spPointInfo[uipPointIdx[Idx]].x,
		spPointInfo[uipPointIdx[Idx]].y,
		MAGICPOINT_RADIUS))
	{
		bPointTouch[Idx] = TRUE;
		return TRUE;
	}

	return ERROR;
}

BOOL MagicCircle::IsMagicFinished(FLOAT X, FLOAT Y, FLOAT Radius)
{
	if (Update(X, Y, Radius) != ERROR)
	{
		return bFinish;
	}

	return FALSE;
}



int DoImpact(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float RealDistance = (y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2);
	float ImpactDistance = r1 + r2;
	return ImpactDistance > RealDistance;
}