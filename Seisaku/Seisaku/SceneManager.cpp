#include "SceneManager.h"
#include "TitleScene.h"
#include "EndScene.h"
#include "GameMainScene.h"
#include "Skil.h"
#include "DxLib.h"

GAME_MODE game_mode;
GAME_MODE next_mode;
int read_error;

void SceneManager_Initialize(GAME_MODE mode)
{
	read_error = D_NORMALITY;
	switch (mode)
	{
	case E_TITLE:
		read_error = TitleScene_Initialize();
		break;

	case E_GAMEMAIN:
		read_error = GameMainScene_Initialize();
		break;

	case E_SKIL:
		read_error = Skil_ChangeInitialize();
		break;

	case E_END:
	default:
		EndScene_Initialize;
		break;
	}

	game_mode = mode;
	next_mode = game_mode;
}

void SceneManager_Update()
{
	if (game_mode != next_mode)
	{
		SceneManager_Initialize(next_mode);
	}

	switch (game_mode)
	{
	case E_TITLE:
		TitleScene_Update();
		break;
	case E_GAMEMAIN:
		GameMainScene_Update();
		break;
	case E_SKIL:
		Skil_ChangeUpdate();
		break;

	case E_END:
	default:
		EndScene_Update();
		break;
	}
}

void SceneManager_Draw()
{
	switch (game_mode)
	{
	case E_TITLE:
		TitleScene_Draw();
		break;

	case E_SKIL:
		Skil_ChangeDraw();
		break;

	case E_END:
		EndScene_Draw();
		break;
	}
}

void Change_Scene(GAME_MODE mode)
{
	next_mode = mode;
}

int ErrorCheck()
{
	if (Get_EndTime() == TRUE)
	{
		read_error = D_ERROR;
	}

	return read_error;
}