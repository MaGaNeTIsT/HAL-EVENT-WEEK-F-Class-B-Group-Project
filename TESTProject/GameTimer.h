#ifndef _GAMETIMER_H
#define _GAMETIMER_H

#include <Windows.h>

typedef struct BattleTimerStruct
{
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	LARGE_INTEGER Ticks;
	double dDelta;
	double dClock;
} BattleTimer;

void InitTimer(void);
void UpdateTimer(void);
double GetTimer(void);

#endif // !_GAMETIMER_H
