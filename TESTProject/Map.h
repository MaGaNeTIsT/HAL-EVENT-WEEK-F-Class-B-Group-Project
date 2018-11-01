#ifndef _MAP_H
#define _MAP_H

#include <Windows.h>
#include "Common.h"

class MapBasic
{
public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Finalize(void);
};

typedef enum EMapUnitType {
	MUT_NONE = 0,
	MUT_LAND
}MapUnitType;

typedef struct SMapUnitProperty {
	MapUnitType eType;
	bool bLand;
	bool bCross;
}MapUnitProperty;

typedef struct SMapScreen {
	UINT Index;
	double fWidth;
	double fHeight;
	MapUnitProperty sBackGroundProperty;
	MapBasic* pBackGround;
	MapUnitProperty sStaticObjectProperty;
	MapBasic* pStaticObject;
	MapUnitProperty sActiveObjectProperty;
	MapBasic* pActiveObject;
}MapScreen;

typedef struct SMapArea {
	UINT Index;
	int iWidth;
	int iHeight;
	MapScreen* pMapScreen;
}MapArea;

typedef struct SMapBlock {
	UINT Index;
	int iWidth;
	int iHeight;
	MapArea* pMapArea;
}MapBlock;

class MapManage {

public:

	typedef enum EMapSceneIndex {
		MSI_NONE = 0,
		MSI_TUTORIAL
	}MapSceneIndex;

	typedef struct SMapScene {
		MapSceneIndex eMapSceneIndex;
		LPCSTR pFilePath;
	}MapScene;

	MapManage();
	~MapManage();

	BOOL Map_Load(MapSceneIndex Index);

private:

	int** ppMapObj;

	int iWidth;
	int iHeight;

	MapScene* pMapScene;
	MapScene sMapScene[MAP_SCENE_COUNT];
};

#endif // !_MAP_H