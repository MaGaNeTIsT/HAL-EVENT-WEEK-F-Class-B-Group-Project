#include "GameFrame.h"
#include "MyDirect.h"
#include "Texture.h"

void Initialize(HINSTANCE hInstance, HWND hWnd)
{
	//Initialize Function (

	if ((MyDirect3D_Initialize(hWnd)) == FALSE) { return; }

	TextureLoad();
	TextureSampler();

	srand((unsigned)time(NULL));

	//Initialize Function )
}

void Finalize(HWND hWnd)
{
	//Finalize Function (

	ReleaseTexture();

	MyDirect3D_Finalize();

	//Finalize Function )
}

void Draw(void)
{
	Matrix_Set();
}

D3DXMATRIX matWorld;
D3DXMATRIX matView;
D3DXMATRIX matProj;
D3DVIEWPORT9 vp;

D3DXVECTOR3 vFront(0.0, 0.0, 1.0);
D3DXVECTOR3 vRight(1.0, 0.0, 0.0);
D3DXVECTOR3 vTop(0.0, 1.0, 0.0);
D3DXVECTOR3 vPos(0.0, 0.0, 0.0);
D3DXVECTOR3 vAt;

void Matrix_Set(void)
{
	vAt = vPos + vFront;
	D3DXMatrixLookAtLH(&matView, &vPos, &vAt, &vTop);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMatrixIdentity(&matWorld);
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	pDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, 16.0f / 9.0f, 1.0f, 1000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	vp.X = 0;
	vp.Y = 0;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	pDevice->SetViewport(&vp);
}