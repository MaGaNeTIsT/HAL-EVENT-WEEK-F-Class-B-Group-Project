#ifndef _FADEINOUT_H
#define _FADEINOUT_H

#include <Windows.h>

typedef enum EFadeState {
	EFS_NONE = 0,
	EFS_IN,
	EFS_OUT
}FadeState;

void FadeInOut_Init(void);
void FadeInOut_On(void);
void OnFadeIn(void);
void OnFadeOut(void);

#endif // !_FADEINOUT_H