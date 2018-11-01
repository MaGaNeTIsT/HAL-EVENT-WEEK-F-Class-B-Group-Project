#ifndef _CIRCLE_H
#define _CIRCLE_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <d3dx9.h>
#include <Windows.h>
#include <math.h>
#include "Polygon.h"

typedef enum eCircleImpactState {
	CIS_NONE,
	CIS_LEFT,
	CIS_RIGHT,
	CIS_TOP,
	CIS_BUTTOM
}CircleImpact;

typedef enum eCircleCircleImpactState {
	CCIS_NONE,
	CCIS_IMPACTSTART,
	CCIS_IMPACTEND
}CircleCirImpact;

typedef struct Vertex2D_CircleTag {
	Vertex2D* sCircleFormat;
	double fCircleRadius;
	double fCircleFormatCount;
	double fAngle;
	double fRollSpeed;
	double fMoveSpeedX;
	double fMoveSpeedY;
	double fMass;
	CircleImpact bImpactState;
	CircleCirImpact bCircleImapct;
	BOOL bImpact;
}VertexCircle;

VertexCircle* CreateCircle(double CircleX, double CircleY, double CircleRadius, double FormatCount, double RollSpeed);
void DestoryCircle(VertexCircle* &Circle);
void DoRollCircle(VertexCircle* Circle);
CircleImpact CircleImapctScreen(VertexCircle* Circle);
void CircleImapctEffect(VertexCircle* Circle1, VertexCircle* Circle2);
BOOL DoCircleImapct(VertexCircle* Circle1, VertexCircle* Circle2);
INT CircleImapct(VertexCircle* Circle1, VertexCircle* Circle2);

#endif // !_CIRCLE_H