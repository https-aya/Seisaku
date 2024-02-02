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
int ADLv;
int ASLv;
float skillife;
float skilspan;
float attackspan;
int play;
int AR_Image;
int AS_Image;
int cursor;

void Player_Initialize()	//‰Šú‰»ˆ—
{
	play = 1;
	cursor = 0;
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
	AR_Image = LoadGraph("image/AttackR.png");
	AS_Image = LoadGraph("image/AttackS.png");
}
void Player_Update()		//XVˆ—
{
	InputControl::Update();
	if (play != 0)
	{
		Field_Draw();
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
	else
	{
		Draw_LvUp();
		LvUp_Move();
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

void Draw_LvUp()
{
	DrawGraph(200, 200, AR_Image, FALSE);
	DrawGraph(400, 200, AS_Image, FALSE);
	switch (cursor)
	{
	case 0:
		DrawBoxAA(200, 200, 300, 300, 0xffffff, FALSE, 2.0f);
		break;
	case 1:
		DrawBoxAA(400, 200, 500, 300, 0xffffff, FALSE, 2.0f);
		break;
	}
}

void LvUp_Move()
{
	if (InputControl::GetKeyDown(KEY_INPUT_A))
	{
		if (cursor == 0)
		{
			cursor = 1;
		}
		cursor--;
	}
	if (InputControl::GetKeyDown(KEY_INPUT_D))
	{
		if (cursor == 1)
		{
			cursor = 0;
		}
		cursor++;
	}
	if (InputControl::GetKeyDown(KEY_INPUT_K))
	{
		switch (cursor)
		{
		case 0:
			ARLv++;
			break;
		case 1:
			ASLv++;
			break;
		}
		play = 1;
	}
}

int Get_ARLv()
{
	return ARLv;
}

int Get_ASLv()
{
	return ASLv;
}

void play_change()
{
	play = 0;
}

int Get_play()
{
	return play;
}