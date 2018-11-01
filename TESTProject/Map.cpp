#include "Map.h"
#include <stdio.h>
#include <stdlib.h>

MapManage::MapManage()
{
	ppMapObj = NULL;
	pMapScene = NULL;
	iWidth = 0;
	iHeight = 0;
	for (int i = 0; i < MAP_SCENE_COUNT; i++)
	{
		sMapScene[i].eMapSceneIndex = MSI_NONE;
	}
	sMapScene[0].eMapSceneIndex = MSI_TUTORIAL;
	sMapScene[0].pFilePath = "./Map/Map_Tutorial.csv";
}
MapManage::~MapManage()
{

}

BOOL MapManage::Map_Load(MapSceneIndex Index)
{
	FILE* fp = NULL;

	for (int i = 0; i < MAP_SCENE_COUNT; i++)
	{
		if (sMapScene[i].eMapSceneIndex == Index)
		{
			fp = fopen(sMapScene[i].pFilePath, "r");
			break;
		}
	}

	if (fp == NULL)
	{
		return FALSE;
	}

	fseek(fp, 0, SEEK_SET);

	putw(iWidth, fp);
}