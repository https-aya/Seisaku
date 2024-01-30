#include "Player.h"
#include "Field.h"
#include "InputControl.h"
#include "io.h"
#include "Skil.h"
#include "DxLib.h"

#define SkilCount (600)

float PlayerX;
float PlayerY;
int PfieldH;
int PfieldW;
int image;
int score;
int ARLv;
int ASLv;
float skillife;
float skilspan;
float attackspan;

void Player_Initialize()	//‰Šú‰»ˆ—
{
	PlayerX = 220;
	PlayerY = 660;
	score = 0;
	ARLv = 0;
	ASLv = 0;
	skillife = 0;
	skilspan = 0;
	attackspan = 0;
	Field_Create();
	image = LoadGraph("image/kougeki.png");
}
void Player_Update()		//XVˆ—
{
	Field_Draw();
	InputControl::Update();
	Player_Move();
	Player_Draw();
	if (InputControl::GetKeyDown(KEY_INPUT_J) == true && attackspan <= 0)
	{
		Player_Attack();
		attackspan = 30 - (ASLv * 20);
	}
	if (attackspan > 0)
	{
		DrawGraph(PlayerX - 20, PlayerY - 60, image, TRUE);
		attackspan--;
	}
	if (InputControl::GetKeyDown(KEY_INPUT_K) == true && skilspan <= 0)
	{
		Skil_On();
		skilspan = 600;
	}
	if (GetSkil() == 1)
	{
		skillife++;
		if (skillife >= SkilCount)
		{
			Skil_Off();
			skillife = 0;
		}
	}
	if (GetSkil() == 0 && skilspan > 0)
	{
		skilspan--;
	}
}
void Player_Move()			//ˆÚ“®ˆ—
{

	if (InputControl::GetKeyDown(KEY_INPUT_A) == true && attackspan <= 0)
	{
		if (check_overlap(PfieldW - 1, PfieldH) == TRUE
			&& PlayerX - TroutSize >= 0)
		{
			Player_MoveField();
			PlayerX -= TroutSize;
		}

	}
	if (InputControl::GetKeyDown(KEY_INPUT_D) == true && attackspan <= 0)
	{
		if (check_overlap(PfieldW + 1, PfieldH) == TRUE)
		{
			Player_MoveField();
			PlayerX += TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_W) == true && attackspan <= 0)
	{
		if (check_overlap(PfieldW, PfieldH - 1) == TRUE
			&& PlayerY - TroutSize >= 0)
		{
			Player_MoveField();
			PlayerY -= TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_S) == true && attackspan <= 0)
	{
		if (check_overlap(PfieldW, PfieldH + 1) == TRUE)
		{
			Player_MoveField();
			PlayerY += TroutSize;
		}
	}
}

void Player_Draw()
{
	PfieldH = PlayerY / TroutSize;
	PfieldW = PlayerX / TroutSize;
	Player_Field();
	DrawCircleAA(PlayerX, PlayerY, TroutSize / 2, 100, 0xffffff, TRUE);
	DrawFormatString(500,50, 0xffffff, "%0.0f",skilspan/10);
}

void Player_Attack()
{
	CheckDamage();
}

float Player_GetX()
{
	return PlayerX;
}

float Player_GetY()
{
	return PlayerY;
}

void ScoreUP()
{
	score += 50;
}

int Get_Score()
{
	return score;
}

void ARLv_Up()
{
	if (ARLv < 5)
	{
		ARLv++;
	}
}

int Get_ARLv()
{
	return ARLv;
}