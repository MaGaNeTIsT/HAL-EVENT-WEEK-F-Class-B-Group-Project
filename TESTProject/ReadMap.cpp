#include "ReadMap.h"
#include <fstream>
#include <iostream>
ReadMap::ReadMap(const char* filepath)
{
	ReadFile(filepath);
}


ReadMap::~ReadMap()
{
}

bool ReadMap::ReadFile(const char * FilePath)
{
	std::ifstream File;
	File.open(FilePath);

	if (!File.is_open())
	{
		return false;
	}

	std::string Str;
	int iLineIndex = 0;
	while (std::getline(File, Str))
	{
		if (Str.empty())
		{
			continue;
		}

		// 获取第一行  
		// Get First Line,eg."40,30------"
		if (iLineIndex == 0)
		{
			if (!GetMapInfo(Str))
			{
				return false;
			}
		}
		else
		{
			std::vector<int> line;
			int LineElem = 0;
			for (int i = 0; i < Str.length(); ++i)
			{
				if (Str[i] == ',')
				{
					line.push_back(LineElem);
					LineElem = 0;
				}
				else
				{
					LineElem = LineElem * 10 + Str[i] - '0';
				}
			}
			Map.push_back(line);
		}
		iLineIndex++;
	}

	return true;
}

bool ReadMap::GetMapInfo(const std::string& MapInfo)
{
	int StrLen = MapInfo.length();
	bool bGetLineNum = true;
	for (int i = 0; i < StrLen; ++i)
	{
		if (MapInfo[i] == ',')
		{
			if (!bGetLineNum)
			{
				break;
			}
			bGetLineNum = false;
			continue;
		}
		if (bGetLineNum)
		{
			LineNum = LineNum * 10 + MapInfo[i] - '0';
		}
		else
		{
			LineElemNum = LineElemNum * 10 + MapInfo[i] - '0';
		}
	}
	return true;
}

void ReadMap::Test()
{
	for (std::vector<int>& line : Map)
	{
		for (int& elem : line)
		{
			std::cout << elem << ";";
		}
		std::cout<<std::endl;
	}
}