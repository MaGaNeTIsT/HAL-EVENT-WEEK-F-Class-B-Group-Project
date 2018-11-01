#pragma once
#include <string>
#include <vector>
class ReadMap
{
public:
	ReadMap(const char* FilePath);
	~ReadMap();
	void Test();

protected:
	bool ReadFile(const char* FilePath);

	// ���ڻ�ȡ��������
	bool GetMapInfo(const std::string& MapInfo);

private:
	std::vector<std::vector<int>> Map;
	int LineNum;
	int LineElemNum;

};