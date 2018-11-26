#ifndef _MYDIRECT_H
#define _MYDIRECT_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <Windows.h>
#include <d3dx9.h>

typedef struct TSVertex {
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TextureCoor;
}Vertex;

//Function
bool MyDirect3D_Initialize(HWND hWnd);
bool MyDirect3D_SetInitialize(HWND hWnd);
void MyDirect3D_Finalize(void);

LPDIRECT3DDEVICE9  MyDirect3D_GetDevice(void);

void MyDirect3D_DeviceRenderTextureAlpha(void);
void MyDirect3D_DestoryRenderTextureAlpha(void);

bool CreateVertexBuffer(UINT FormatCount);

#endif // !_MYDIRECT_H