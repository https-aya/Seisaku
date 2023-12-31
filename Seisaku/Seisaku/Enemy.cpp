#include "Enemy.h"
#include "Field.h"
#include "Castle.h"
#include "DxLib.h"
#include "time.h"



#define WaitTime  (100)

struct EnemyPattern
{
	char type;
	float EnemyX;
	float EnemyY;
	int Wait;
	int HP;
};
EnemyPattern enemy[MAX_ENEMY];

void Enemy_Initialize()
{
	Enemy_Create();
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		enemy[k].Wait = 0;
	}
}

void Enemy_Update()
{
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		if(enemy[k].HP > 0)
		{
			enemy[k].Wait++;
			if (enemy[k].Wait > WaitTime)
			{
				if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == true)
				{
					Castle_Damage();
					enemy[k].HP--;
				}
				else if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize;
				}
				enemy[k].Wait = 0;
			}
			//DrawFormatString(500, 50 + (20 * k), 0xffffff, "%d", enemy[k].HP);
			/*DrawFormatString(520, 50 + (20 * k), 0xffffff, "%f", enemy[k].EnemyX);*/
		}
	}
	Enemy_Draw();
}

void Enemy_Draw()
{
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		if (enemy[k].HP > 0)
		{
			DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff0000, TRUE);
			Enemy_Field(k);
		}
	}
}

void Enemy_Create()
{
	srand((unsigned)time(NULL));
	int k;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		k = rand() % 11;
		enemy[i].EnemyX = 20 + (TroutSize * k);
		enemy[i].EnemyY = 20;
		enemy[i].HP = 1;
		if (Check_Enemy(enemy[i].EnemyY / TroutSize, enemy[i].EnemyX / TroutSize) == true)
		{
			i--;
		}
		else
		{
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