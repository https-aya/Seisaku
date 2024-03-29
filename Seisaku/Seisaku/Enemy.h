﻿#pragma once

#define MAX_ENEMY (2)

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


void Enemy_Initialize();		//初期化処理
void Enemy_Update();			//更新処理
void Enemy_Draw();				//描画処理
void Enemy_Create(int i);			//生成処理
void Enemy_DecreaseHP(int n,int d);			//HP減少処理
int Enemy_GetHP(int n);			//㏋取得処理
float Enemy_GetX(int n);		//X座標取得処理
float Enemy_GetY(int n);		//Y座標取得処理
int GetEnemyattack_count();				//キルカウント取得処理
void CastleHit(int k);
void Enemy_Move(int k,int skil,int skilnum);