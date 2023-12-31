#pragma once

#define MAX_ENEMY (10)

enum EnemyType
{
	E_NOMAL,
	E_CROSS,
	E_JCROSS,
	E_QUICK,
	E_BOME,
	E_STRAIGHT,
	E_GUARD,
	E_ZIGZAG
};

void Enemy_Initialize();
void Enemy_Update();
void Enemy_Draw();
void Enemy_Create();
void Enemy_HP(int n);
int Enemy_GetHP(int n);
float Enemy_GetX(int n);
float Enemy_GetY(int n);