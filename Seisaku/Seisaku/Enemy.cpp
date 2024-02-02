#include "Enemy.h"
#include "Field.h"
#include "Castle.h"
#include "Skil.h"
#include "DxLib.h"
#include "time.h"

#define WaitTime  (300)

struct EnemyPattern
{
	char type;
	int image;
	float EnemyX;
	float EnemyY;
	int Wait;
	int waitcount;
	int HP;
};
EnemyPattern enemy[50];
int enemykill;
int enemycriatecount;
int criatedelay;

void Enemy_Initialize()
{
	enemykill = 0;
	enemycriatecount = 0;
	criatedelay = 0;
}

void Enemy_Update()
{
	if (enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay == 0)
	{
		srand((unsigned)time(NULL));
		int k;
		k = rand() % 11;
		enemy[enemycriatecount].EnemyX = 20 + (TroutSize * k);
		enemy[enemycriatecount].EnemyY = 20;
		if (Check_Enemy(enemy[enemycriatecount].EnemyY / TroutSize,
			enemy[enemycriatecount].EnemyX / TroutSize) == false)
		{
			Enemy_Create(enemycriatecount);
			enemycriatecount++;
			k = rand() % 3 + 1;
			criatedelay = k * 100;
		}
	}
	else if(enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay > 0)
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

					case E_QUICK:
						enemy[k].waitcount++;
						if (enemy[k].waitcount >= 3)
						{
							while (enemy[k].HP > 0)
							{
								CastleHit(k);
								break;
							}
							enemy[k].waitcount = 0;
						}
						break;
					}

					enemy[k].Wait = 0;
				}
			}
		}
		Enemy_Draw();
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
				DrawGraph(enemy[k].EnemyX - 25, enemy[k].EnemyY - 25, enemy[k].image, FALSE);
				//DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff0000, TRUE);
				break;

			case E_QUICK:
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
				DrawGraph(enemy[k].EnemyX, enemy[k].EnemyY, enemy[k].image, FALSE);
				break;
			}
		}
		Enemy_Field(k);
	}
}

void Enemy_Create(int i)
{
	enemy[i].Wait = 0;
	int j = 3;
	if (Get_Wave() >= 3)
	{
		if (Get_Wave() >= 6)
		{
			if (Get_Wave() >= 9)
			{
				j = rand() % 11;
			}
			else
			{
				j = rand() % 9;
			}
		}
		else
		{
			j = rand() % 7;
		}
	}

	switch (j)
	{
	case 4:
	case 5:
	case 6:
		enemy[i].type = E_QUICK;
		enemy[i].waitcount = 0;
		enemy[i].HP = 2;
		break;

	case 7:
	case 8:
		enemy[i].type = E_BOME;
		enemy[i].image = LoadGraph("image/E_BOME_C.png");
		enemy[i].HP = 3;
		break;

	default:
		enemy[i].type = E_NOMAL;
		enemy[i].image = LoadGraph("image/E_BOME_C.png");
		enemy[i].HP = 1;
		break;
	}
	Enemy_Field(i);
	Enemy_Draw();
}


void Enemy_HP(int n)
{
	enemy[n].HP--;
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

void EnemykillUp()
{
	enemykill++;
}

int GetEnemykill()
{
	return enemykill;
}

void CastleHit(int k)
{
	if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == true)
	{
		if (GetSkil() != 0 && GetSkilnum() == 0)
		{
			enemy[k].HP = 0;
			enemykill++;
			Skil_Off();
		}
		else
		{
			enemy[k].HP = 0;
			enemykill++;
			Castle_Damage();
		}
	}
	else if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
	{
		Enemy_MoveField();
		enemy[k].EnemyY += TroutSize;
	}
}