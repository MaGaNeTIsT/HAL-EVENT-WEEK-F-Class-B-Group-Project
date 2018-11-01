#include "TextPrint.h"
#include "MyDirect.h"
#include <tchar.h>
//#include <string.h>

static LPD3DXFONT g_pTextFont[TEXTFONT_COUNT];

void TextFont_Initialize(void)
{
	for (int i = 0; i < TEXTFONT_COUNT; i++)
	{
		g_pTextFont[i] = NULL;
	}
}

bool CreateTextFont(UINT Index, INT Height, UINT Width, UINT Weight, BOOL Italic, LPCTSTR FontName)
{
	HRESULT hr;

	if (g_pTextFont[Index] != NULL)
	{
		MessageBox(NULL, "Font Index Exist", "WARNING", MB_OK);
		return FALSE;
	}
	hr = D3DXCreateFont(MyDirect3D_GetDevice(), Height, Width, Weight, D3DX_DEFAULT, Italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, FontName, &g_pTextFont[Index]);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Font Create Error", "WARNING", MB_OK);
		return FALSE;
	}
	return TRUE;
}

void TextFont_Finalize(void)
{
	for (int i = 0; i < TEXTFONT_COUNT; i++)
	{
		if (g_pTextFont[i] != NULL)
		{
			g_pTextFont[i]->Release();
			g_pTextFont[i] = NULL;
		}
	}
}

LPD3DXFONT GetTextFontPtr(UINT Index)
{
	return g_pTextFont[Index];
}

TextPrintData* SetTextData(UINT FontIndex, LPCTSTR Text, LONG x, LONG y, LONG Width, LONG Height, D3DCOLOR Color)
{
	if (g_pTextFont[FontIndex] == NULL)
	{
		return NULL;
	}
	TextPrintData* TextData = new TextPrintData;

	TextData->pFont = g_pTextFont[FontIndex];
	TextData->pText = Text;
	TextData->sRect.left = x;
	TextData->sRect.top = y;
	TextData->sRect.right = x + Width;
	TextData->sRect.bottom = y + Height;
	TextData->Color = Color;
	TextData->iCount = _tcslen(Text);

	return TextData;
}

void DestoryTextData(TextPrintData* &pTextData)
{
	if (pTextData != NULL)
	{
		delete pTextData;
		pTextData = NULL;
	}
}

int TextPrint(UINT FontIndex, TextPrintData* Text, DWORD Format)
{ 	
	g_pTextFont[FontIndex]->DrawText(NULL, (Text->pText), (-1), (&(Text->sRect)), (Format), (Text->Color));
	return 1;
}