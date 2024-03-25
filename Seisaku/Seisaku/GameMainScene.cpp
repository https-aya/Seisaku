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
int wait_time;
int AttackRange_Image;
int AttackSpeed_Image;
int AttackDamage_Image;
int Skil_Image;
int lockimage;

int GameMainScene_Initialize()
{
	WaveCount = 1;
	wait_time = 0;
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
	case 2:
		Skil_Image = LoadGraph("image/SkilTarget.png");
	}
	lockimage = LoadGraph("image/SkillLock.png");
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
		DrawFormatString(500, 40, 0xffffff, "Player Level", TRUE);
		DrawFormatString(500, 60, 0xffffff, "%d", Get_PLv(), TRUE);
		DrawFormatString(500, 80, 0xffffff, "SCORE", TRUE);
		DrawFormatString(500, 100, 0xffffff, "%d", Get_Score(), TRUE);
		DrawFormatString(500, 120, 0xffffff, "WAVE", TRUE);
		DrawFormatString(500, 140, 0xffffff, "%d", WaveCount, TRUE);
		DrawGraph(500, 400, Skil_Image, FALSE);
		if (Get_SkilSpan() > 0)
		{
			DrawGraph(500, 400, lockimage, TRUE);
		}
		if (GetEnemyattack_count() + Get_enemykill() >= MAX_ENEMY * Get_Wave())
		{
			WaveCount++;
			play_change(2);
			WaveUp();
			Enemy_Initialize();
			wait_time = 450;
		}
		if (Get_play() == 2)
		{
			if (wait_time > 0)
			{
				DrawFormatString(wait_time*2, 360, 0x18ff04, "Wave%d", WaveCount);
				wait_time--;
				if (wait_time == 0)
				{
					play_change(1);
				}
			}
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
}
