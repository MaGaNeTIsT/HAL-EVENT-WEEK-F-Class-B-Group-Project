#include "Input.h"
#include "Common.h"

static LPDIRECTINPUT8 g_pMyDirectInput = NULL;
static LPDIRECTINPUTDEVICE8 g_pKeyboardDevice = NULL;
static LPDIRECTINPUTDEVICE8 g_pMouseDevice = NULL;
static LPDIRECTINPUTDEVICE8 g_pJoyconDevice = NULL;
static DIJOYSTATE g_cJoyInformation = { 0 };
static char g_cKeyboardBuffer[256] = { 0 };
static const long lKeyboardBufferSize = sizeof(g_cKeyboardBuffer);
static DIMOUSESTATE g_cMouseInformation = { 0 };

BOOL FAR PASCAL Poll_Device(LPCDIDEVICEINSTANCE pdInst, LPVOID pvRef);
LPVOID ptr = NULL;

bool InputHandle(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	hr = DirectInput8Create(hInstance, DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (void**)&g_pMyDirectInput, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//hr = IDirectInput8_EnumDevices(g_pMyDirectInput,);

	hr = g_pMyDirectInput->CreateDevice(GUID_SysKeyboard, &g_pKeyboardDevice, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = g_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = g_pKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = g_pMyDirectInput->CreateDevice(GUID_SysMouse, &g_pMouseDevice, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = g_pMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = g_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//do
	//{
	//	DevicePoll();
	//} while (g_pJoyconDevice == NULL);

	//hr = g_pJoyconDevice->SetDataFormat(&c_dfDIJoystick);
	//if (FAILED(hr))
	//{
	//	return FALSE;
	//}

	//hr = g_pJoyconDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	//if (FAILED(hr))
	//{
	//	return FALSE;
	//}

	return TRUE;
}

void InputRelease(void)
{
	g_pKeyboardDevice->Unacquire();
	g_pMouseDevice->Unacquire();
	g_pJoyconDevice->Unacquire();

	SAFE_RELEASE(g_pJoyconDevice)
	SAFE_RELEASE(g_pMouseDevice)
	SAFE_RELEASE(g_pKeyboardDevice)
	SAFE_RELEASE(g_pMyDirectInput)
}

Command UpdateInput(HINSTANCE hInstance, HWND hWnd)
{
	bool KeyUp = 0, KeyDown = 0, KeyLeft = 0, KeyRight = 0, KeyZ = 0;
	ZeroMemory(g_cKeyboardBuffer, lKeyboardBufferSize);
	if (InputDeviceAuthorization((LPVOID)g_cKeyboardBuffer, lKeyboardBufferSize))
	{
		if (g_cKeyboardBuffer[DIK_Q] & 0x80)
		{
			return Com_Q;
		}
		if (g_cKeyboardBuffer[DIK_E] & 0x80)
		{
			return Com_E;
		}
		if (g_cKeyboardBuffer[DIK_A] & 0x80)
		{
			return Com_A;
		}
		if (g_cKeyboardBuffer[DIK_D] & 0x80)
		{
			return Com_D;
		}
		if (g_cKeyboardBuffer[DIK_W] & 0x80)
		{
			return Com_W;
		}
		if (g_cKeyboardBuffer[DIK_S] & 0x80)
		{
			return Com_S;
		}
		if (g_cKeyboardBuffer[DIK_UP] & 0x80)
		{
			return Com_Up;
		}
		if (g_cKeyboardBuffer[DIK_DOWN] & 0x80)
		{
			return Com_Down;
		}
		if (g_cKeyboardBuffer[DIK_SPACE] & 0x80)
		{
			return Com_Sp;
		}
	}
	return Com_None;
}

bool InputDeviceAuthorization(void* pBuffer, long lSize)
{
	HRESULT hr;
	while (true)
	{
		g_pKeyboardDevice->Poll();
		g_pKeyboardDevice->Acquire();

		hr = g_pKeyboardDevice->GetDeviceState(lSize, pBuffer);
		if (SUCCEEDED(hr))
		{
			break;
		}
		if ((hr != DIERR_INPUTLOST) || (hr != DIERR_NOTACQUIRED))
		{
			return FALSE;
		}
		hr = g_pKeyboardDevice->Acquire();
		if (FAILED(hr))
		{
			return FALSE;
		}
	}
	return TRUE;
}

DIMOUSESTATE* MouseInputDeviceAuthorization(void)
{
	g_pMouseDevice->Poll();
	g_pMouseDevice->Acquire();
	ZeroMemory(&g_cMouseInformation, sizeof(g_cMouseInformation));
	if (SUCCEEDED(g_pMouseDevice->GetDeviceState(sizeof(g_cMouseInformation), (LPVOID)&g_cMouseInformation)))
	{
		return &g_cMouseInformation;
	}
	else
	{
		return NULL;
	}

}

DIJOYSTATE* JoyInputDeviceAuthorization(void)
{
	g_pJoyconDevice->Poll();
	g_pJoyconDevice->Acquire();
	ZeroMemory(&g_cJoyInformation, sizeof(g_cJoyInformation));
	if (SUCCEEDED(g_pJoyconDevice->GetDeviceState(sizeof(g_cJoyInformation), (LPVOID)&g_cJoyInformation)))
	{
		return &g_cJoyInformation;
	}
	else
	{
		return NULL;
	}

}

void DevicePoll(void)
{
	g_pMyDirectInput->EnumDevices(DI8DEVCLASS_ALL, Poll_Device, ptr, DIEDFL_ALLDEVICES);
}

BOOL FAR PASCAL Poll_Device(LPCDIDEVICEINSTANCE pdInst, LPVOID pvRef)
{
	if (pdInst->tszProductName != NULL)
	{
		if ((strcmp(pdInst->tszProductName, "vJoy Device")) == 0)
		{
			HRESULT hr;
			hr = g_pMyDirectInput->CreateDevice(pdInst->guidInstance, &g_pJoyconDevice, NULL);

			return DIENUM_STOP;
		}
		return DIENUM_CONTINUE;
	}
	else
	{
		return DIENUM_STOP;
	}
}