#include "Polygon.h"

Vertex2D FormatData_Initialize(double X, double Y, unsigned int R, unsigned int G, unsigned int B, unsigned int A, double tX, double tY)
{
	Vertex2D Format;
	Format.position = D3DXVECTOR4(X, Y, 1.0f, 1.0f);
	Format.color = D3DCOLOR_RGBA(R, G, B, A);
	Format.TextureCoor = D3DXVECTOR2(tX, tY);
	return Format;
}

SquarePolygon* CreateSquarePolygon(UINT Index, double CentreX, double CentreY, double TexWidth, double TexHeight)
{
	SquarePolygon* Polygon;
	Polygon = new SquarePolygon;
	Polygon->TextureFormat = new Vertex2D[4];
	Polygon->Index = Index;
	Polygon->CentrePoint = D3DXVECTOR4(CentreX, CentreY, 1.0f, 1.0f);
	Polygon->TextureSize.Width = TexWidth;
	Polygon->TextureSize.Height = TexHeight;
	Polygon->ImpactDistance.Top = TexHeight / 2.0f;
	Polygon->ImpactDistance.Bottom = TexHeight - Polygon->ImpactDistance.Top;
	Polygon->ImpactDistance.Left = TexWidth / 2.0f;
	Polygon->ImpactDistance.Right = TexWidth - Polygon->ImpactDistance.Left;

	Polygon->TextureFormat[0] = FormatData_Initialize((CentreX - (TexWidth / 2.0f)), (CentreY - (TexHeight / 2.0f)), 255, 255, 255, 255, 0.0f, 0.0f);
	Polygon->TextureFormat[1] = FormatData_Initialize((Polygon->TextureFormat[0].position.x + TexWidth), (Polygon->TextureFormat[0].position.y), 255, 255, 255, 255, 1.0f, 0.0f);
	Polygon->TextureFormat[2] = FormatData_Initialize((Polygon->TextureFormat[0].position.x), (Polygon->TextureFormat[0].position.y + (TexHeight)), 255, 255, 255, 255, 0.0f, 1.0f);
	Polygon->TextureFormat[3] = FormatData_Initialize((Polygon->TextureFormat[0].position.x + TexWidth), (Polygon->TextureFormat[0].position.y + (TexHeight)), 255, 255, 255, 255, 1.0f, 1.0f);

	return Polygon;
}

void UpdatePolygon(SquarePolygon* &Polygon)
{
	double CentreX = 0.0f, CentreY = 0.0f, TexWidth = 0.0f, TexHeight = 0.0f;

	CentreX = Polygon->CentrePoint.x;
	CentreY = Polygon->CentrePoint.y;
	TexWidth = Polygon->TextureSize.Width;
	TexHeight = Polygon->TextureSize.Height;

	Polygon->TextureFormat[0].position = D3DXVECTOR4((CentreX - (TexWidth / 2.0f)), (CentreY - (TexHeight / 2.0f)), 1.0f, 1.0f);
	Polygon->TextureFormat[1].position = D3DXVECTOR4((Polygon->TextureFormat[0].position.x + TexWidth), (Polygon->TextureFormat[0].position.y), 1.0f, 1.0f);
	Polygon->TextureFormat[2].position = D3DXVECTOR4((Polygon->TextureFormat[0].position.x), (Polygon->TextureFormat[0].position.y + (TexHeight)), 1.0f, 1.0f);
	Polygon->TextureFormat[3].position = D3DXVECTOR4((Polygon->TextureFormat[0].position.x + TexWidth), (Polygon->TextureFormat[0].position.y + (TexHeight)), 1.0f, 1.0f);
}

void DestoryPolygon(SquarePolygon* &spPolygon)
{
	if (spPolygon != NULL)
	{
		if (spPolygon->TextureFormat != NULL)
		{
			delete[]spPolygon->TextureFormat;
			spPolygon->TextureFormat = NULL;
		}

		delete spPolygon;
		spPolygon = NULL;
	}
}

void Set_TextureCoor(SquarePolygon* &spPolygon,double x1, double y1, double x2, double y2)
{
	spPolygon->TextureFormat[0].TextureCoor = D3DXVECTOR2(x1, y1);
	spPolygon->TextureFormat[1].TextureCoor = D3DXVECTOR2(x2, y1);
	spPolygon->TextureFormat[2].TextureCoor = D3DXVECTOR2(x1, y2);
	spPolygon->TextureFormat[3].TextureCoor = D3DXVECTOR2(x2, y2);
}