#include "GameMainScene.h"
#include "Player.h"
#include "Castle.h"
#include "Enemy.h"
#include "Skil.h"
#include "DxLib.h"

int WaveCount;
int Star_B;
int Star_Y;
int AttackRange_Image;
int AttackSpeed_Image;
int AttackDamage_Image;

int GameMainScene_Initialize()
{
	WaveCount = 1;
	Star_B = LoadGraph("image/hosi_B.png");
	Star_Y = LoadGraph("image/hosi_Y.png");
	AttackRange_Image = LoadGraph("image/AttackR.png");
	AttackSpeed_Image = LoadGraph("image/AttackS.png");
	Castle_Initialize();
	Player_Initialize();
	Enemy_Initialize();
	Skil_Initialize();
	return 0;
}
void GameMainScene_Update()
{
	Player_Update();
	if (Get_play() != 0)
	{
		Enemy_Update();
		Castle_Update();
		Skil_Update();
		GameMainScene_Draw();
		DrawFormatString(800, 200, 0xffffff, "%d", Get_Score(), TRUE);
		DrawFormatString(800, 240, 0xffffff, "%d", WaveCount, TRUE);
		if (GetEnemykill() >= MAX_ENEMY * Get_Wave())
		{
			WaveUp();
			play_change();
			Enemy_Initialize();
		}
	}
}

void GameMainScene_Draw()
{
	DrawExtendGraph(500, 90, 550, 140, AttackRange_Image, FALSE);
	DrawExtendGraph(500, 140, 550, 190, AttackSpeed_Image, FALSE);
	for (int i = 0; i < 5 - Get_ARLv(); i++)
	{
		DrawGraph(650 - (25 * i), 100, Star_B, FALSE);
	}
	for (int i = 0; i < Get_ARLv(); i++)
	{
		DrawGraph(550 + (25 * i), 100, Star_Y, FALSE);
	}
	for (int i = 0; i < 5 - Get_ASLv(); i++)
	{
		DrawGraph(650 - (25 * i), 150, Star_B, FALSE);
	}
	for (int i = 0; i < Get_ASLv(); i++)
	{
		DrawGraph(550 + (25 * i), 150, Star_Y, FALSE);
	}
}
