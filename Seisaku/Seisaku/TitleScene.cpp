#include"TitleScene.h"
#include"InputControl.h"
#include"SceneManager.h"
#include"DxLib.h"

int cursor_number;
int TitleScene;

int TitleScene_Initialize()
{
	cursor_number = 0;
	return 0;
}

void TitleScene_Update()
{
	InputControl::Update();
	if (InputControl::GetKeyDown(KEY_INPUT_J) == true)
	{
		switch (cursor_number)
		{
		case 0:
			Change_Scene(E_GAMEMAIN);
			break;
		case 1:
			Change_Scene(E_SKIL);
			break;
		case 2:
		default:
			Change_Scene(E_END);
			break;
		}
	}

	if (InputControl::GetKeyDown(KEY_INPUT_W) == true)
	{
		if (cursor_number <= 0)
		{
			cursor_number = 0;
		}
		else
		{
			cursor_number--;
		}
	}

	if (InputControl::GetKeyDown(KEY_INPUT_S) == true)
	{
		if (cursor_number >= 2)
		{
			cursor_number = 2;
		}
		else
		{
			cursor_number++;
		}
	}
}

void TitleScene_Draw()
{
	DrawFormatString(340, 340, 0xffffff, "GAME START");
	DrawFormatString(340, 380, 0xffffff, "SKIL CHANGE");
	DrawFormatString(340, 420, 0xffffff, "END");
	DrawCircle(320, 345 + (cursor_number * 40), 10, GetColor(255, 0, 0));
}