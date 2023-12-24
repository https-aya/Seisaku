#pragma once


#define FieldWide	(12)
#define FieldHight	(18)
#define TroutSize	(720/FieldHight)

enum FieldState
{
	E_Player,
	E_Empty,
	E_Enemy,
	E_Wall,
	E_Attack
};

void Player_Initialize();			//初期化処理
void Player_Update();				//更新処理
void Player_Move();					//移動処理
void Player_Draw();					//描画処理
void Player_Attack();				//攻撃処理
void CheckDamage();
void Field_Draw();					//フィールド描画処理
void Field_Create();				//フィールド生成処理
void Enemy_MoveField();				//敵移動後フィールド処理
int check_overlap(int x, int y);	//壁判定処理

