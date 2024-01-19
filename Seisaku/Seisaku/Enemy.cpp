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
	float EnemyX;
	float EnemyY;
	int Wait;
	int waitcount;
	int HP;
};
EnemyPattern enemy[10];
int enemykill;
int maxwave = 1;

void Enemy_Initialize()
{
	enemykill = 0;
	Enemy_Create();
	for (int k = 0; k < MAX_ENEMY * maxwave; k++)
	{
		enemy[k].Wait = 0;
	}
}

void Enemy_Update()
{
	if (GetSkilnum() == 1 && GetSkil() != 0)
	{
		for (int k = 0; k < MAX_ENEMY * maxwave; k++)
		{
			enemy[k].Wait = 0;
		}
	}
	else
	{
		for (int k = 0; k < MAX_ENEMY * maxwave; k++)
		{
			if (enemy[k].HP > 0)
			{
				enemy[k].Wait++;
				if (enemy[k].Wait > WaitTime - (2*Get_Wave()))
				{
					switch (enemy[k].type)
					{
					case E_NOMAL:
						if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == true)
						{
							if (GetSkil() != 0)
							{
								enemy[k].HP = 0;
								EnemykillUp();
								Skil_Off();
							}
							else
							{
								EnemykillUp();
								Castle_Damage();
								enemy[k].HP = 0;
							}
						}
						else if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
						{
							Enemy_MoveField();
							enemy[k].EnemyY += TroutSize;
						}
						break;

					case E_QUICK:
						enemy[k].waitcount++;
						if (enemy[k].waitcount >= 3)
						{
							while (enemy[k].HP > 0)
							{
								if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == true)
								{
									if (GetSkil() != 0)
									{
										enemy[k].HP = 0;
										EnemykillUp();
										Skil_Off();
									}
									else
									{
										Castle_Damage();
										EnemykillUp();
										enemy[k].HP = 0;
									}
								}
								else if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
								{
									Enemy_MoveField();
									enemy[k].EnemyY += TroutSize;
								}
								else {
									break;
								}
							}
							enemy[k].waitcount = 0;
						}
						break;
					}
					
					enemy[k].Wait = 0;
				}
				DrawFormatString(500, 50 + (20 * k), 0xffffff, "%d", k);
				DrawFormatString(520, 50 + (20 * k), 0xffffff, "%f", enemy[k].EnemyX);
			}
		}
	}
	Enemy_Draw();
}

void Enemy_Draw()
{
	for (int k = 0; k < MAX_ENEMY * maxwave; k++)
	{
		if (enemy[k].HP > 0)
		{
			switch (enemy[k].type)
			{
			case E_NOMAL:
				DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff0000, TRUE);
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
				
			}
		}
		Enemy_Field(k);
	}
}

void Enemy_Create()
{
	srand((unsigned)time(NULL));
	int k;
	int j = 3;
	for (int i = 0; i < MAX_ENEMY * maxwave; i++)
	{
		k = rand() % 11;
		enemy[i].EnemyX = 20 + (TroutSize * k);
		enemy[i].EnemyY = 20;
		if (Check_Enemy(enemy[i].EnemyY / TroutSize, enemy[i].EnemyX / TroutSize) == true)
		{
			i--;
		}
		else
		{
			if (Get_Wave() >= 3)
			{
				if (Get_Wave() >= 6)
				{
					if (Get_Wave() >= 9)
					{
						j = rand() % 7;
					}
					else
					{
						j = rand() % 9;
					}
				}
				else 
				{
					j = rand() % 11;
				}
	
			}
			switch (j)
			{
			case 0:
			case 1:
			case 2:
				enemy[i].type = E_QUICK;
				enemy[i].waitcount = 0;
				enemy[i].HP = 2;
				break;

			default:
				enemy[i].type = E_NOMAL;
				enemy[i].HP = 1;
				break;
			}
			Enemy_Field(i);
		}
	}
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

void MAXWAVEUp()
{
	if (maxwave >= 5)
	{
		maxwave = 5;
	}
	else
	{
		maxwave++;
	}
}

int GetMAXWAVE()
{
	return maxwave;
}