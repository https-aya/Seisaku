#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
	{
		ChangeWindowMode(TRUE);

		if (DxLib_Init() == -1)
		{
			return -1;
		}

		SetDrawScreen(DX_SCREEN_BACK);

		Player_Initialize();
		Enemy_Initialize();

		while (ProcessMessage() != -1)
		{
			ClearDrawScreen();

			Player_Update();

			Enemy_Update();

			ScreenFlip();
		}
	
		DxLib_End();

		return 0;
	}