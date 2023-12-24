#include "Player.h"
#include "Enemy.h"
#include "InputControl.h"
#include "io.h"
#include "DxLib.h"

FieldState Field[FieldHight][FieldWide];
FieldState Player[FieldHight][FieldWide];


float PlayerX;
float PlayerY;
int PfieldH;
int PfieldW;
int EFH;
int EFW;
int image;

void Player_Initialize()	//初期化処理
{
	PlayerX = 220;
	PlayerY = 660;
	Field_Create();
	image = LoadGraph("image/kougeki.png");
}
void Player_Update()		//更新処理
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
}
void Player_Move()			//移動処理
{

	if (InputControl::GetKeyDown(KEY_INPUT_A) == true)
	{
		if (check_overlap(PfieldW - 1, PfieldH) == TRUE
			&& PlayerX - TroutSize >= 0)
		{
			Field[PfieldH][PfieldW] = E_Empty;
			PlayerX -= TroutSize;
		}

	}
	if (InputControl::GetKeyDown(KEY_INPUT_D) == true)
	{
		if (check_overlap(PfieldW + 1, PfieldH) == TRUE)
		{
			Field[PfieldH][PfieldW] = E_Empty;
			PlayerX += TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_W) == true)
	{
		if (check_overlap(PfieldW, PfieldH - 1) == TRUE
			&& PlayerY - TroutSize >= 0)
		{
			Field[PfieldH][PfieldW] = E_Empty;
			PlayerY -= TroutSize;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_S) == true)
	{
		if (check_overlap(PfieldW, PfieldH + 1) == TRUE)
		{
			Field[PfieldH][PfieldW] = E_Empty;
			PlayerY += TroutSize;
		}
	}
}

void Player_Draw()
{
	PfieldH = PlayerY / TroutSize;
	PfieldW = PlayerX / TroutSize;
	for (int n = 0; n < MAX_ENEMY; n++)
	{
		if (Enemy_GetHP(n) > 0)
		{
			EFH = Enemy_GetY(n) / TroutSize;
			EFW = Enemy_GetX(n) / TroutSize;
			Field[EFH][EFW] = E_Enemy;
		}
		else
		{
			EFH = Enemy_GetY(n) / TroutSize;
			EFW = Enemy_GetX(n) / TroutSize;
			Field[EFH][EFW] = E_Empty;
		}

	}

	DrawCircleAA(PlayerX, PlayerY, TroutSize / 2, 100, 0xffffff, TRUE);
	Field[PfieldH][PfieldW] = E_Player;
	DrawFormatString(PfieldW * TroutSize, PfieldH * TroutSize, 0xffffff, "1");
}

void Player_Attack()
{
	if (Field[PfieldH - 1][PfieldW] == E_Enemy)
	{
		CheckDamage();
	}
}

void CheckDamage()
{
	for (int n = 0; n < MAX_ENEMY; n++)
	{
		EFH = Enemy_GetY(n) / TroutSize;
		EFW = Enemy_GetX(n) / TroutSize;
		if (Field[EFH + 1][EFW] == E_Player)
		{
			Enemy_HP(n);
		}
	}
}

void Field_Draw()
{
	float i,j;
	DrawBoxAA(0, 0, TroutSize * FieldWide, 720, 0xffffff, FALSE, 0.5f);
	for (i = 1; i < FieldWide; i++)
	{
		DrawLineAA((i * TroutSize), 0, (i * TroutSize), 720, 0xffffff, 1.0f);
	}
	for (i = 1; i < FieldHight; i++)
	{
		DrawLineAA(0, (i * TroutSize), TroutSize * FieldWide, (i * TroutSize), 0xffffff, 1.0f);
	}
}

void Field_Create()
{
	int i, j;
	for (i = 0; i < FieldHight; i++)
	{
		for (j = 0; j < FieldWide; j++)
		{

			//フィールド値の設定
			if (j == FieldWide - 1 || i == FieldHight - 1)
			{
				Field[i][j] = E_Wall;		//壁状態にする
				DrawFormatString(j * TroutSize, i * TroutSize, 0xffffff, "9");
			}
			else
			{
				Field[i][j] = E_Empty;	//空状態にする
				DrawFormatString(j * TroutSize, i * TroutSize, 0xffffff, "0");
			}
		}
	}
}

int check_overlap(int x, int y)
{
	if (Field[y][x] != E_Empty)
	{
		return FALSE;
	}

	return TRUE;
}

void Enemy_MoveField()
{
	int i, j;
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		i = Enemy_GetY(k) / TroutSize;
		j = Enemy_GetX(k) / TroutSize;
		Field[i][j] = E_Empty;
	}
}