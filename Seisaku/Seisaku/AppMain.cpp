#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Castle.h"

#define SCREEN_HEIGHT (720)
#define SCREEN_WIDTH (1280)
#define SCREEN_COLORBIT (32)

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
	{
		ChangeWindowMode(TRUE);

		SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);

		if (DxLib_Init() == -1)
		{
			return -1;
		}

		SetDrawScreen(DX_SCREEN_BACK);

		Castle_Initialize();
		Player_Initialize();
		Enemy_Initialize();

		while ( Castle_GetHp() != 0)
		{
			ClearDrawScreen();

			Player_Update();

			Enemy_Update();

			Castle_Update();

			ScreenFlip();
		}
	
		DxLib_End();

		return 0;
	}