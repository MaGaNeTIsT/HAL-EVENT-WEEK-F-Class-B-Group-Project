#include "Score.h"
#include "Polygon.h"
#include "MyDirect.h"
#include "Texture.h"

long iNumber[SCORE_COUNT];


DrawNumData Create_NumData(long iNum, double fPosX, double fPosY, UINT iSWidth, UINT iSHeight)
{
	DrawNumData sNumber;
	sNumber.iNum = iNum;
	sNumber.fPosX = fPosX;
	sNumber.fPosY = fPosY;
	sNumber.iSWidth = iSWidth;
	sNumber.iSHeight = iSHeight;
	return sNumber;
}

void Init_Num(void)
{
	for (int i = 0; i < SCORE_COUNT; i++)
	{
		iNumber[i] = 0;
	}
}

long Get_Num(UINT Index)
{
	return iNumber[Index];
}

void Set_Num(UINT Index, long Num)
{
	iNumber[Index] = Num;
}

bool Draw_Num(DrawNumData sNumber)
{
	long Number = sNumber.iNum;
	int iCount = 0;
	while (Number)
	{
		Number = Number / 10;
		iCount++;
	}
	SquarePolygon** ppNumPolygon = new SquarePolygon*[iCount];
	for (int i = 0; i < iCount; i++)
	{
		ppNumPolygon[i] = CreateSquarePolygon(-1, ((sNumber.fPosX + (sNumber.iSWidth * (0.5f))) + (i * SCORE_FONT_WIDTH)), (sNumber.fPosY + (sNumber.iSHeight * (0.5f))), SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT);
		int OnCount = (sNumber.iNum / (Square_Num(10, ((iCount - i) - 1)))) % 10;
		Set_TextureCoor(ppNumPolygon[i], (OnCount * 0.1f), 0.0f, ((OnCount + 1) * 0.1f), 1.0f);
	}
	if (OnTexture(GetTexture(NUMBER)))
	{
		for (int i = 0; i < iCount; i++)
		{
			Draw(ppNumPolygon[i]->TextureFormat, D3DPT_TRIANGLESTRIP, 2);
		}
	}
	for (int i = 0; i < iCount; i++)
	{
		DestoryPolygon(ppNumPolygon[i]);
	}
	delete[]ppNumPolygon;

	return TRUE;
}

long Square_Num(long Num1, long Num2)
{
	long Num = Num1;
	if (Num2 != 0)
	{
		for (int i = 0; i < (Num2 - 1); i++)
		{
			Num = Num * Num1;
		}
	}
	if (Num2 == 0)
	{
		return 1;
	}
	return Num;
}