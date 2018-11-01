#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

#include <Windows.h>

typedef enum EGameState {
	EGS_TITLE = 0,
	EGS_STAGE01,
	EGS_RESULT
}GameState;

void SetRewardData(int Number);
void UpdateGameLogic(HINSTANCE hInstance, HWND hWnd);
void EnterGameStage(GameState State, HINSTANCE hInstance, HWND hWnd);
void GameStage_Init(HINSTANCE hInstance, HWND hWnd);
void GameStage_Final(HINSTANCE hInstance, HWND hWnd);
void GameStage_Render(void);
void GameStage_Timer(WPARAM wParam);
GameState GameStage_Get(void);


#endif // !_GAMEFRAME_H