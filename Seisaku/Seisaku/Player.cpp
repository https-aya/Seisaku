#include "Player.h"
#include "Field.h"
#include "InputControl.h"
#include "io.h"
#include "Skil.h"
#include "DxLib.h"

float PlayerX;
float PlayerY;
int PfieldH;
int PfieldW;
int image;

void Player_Initialize()	//‰Šú‰»ˆ—
{
	PlayerX = 220;
	PlayerY = 660;
	Field_Create();
	image = LoadGraph("image/kougeki.png");
}
void Player_Update()		//XVˆ—
{
	Field_Draw();
	InputControl::Update();
	Player_Move();
	Player_Draw();
	if (InputControl::GetKeyDown(KEY_INPUT_J) == true)
	{
		DrawGraph(PlayerX - 20, PlayerY - 60, image, TRUE);
		Player_Attack();
	}
	if (InputControl::GetKeyDown(KEY_INPUT_K) == true)
	{
		Skil_On();
	}
}
void Player_Move()			//ˆÚ“®ˆ—
{

	if (InputControl::GetKeyDown(KEY_INPUT_A) == true)
	{
		if (check_overlap(PfieldW - 1, PfieldH) == TRUE
			&& PlayerX - TroutSize >= 0)
		{
			Player_MoveField();
			PlayerX -= TroutSize;
		}

	}
	if (InputControl::GetKeyDown(KEY_INPUT_D) == true)
	{
		if (check_overlap(PfieldW + 1, PfieldH) == TRUE)
		{
			Player_MoveField();
			PlayerX += TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_W) == true)
	{
		if (check_overlap(PfieldW, PfieldH - 1) == TRUE
			&& PlayerY - TroutSize >= 0)
		{
			Player_MoveField();
			PlayerY -= TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_S) == true)
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
	DrawFormatString(PfieldW * TroutSize, PfieldH * TroutSize, 0xffffff, "1");
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