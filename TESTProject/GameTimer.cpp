#include "GameTimer.h"

BattleTimer gsBattleTimer;


void InitTimer(void)
{
	gsBattleTimer.dDelta = 0.0;
	QueryPerformanceFrequency(&gsBattleTimer.Ticks);
	gsBattleTimer.dClock = 0.0;
	QueryPerformanceCounter(&gsBattleTimer.t1);
}

void UpdateTimer(void)
{
	QueryPerformanceCounter(&gsBattleTimer.t2);
	gsBattleTimer.dDelta = (double)(gsBattleTimer.t2.QuadPart - gsBattleTimer.t1.QuadPart);
	gsBattleTimer.dClock += gsBattleTimer.dDelta / ((double)gsBattleTimer.Ticks.QuadPart);
	QueryPerformanceCounter(&gsBattleTimer.t1);
}

double GetTimer(void)
{
	return gsBattleTimer.dClock;
}