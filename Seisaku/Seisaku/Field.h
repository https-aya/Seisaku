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
	E_Castle
};

void CheckDamage();					//ダメージ判定処理
void Field_Draw();					//フィールド描画処理
void Field_Create();				//フィールド生成処理
int check_overlap(int x, int y);	//壁判定処理
int Check_Castile(int h, int w);	//城判定
void Enemy_MoveField();				//敵移動後フィールド処理
void Enemy_Field(int n);			//敵フィールド判定生成
int Check_Enemy(int h, int w);		//敵生成時重なり判定
void Player_MoveField();			//敵移動後フィールド処理
void Player_Field();				//プレイヤーフィールド判定生成

