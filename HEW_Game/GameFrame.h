#pragma once

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <Windows.h>
#include <d3dx9.h>
#include <time.h>
#include "Common.h"

void Initialize(HINSTANCE hInstance, HWND hWnd);
void Finalize(HWND hWnd);
void Draw(void);
void Matrix_Set(void);