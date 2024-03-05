#include "Enemy.h"
#include "Player.h"
#include "Field.h"
#include "Castle.h"
#include "Skil.h"
#include "DxLib.h"


#define WaitTime  (20)

struct EnemyPattern
{
	char type;
	int image;
	float EnemyX;
	float EnemyY;
	int Wait;
	int waitcount;
	int HP;
	float enemy_vectol_X;
	float enemy_vectol_Y;
};
EnemyPattern enemy[50];
int enemyattack_count;
int enemycriatecount;
int criatedelay;

void Enemy_Initialize()
{
	enemyattack_count = 0;
	enemycriatecount = 0;
	criatedelay = 0;
	enemykill_clear();
}

void Enemy_Update()
{
	if (Get_play() == 1)
	{
		if (enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay == 0)
		{
			int k;
			k = GetRand(10);
			enemy[enemycriatecount].EnemyX = 20 + (TroutSize * k);
			enemy[enemycriatecount].EnemyY = 20;
			if (Check_Enemy(enemy[enemycriatecount].EnemyY / TroutSize,
				enemy[enemycriatecount].EnemyX / TroutSize) == FALSE)
			{
				Enemy_Create(enemycriatecount);
				enemycriatecount++;
				k = GetRand(5) + 1;
				criatedelay = k * 60 - (2 * Get_Wave());
			}
		}
		else if (enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay > 0)
		{
			criatedelay--;
		}
		if (GetSkilnum() == 1 && GetSkil() != 0)
		{
			for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
			{
				enemy[k].Wait = 0;
			}
		}
		else
		{
			for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
			{
				if (GetSkilnum() == 2 && GetSkil() != 0)
				{
					if (Player_GetX() / TroutSize != enemy[k].EnemyX / TroutSize || Player_GetY() / TroutSize != enemy[k].EnemyY / TroutSize)
					{
						if (enemy[k].HP > 0)
						{
							enemy[k].Wait++;
							if (enemy[k].Wait > WaitTime - (2 * Get_Wave()))
							{
								CastleHit(k);
								enemy[k].Wait = 0;
							}
						}
					}
				}
				else
				{
					if (enemy[k].HP > 0)
					{
						enemy[k].Wait++;
						if (enemy[k].Wait > WaitTime - (2 * Get_Wave()))
						{
							switch (enemy[k].type)
							{
							case E_NOMAL:
								CastleHit(k);
								break;

							case E_CROSS:
								CastleHit(k);
								break;

							case E_BOME:
								CastleHit(k);
								break;

							}

							enemy[k].Wait = 0;
						}
					}
				}
			}
			Enemy_Draw();
		}
	}
}

void Enemy_Draw()
{
	for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
	{
		if (enemy[k].HP > 0)
		{
			switch (enemy[k].type)
			{
			case E_NOMAL:
				DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff0000, TRUE);
				break;

			case E_CROSS:
				if (enemy[k].HP > 1)
				{
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x00ff00, TRUE);
					break;
				}
				else
				{
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x0000ff, TRUE);
					break;
				}
			case E_BOME:
				switch (enemy[k].HP)
				{
				case 3:
					enemy[k].image = LoadGraph("image/E_BOME_C.png");
					break;
				case 2:
					enemy[k].image = LoadGraph("image/E_BOME2.png");
					break;
				case 1:
					enemy[k].image = LoadGraph("image/E_BOME3.png");
					break;
				}
				DrawExtendGraph(enemy[k].EnemyX - 20, enemy[k].EnemyY - 20, enemy[k].
					EnemyX + 20, enemy[k].EnemyY + 20, enemy[k].image, TRUE);
				break;
			}
		}
		Enemy_Field(k);
	}
}

void Enemy_Create(int i)
{
	enemy[i].Wait = 0;
	int j = 0;
	if (Get_Wave() >= 3)
	{
		if (Get_Wave() >= 6)
		{
			if (Get_Wave() >= 9)
			{
				if (Get_Wave() >= 12)
				{
					j = rand() % 15;
				}
				else
				{
					j = rand() % 12;
				}
			}
			else
			{
				j = rand() % 9;
			}
		}
		else
		{
			j = rand() % 6;
		}
	}

	switch (j)
	{
	case 3:
	case 4:
	case 5:
		enemy[i].type = E_CROSS;
		enemy[i].enemy_vectol_X = TroutSize;
		enemy[i].enemy_vectol_Y = TroutSize;
		enemy[i].HP = 2;
		break;

	case 6:
	case 7:
	case 8:
		enemy[i].type = E_BOME;
		enemy[i].HP = 3;
		break;

	

	default:
		enemy[i].type = E_NOMAL;
		enemy[i].HP = 1;
		break;
	}
	Enemy_Field(i);
	Enemy_Draw();
}


void Enemy_DecreaseHP(int n,int d)
{
	enemy[n].HP -= d;
}

int Enemy_GetHP(int n)
{
	return enemy[n].HP;
}

float Enemy_GetX(int n)
{
	return enemy[n].EnemyX;
}

float Enemy_GetY(int n)
{
	return enemy[n].EnemyY;
}

int GetEnemyattack_count()
{
	return enemyattack_count;
}

void CastleHit(int k)
{
	if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == TRUE)
	{
		if (GetSkil() != 0 && GetSkilnum() == 0)
		{
			enemy[k].HP = 0;
			enemyattack_count++;
			Skil_Off();
		}
		else
		{
			enemy[k].HP = 0;
			enemyattack_count++;
			Castle_Damage();
		}
	}
	else
	{
		Enemy_Move(k,GetSkil(),GetSkilnum());
	}
}

void Enemy_Move(int k,int skil,int skilnum)
{
	if (skilnum==2 && skil != 0)
	{
		if (check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize)) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize)) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize), (enemy[k].EnemyX / TroutSize) + 1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize)+1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize)) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize) - 1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) , (enemy[k].EnemyX / TroutSize) - 1) == FALSE)
		{
			Enemy_MoveField();
			if (Player_GetX() > enemy[k].EnemyX)
			{
				enemy[k].EnemyX += TroutSize;
			}
			else if (Player_GetX() < enemy[k].EnemyX)
			{
				enemy[k].EnemyX -= TroutSize;
			}
			if (Player_GetY() > enemy[k].EnemyY)
			{
				enemy[k].EnemyY += TroutSize;
			}
		}
	}
	else
	{
		switch (enemy[k].type)
		{
		case E_CROSS:
			if (enemy[k].enemy_vectol_X == TroutSize && check_overlap((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == TRUE || enemy[k].enemy_vectol_X == -TroutSize && check_overlap((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
			{
				Enemy_MoveField();
				enemy[k].EnemyX += enemy[k].enemy_vectol_X;
				enemy[k].EnemyY += enemy[k].enemy_vectol_Y;
			}
			if (check_overlap((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE && check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE)
			{
				enemy[k].enemy_vectol_X = -TroutSize;
			}
			if (check_overlap((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE && check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE || enemy[k].EnemyX - TroutSize <= 0)
			{
				enemy[k].enemy_vectol_X = TroutSize;
			}
			break;
		default:
			if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
			{
				Enemy_MoveField();
				enemy[k].EnemyY += TroutSize;
			}
			break;
		}
	}
}