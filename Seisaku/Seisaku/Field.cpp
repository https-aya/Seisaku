#include "Field.h"
#include "Enemy.h"
#include "Player.h"
#include "Castle.h"
#include "io.h"
#include "DxLib.h"

FieldState Field[FieldHight][FieldWide];

int PFH;
int PFW;
int EFH;
int EFW;

void CheckDamage()
{
	for (int n = 0; n < MAX_ENEMY * GetMAXWAVE(); n++)
	{
		EFH = Enemy_GetY(n) / TroutSize;
		EFW = Enemy_GetX(n) / TroutSize;
		switch (Get_ARLv())
		{
		case 0:
			if (Field[EFH + 1][EFW] == E_Player)
			{
				EnemyDamage(n);
			}
			break;
		case 1:
			if (Field[EFH + 1][EFW] == E_Player ||
				Field[EFH + 1][EFW + 1] == E_Player ||
				Field[EFH + 1][EFW - 1] == E_Player)
			{
				EnemyDamage(n);
			}
			break;
		case 2:
			if (EFW > 0)
			{
				if (Field[EFH][EFW - 1] == E_Player)
				{
					EnemyDamage(n);
					break;
				}
			}
			if (Field[EFH + 1][EFW] == E_Player ||
				Field[EFH + 1][EFW + 1] == E_Player ||
				Field[EFH + 1][EFW - 1] == E_Player ||
				Field[EFH][EFW + 1] == E_Player)
			{
				EnemyDamage(n);
			}
			break;
		case 3:
			if (EFH > 0)
			{
				if (EFW > 0)
				{
					if (Field[EFH - 1][EFW - 1] == E_Player)
					{
						EnemyDamage(n);
						break;
					}
				}
				if (Field[EFH - 1][EFW + 1] == E_Player)
				{
					EnemyDamage(n);
					break;
				}
			}
			if (EFW > 0)
			{
				if (Field[EFH][EFW - 1] == E_Player)
				{
					EnemyDamage(n);
					break;
				}
			}
			if (Field[EFH + 1][EFW] == E_Player ||
				Field[EFH + 1][EFW + 1] == E_Player ||
				Field[EFH + 1][EFW - 1] == E_Player ||
				Field[EFH][EFW + 1] == E_Player)
			{
				EnemyDamage(n);
			}
			break;
		case 4:
		default:
			if (EFH > 0)
			{
				if (EFW > 0)
				{
					if (Field[EFH - 1][EFW - 1] == E_Player)
					{
						EnemyDamage(n);
						break;
					}
				}
				if (Field[EFH - 1][EFW + 1] == E_Player ||
					Field[EFH - 1][EFW] == E_Player)
				{
					EnemyDamage(n);
					break;
				}
			}
			if (EFW > 0)
			{
				if (Field[EFH][EFW - 1] == E_Player)
				{
					EnemyDamage(n);
					break;
				}
			}
			if (Field[EFH + 1][EFW] == E_Player ||
				Field[EFH + 1][EFW + 1] == E_Player ||
				Field[EFH + 1][EFW - 1] == E_Player ||
				Field[EFH][EFW + 1] == E_Player)
			{
				EnemyDamage(n);
			}
			break;
		
		}
	}
}

void Field_Draw()
{
	int i;
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
			if (j == FieldWide - 1 )
			{
				Field[i][j] = E_Wall;		//壁状態にする
				DrawFormatString(j * TroutSize, i * TroutSize, 0xffffff, "9");
			}
			else if (i == FieldHight - 1)
			{
				Field[i][j] = E_Castle;
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

int Check_Castile(int h, int w)
{
	if (Field[h][w] == E_Castle)
	{
		return true;
	}
	return false;
}

void Enemy_MoveField()
{
	int i, j;
	for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
	{
		i = Enemy_GetY(k) / TroutSize;
		j = Enemy_GetX(k) / TroutSize;
		Field[i][j] = E_Empty;
	}
}

void Enemy_Field(int n)
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

int Check_Enemy(int h, int w)
{
	if (Field[h][w] != E_Empty)
	{
		return true;
	}
	return false;
}

void Player_MoveField()
{
	PFH = Player_GetY() / TroutSize;
	PFW = Player_GetX() / TroutSize;
	Field[PFH][PFW] = E_Empty;
}

void Player_Field()
{
	PFH = Player_GetY() / TroutSize;
	PFW = Player_GetX() / TroutSize;
	Field[PFH][PFW] = E_Player;
}

void EnemyDamage(int n)
{
	Enemy_HP(n);
	if (Enemy_GetHP(n) == 0)
	{
		ScoreUP();
		EnemykillUp();
		Field[EFH][EFW] = E_Empty;
	}
}