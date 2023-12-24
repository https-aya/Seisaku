#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#include "time.h"



#define WaitTime  (200)

struct EnemyPattern
{
	char type;
	float EnemyX;
	float EnemyY;
	int Wait;
	int HP;
};
EnemyPattern enemy[MAX_ENEMY];
int times;
int EnemyTimes;

void Enemy_Initialize()
{
	Enemy_Create();
	times = 0;
	EnemyTimes = 0;
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		enemy[k].Wait = rand() % 4;
	}
}

void Enemy_Update()
{
	for (int k = 0; k < MAX_ENEMY; k++)
	{
		if(enemy[k].HP > 0)
		{
			times++;
			if (times > WaitTime)
			{
				if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize;
				}
				times = 0;
			}
			DrawFormatString(400, 50 + (20 * k), 0xffffff, "%d", enemy[k].HP);
			DrawFormatString(420, 50 + (20 * k), 0xffffff, "%f", enemy[k].EnemyY);
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
		}
	}
}

void Enemy_Create()
{
	srand((unsigned)time(NULL));
	EnemyTimes = 5;
	int k;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		k = rand() % 7;
		enemy[i].EnemyX = 20 + (TroutSize * k);
		enemy[i].EnemyY = 20;
		enemy[i].HP = 1;
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