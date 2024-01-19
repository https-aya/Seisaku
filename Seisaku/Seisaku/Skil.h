#pragma once

void Skil_Initialize();				//初期化処理
void Skil_Update();					//更新処理
void Skil_On();						//スキルオン
void Skil_Off();					//スキルオフ
int GetSkil();						//スキル発動取得処理
int GetSkilnum();					//スキル種類取得処理
int Skil_ChangeInitialize();		//スキル選択画面初期化処理
void Skil_ChangeUpdate();			//スキル選択画面更新処理
void Skil_ChangeDraw();				//スキル選択画面描画処理
