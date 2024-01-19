#include "GameMainScene.h"
#include "Player.h"
#include "Castle.h"
#include "Enemy.h"
#include "Skil.h"
#include "DxLib.h"

int GameMainScene_Initialize()
{
	Castle_Initialize();
	Player_Initialize();
	Enemy_Initialize();
	Skil_Initialize();
	return 0;
}
void GameMainScene_Update()
{
	Player_Update();
	Enemy_Update();
	Castle_Update();
	Skil_Update();
	DrawFormatString(800, 200, 0xffffff, "%d", Get_Score(), TRUE);
	DrawFormatString(800, 240, 0xffffff, "%d", Get_Wave(), TRUE);
	if (GetEnemykill() >= MAX_ENEMY * GetMAXWAVE())
	{
		WaveUp();
		MAXWAVEUp();
		ARLv_Up();
		Enemy_Initialize();
	}
}

