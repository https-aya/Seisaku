#include "GameMainScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Castle.h"
#include "Enemy.h"
#include "Field.h"
#include "Skil.h"
#include "DxLib.h"

int WaveCount;
int Star_B;
int Star_Y;
int AttackRange_Image;
int AttackSpeed_Image;
int AttackDamage_Image;
int Skil_Image;

int GameMainScene_Initialize()
{
	WaveCount = 1;
	Star_B = LoadGraph("image/hosi_B.png");
	Star_Y = LoadGraph("image/hosi_Y.png");
	AttackRange_Image = LoadGraph("image/AttackR.png");
	AttackSpeed_Image = LoadGraph("image/AttackS.png");
	AttackDamage_Image = LoadGraph("image/AttackD.png");
	switch (GetSkilnum())
	{
	case 0:
		Skil_Image = LoadGraph("image/SkillWall.png");
		break;
	case 1:
		Skil_Image = LoadGraph("image/SkillTimeStop.png");
		break;
	}
	Castle_Initialize();
	Player_Initialize();
	Enemy_Initialize();
	Skil_Initialize();
	enemycount_clear();
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
		if (GetEnemyattack_count() + Get_enemykill() >= MAX_ENEMY * Get_Wave())
		{
			WaveCount++;
			WaveUp();
			Enemy_Initialize();
		}
	}
	if (Get_enemycount() >= 4 * (Get_PLv() + 1))
	{
		play_change(0);
		enemycount_clear();
	}
	if (Castle_GetHp() <= 0)
	{
		play_change(0);
		Change_Scene(E_RANKING);
	}
}

void GameMainScene_Draw()
{

	DrawExtendGraph(500, 190, 550, 240, AttackRange_Image, FALSE);
	DrawExtendGraph(500, 240, 550, 290, AttackSpeed_Image, FALSE);
	DrawExtendGraph(500, 290, 550, 340, AttackDamage_Image, FALSE);
	for (int i = 0; i < 5 - Get_ARLv(); i++)
	{
		DrawGraph(650 - (25 * i), 200, Star_B, FALSE);
	}
	for (int i = 0; i < Get_ARLv(); i++)
	{
		DrawGraph(550 + (25 * i), 200, Star_Y, FALSE);
	}
	for (int i = 0; i < 5 - Get_ASLv(); i++)
	{
		DrawGraph(650 - (25 * i), 255, Star_B, FALSE);
	}
	for (int i = 0; i < Get_ASLv(); i++)
	{
		DrawGraph(550 + (25 * i), 255, Star_Y, FALSE);
	}
	for (int i = 0; i < 5 - Get_ADLv(); i++)
	{
		DrawGraph(650 - (25 * i), 310, Star_B, FALSE);
	}
	for (int i = 0; i < Get_ADLv(); i++)
	{
		DrawGraph(550 + (25 * i), 310, Star_Y, FALSE);
	}
	DrawFormatString(500, 400, 0xffffff, "%d", Get_enemycount());
}
