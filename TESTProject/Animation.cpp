#include "Animation.h"

bool OnSetTimer(HWND hWnd, TimerCode Code, UINT Time)
{
	UINT TCode = TC_ERROR, TEnd = TC_END;
	TCode = Code;
	if ((TCode == TC_ERROR) || (TCode == TC_END))
	{
		MessageBox(hWnd, "Set Timer Error", "TimerError", MB_OK);
		return FALSE;
	}
	SetTimer(hWnd, TCode, Time, NULL);
	return TRUE;
}

void DestoryTimer(HWND hWnd, TimerCode Code)
{
	UINT TCode = TC_ERROR;
	TCode = Code;
	if ((TCode == TC_ERROR) || (TCode == TC_END))
	{
		MessageBox(hWnd, "Destory Timer Error", "TimerError", MB_OK);
		return;
	}
	KillTimer(hWnd, TCode);
}