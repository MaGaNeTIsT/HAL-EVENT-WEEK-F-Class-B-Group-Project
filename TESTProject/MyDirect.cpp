#include "MyDirect.h"
#include "Polygon.h"
#include "Common.h"

static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

bool MyDirect3D_Initialize(HWND hWnd)
{
	if (MyDirect3D_SetInitialize(hWnd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

bool MyDirect3D_SetInitialize(HWND hWnd)
{
	//Variable (
	HRESULT hr;
	D3DVIEWPORT9 ViewPort;
	D3DPRESENT_PARAMETERS g_D3DPP;
	D3DCAPS9 caps;
	int vp = 0;
	//Variable )

	//Create Interface (
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return FALSE;
	}
	//Create Interface )

	//Get Information (
	hr = g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
	{
		return FALSE;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	//Get Information )

	//Write Information (
	ZeroMemory(&g_D3DPP, sizeof(g_D3DPP));

	g_D3DPP.BackBufferWidth = WINDOW_WIDTH;
	g_D3DPP.BackBufferHeight = WINDOW_HEIGHT;
	g_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;  //D3DFMT_A8B8G8R8
	g_D3DPP.BackBufferCount = 1;

	g_D3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3DPP.MultiSampleQuality = 0;

	g_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DPP.hDeviceWindow = hWnd;
	g_D3DPP.Windowed = TRUE;

	//g_D3DPP.EnableAutoDepthStencil = TRUE;
	//g_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;

	g_D3DPP.Flags = 0;
	g_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//Write Information )

	//Create Device (
	hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3DPP,
		&g_pD3DDevice
	);
	if (FAILED(hr))
	{
		return FALSE;
	}
	//Create Device )

	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = g_D3DPP.BackBufferWidth;
	ViewPort.Height = g_D3DPP.BackBufferHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	hr = MyDirect3D_GetDevice()->SetViewport(&ViewPort);
	if (FAILED(hr))
	{
		return FALSE;
	}
	return TRUE;
}

void MyDirect3D_Finalize(void)
{
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	SAFE_RELEASE(g_pVertexBuffer);
	SAFE_RELEASE(g_pIndexBuffer);
}

LPDIRECT3DDEVICE9  MyDirect3D_GetDevice(void)
{
	return g_pD3DDevice;
}

bool Draw(Vertex2D* Polygon, D3DPRIMITIVETYPE Mode,UINT Count)
{
	if (FAILED((MyDirect3D_GetDevice()->DrawPrimitiveUP(Mode, Count, Polygon, sizeof(Vertex2D)))))
	{
		return FALSE;
	}
	return TRUE;
}

void MyDirect3D_DeviceRenderTextureAlpha(void)
{
	MyDirect3D_GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	MyDirect3D_GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	MyDirect3D_GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	MyDirect3D_GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	MyDirect3D_GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	MyDirect3D_GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

void MyDirect3D_DestoryRenderTextureAlpha(void)
{
	MyDirect3D_GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

bool CreateVertexBuffer(UINT FormatCount)
{
	HRESULT hr;

	hr = g_pD3DDevice->CreateVertexBuffer((FormatCount * sizeof(Vertex2D)), D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}