#ifndef _INPUT_H
#define _INPUT_H

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <DInput.h>
#include <Windows.h>

typedef enum TECommand {
	Com_None = 0,
	Com_Q,
	Com_E,
	Com_A,
	Com_D,
	Com_W,
	Com_S,
	Com_Up,
	Com_Down,
	Com_Sp
}Command;

typedef enum TEJoyCommand {
	JoyCom_None = 0,
}JoyCommand;

typedef struct TSJoyconPosition {
	FLOAT PrevX;
	FLOAT PrevY;
	FLOAT PrevZ;

	FLOAT X;
	FLOAT Y;
	FLOAT Z;
}JoyconPos;

bool InputHandle(HINSTANCE hInstance, HWND hWnd);

void InputRelease(void);

Command UpdateInput(HINSTANCE hInstance, HWND hWnd);

bool InputDeviceAuthorization(void* pBuffer, long lSize);

DIMOUSESTATE* MouseInputDeviceAuthorization(void);

DIJOYSTATE* JoyInputDeviceAuthorization(void);

void DevicePoll(void);

#endif // !_INPUT_H