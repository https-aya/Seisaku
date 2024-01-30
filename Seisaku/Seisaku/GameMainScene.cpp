#include "GameMainScene.h"
#include "Player.h"
#include "Castle.h"
#include "Enemy.h"
#include "Skil.h"
#include "DxLib.h"

int WaveCount;
int Star_B;

int GameMainScene_Initialize()
{
	WaveCount = 1;
	Star_B = LoadGraph("image/hosi_B.png");
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
	GameMainScene_Draw();
	DrawFormatString(800, 200, 0xffffff, "%d", Get_Score(), TRUE);
	DrawFormatString(800, 240, 0xffffff, "%d", WaveCount, TRUE);
	if (GetEnemykill() >= MAX_ENEMY * Get_Wave())
	{
		WaveUp();
		ARLv_Up();
		Enemy_Initialize();
	}
}

void GameMainScene_Draw()
{
	DrawGraph(500, 100, Star_B, FALSE);
}
