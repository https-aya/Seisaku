#include "DxLib.h"
#include "Castle.h"
#include "SceneManager.h"

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

		SceneManager_Initialize(E_TITLE);


		while (ErrorCheck() == D_NORMALITY && ProcessMessage() == 0)
		{
			ClearDrawScreen();

			SceneManager_Update();

			SceneManager_Draw();

			ScreenFlip();
		}
	
		DxLib_End();

		return 0;
	}