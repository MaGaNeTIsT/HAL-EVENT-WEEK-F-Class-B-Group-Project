#ifndef _SCORE_H
#define _SCORE_H

#include "Common.h"
#include <Windows.h>

typedef struct SDrawNumData {
	long iNum;
	double fPosX;
	double fPosY;
	UINT iSWidth;
	UINT iSHeight;
}DrawNumData;

DrawNumData Create_NumData(long iNum, double fPosX, double fPosY, UINT iSWidth, UINT iSHeight);
void Init_Num(void);
long Get_Num(UINT Index);
void Set_Num(UINT Index, long Num);
bool Draw_Num(DrawNumData sNumber);
long Square_Num(long Num1, long Num2);

#endif // !_SCORE_H