#include <Windows.h>
#include "GameFrame.h"
#include "MyDirect.h"
#include "Input.h"
#include "Texture.h"

void Initialize(HINSTANCE hInstance, HWND hWnd);
void Finalize(HWND hWnd);
void Render(void);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LONG WindowsWidth = 0, WindowsHeight = 0;
	int SystemWidth = 0, SystemHeight = 0, WindowsDefaultPostX = 0, WindowsDefaultPostY = 0;
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	SystemWidth = GetSystemMetrics(SM_CXSCREEN);
	SystemHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT WindowsRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	AdjustWindowRect(&WindowsRect, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);

	WindowsWidth = min((WindowsRect.right - WindowsRect.left), SystemWidth);
	WindowsHeight = min((WindowsRect.bottom - WindowsRect.top), SystemHeight);

	WindowsDefaultPostX = (SystemWidth - WindowsWidth) / 2;
	WindowsDefaultPostY = (SystemHeight - WindowsHeight) / 2;

	if (!RegisterClass(&wc))
	{
		return -1;
	}

	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		(WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME)),
		WindowsDefaultPostX,
		WindowsDefaultPostY,
		WindowsWidth,
		WindowsHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	Initialize(hInstance, hWnd);

	int a = 0;

	MSG msg = { 0 };
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Update Function (

			UpdateGameLogic(hInstance, hWnd);
			Render();

			//Update Function )
		}
	} while (msg.message != WM_QUIT);

	GameStage_Final(hInstance, hWnd);
	Finalize(hWnd);

	UnregisterClass(CLASS_NAME, wc.hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_TIMER:

		GameStage_Timer(wParam);

		break;

	case WM_PAINT:
		//Render
		//TODO

		ValidateRect(hWnd, NULL);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}

		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "Close Window?", "Warning", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



void Render(void)
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		MyDirect3D_DeviceRenderTextureAlpha();
		//Draw Function (

		GameStage_Render();

		//Draw Function )
		MyDirect3D_DestoryRenderTextureAlpha();
	}
	pDevice->EndScene();
	hr = pDevice->Present(NULL, NULL, NULL, NULL);
	if (hr == D3DERR_DEVICELOST)
	{
		//DeviceCrash
		//TODO
	}
}

void Initialize(HINSTANCE hInstance, HWND hWnd)
{
	//Variable (



	//Variable )

	//Initialize Function (

	if ((MyDirect3D_Initialize(hWnd)) == FALSE)
	{
		return;
	}

	TextureLoad();

	if ((TextureSampler()) == FALSE)
	{
		//TODO
	}

	InputHandle(hInstance, hWnd);

	GameStage_Init(hInstance, hWnd);

	//Initialize Function )
}

void Finalize(HWND hWnd)
{
	//Finalize Function (

	InputRelease();

	MyDirect3D_Finalize();

	ReleaseTexture();

	//Finalize Function )
}