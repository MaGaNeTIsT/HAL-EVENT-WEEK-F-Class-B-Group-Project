#ifndef _POLYGON_H
#define _POLYGON_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif
#include <d3dx9.h>
#include <Windows.h>

typedef struct Vertex2D_tag {
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 TextureCoor;
}Vertex2D;

typedef struct sSquarePolygonTextureSize {
	double Width;
	double Height;
}SquareTextureSize;

typedef struct sSquarePolygonImpactDistance {
	double Top;
	double Bottom;
	double Left;
	double Right;
}SquareImpactDistance;

typedef struct sSquarePolygonData {
	UINT                      Index;
	Vertex2D*                 TextureFormat;
	SquareTextureSize         TextureSize;
	SquareImpactDistance      ImpactDistance;
	D3DXVECTOR4               CentrePoint;
}SquarePolygon;

Vertex2D FormatData_Initialize(double X, double Y, unsigned int R, unsigned int G, unsigned int B, unsigned int A, double tX, double tY);
SquarePolygon* CreateSquarePolygon(UINT Index, double CentreX, double CentreY, double TexWidth, double TexHeight);
void UpdatePolygon(SquarePolygon* &Polygon);
void DestoryPolygon(SquarePolygon* &spPolygon);
void Set_TextureCoor(SquarePolygon* &spPolygon, double x1, double y1, double x2, double y2);

#endif // !_POLYGON_H