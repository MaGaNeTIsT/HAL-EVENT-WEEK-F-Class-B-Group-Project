#ifndef _TEXTPRINT_H
#define _TEXTPRINT_H

#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include <Windows.h>
#include <d3dx9.h>
#include "Common.h"

typedef struct STextPrintData {
	LPD3DXFONT pFont;
	INT iCount;
	LPCTSTR pText;
	RECT sRect;
	D3DCOLOR Color;
}TextPrintData;

void TextFont_Initialize(void);
bool CreateTextFont(UINT Index, INT Height, UINT Width, UINT Weight, BOOL Italic, LPCTSTR FontName);
void TextFont_Finalize(void);
LPD3DXFONT GetTextFontPtr(UINT Index);
TextPrintData* SetTextData(UINT FontIndex, LPCTSTR Text, LONG x, LONG y, LONG Width, LONG Height, D3DCOLOR Color);
int TextPrint(UINT FontIndex, TextPrintData* Text, DWORD Format);
void DestoryTextData(TextPrintData* &pTextData);

#endif // !_TEXTPRINT_H