#pragma once

#define D_ERROR	(-1)
#define D_NORMALITY	(0)

enum GAME_MODE
{
	E_TITLE,
	E_GAMEMAIN,
	E_RANKING,
	E_SKIL,
	E_END,
	E_MODE_MAX
};

void SceneManager_Initialize(GAME_MODE mode);	//初期化処理
void SceneManager_Update();						//更新処理
void SceneManager_Draw();						//描画処理
void Change_Scene(GAME_MODE mode);				//シーン変更処理
int ErrorCheck();								//エラーチェック