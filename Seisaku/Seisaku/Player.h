#pragma once


#define FieldWide	(12)
#define FieldHight	(18)
#define TroutSize	(720/FieldHight)

void Player_Initialize();			//初期化処理
void Player_Update();				//更新処理
void Player_Move();					//移動処理
void Player_Draw();					//描画処理
void Player_Attack();				//攻撃処理
float Player_GetX();				//X座標取得処理
float Player_GetY();				//Y座標取得処理

