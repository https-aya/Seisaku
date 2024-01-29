#include "GameMainScene.h"
#include "Player.h"
#include "Castle.h"
#include "Enemy.h"
#include "Skil.h"
#include "DxLib.h"

int WaveCount;

int GameMainScene_Initialize()
{
	WaveCount = 1;
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
	DrawFormatString(800, 240, 0xffffff, "%d", WaveCount, TRUE);
	if (GetEnemykill() >= MAX_ENEMY * Get_Wave())
	{
		WaveUp();
		ARLv_Up();
		Enemy_Initialize();
	}
}

