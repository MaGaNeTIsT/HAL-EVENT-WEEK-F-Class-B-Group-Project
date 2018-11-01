#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <Windows.h>

typedef enum TimerCode{
	TC_ERROR = 0,
	TC_TIMER01,
	TC_TIMER02,
	TC_TIMER03,
	TC_TIMER04,
	TC_TIMER05,
	TC_END
}TimerCode;

bool OnSetTimer(HWND hWnd, TimerCode Code, UINT Time);
void DestoryTimer(HWND hWnd, TimerCode Code);

#endif // !_ANIMATION_H