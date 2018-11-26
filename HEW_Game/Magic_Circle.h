#pragma once

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x) { (x)->Release(); (x) = NULL;}}
#endif // !SAFE_RELEASE

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if((x) != NULL) { delete[](x); (x) = NULL;}}
#endif // !SAFE_RELEASE

#ifndef PTR_DELETE
#define PTR_DELETE(x) {if((x) != NULL) { delete (x); (x) = NULL;}}
#endif // !SAFE_RELEASE

#ifndef ERROR
#define ERROR (-1011)
#endif

#define MAGICPOINT_RADIUS (20.0f)


#include <Windows.h>
#include <d3dx9.h>

class MagicCircle
{
public:
	BOOL            Create(D3DXVECTOR3* Info, UINT* Index, INT Num);
	BOOL            Clear(void);
private:
	BOOL            Update(FLOAT X, FLOAT Y, FLOAT Radius);
public:
	BOOL            IsMagicFinished(FLOAT X, FLOAT Y, FLOAT Radius);
private:
	D3DXVECTOR3*    spPointInfo;
	UINT*           uipPointIdx;
	UINT            uiPointCount;
private:
	BOOL*           bPointTouch;
	BOOL            bFinish;
public:
	MagicCircle();
	~MagicCircle();
};