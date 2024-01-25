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
			Change_Scene(E_RANKING);
			break;
		case 3:
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
		if (cursor_number >= 3)
		{
			cursor_number = 3;
		}
		else
		{
			cursor_number++;
		}
	}
}

void TitleScene_Draw()
{
	switch (cursor_number)
	{
	case 0:
		SetFontSize(20);
		DrawFormatString(340, 340, 0xff0000, "GAME START");
		SetFontSize(16);
		DrawFormatString(340, 380, 0xffffff, "SKIL CHANGE");
		DrawFormatString(340, 420, 0xffffff, "RANKING");
		DrawFormatString(340, 460, 0xffffff, "END");
		break;
	case 1:
		SetFontSize(20);
		DrawFormatString(340, 380, 0xff0000, "SKIL CHANGE");
		SetFontSize(16);
		DrawFormatString(340, 340, 0xffffff, "GAME START");	
		DrawFormatString(340, 420, 0xffffff, "RANKING");
		DrawFormatString(340, 460, 0xffffff, "END");
		break;
	case 2:
		SetFontSize(20);
		DrawFormatString(340, 420, 0xff0000, "RANKING");
		SetFontSize(16);
		DrawFormatString(340, 340, 0xffffff, "GAME START");
		DrawFormatString(340, 380, 0xffffff, "SKIL CHANGE");
		DrawFormatString(340, 460, 0xffffff, "END");
		break;
	case 3:
		SetFontSize(20);
		DrawFormatString(340, 460, 0xff0000, "END");
		SetFontSize(16);
		DrawFormatString(340, 340, 0xffffff, "GAME START");
		DrawFormatString(340, 380, 0xffffff, "SKIL CHANGE");
		DrawFormatString(340, 420, 0xffffff, "RANKING");
		break;
	}
	
}