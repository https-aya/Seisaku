#include "Player.h"
#include "DxLib.h"

#define FieldLineWide	(7)
#define FieldLineHight	(10)

void Player_Initialize()	//‰Šú‰»ˆ—
{

}
void Player_Update()		//XVˆ—
{
	Field_Draw();
}
void Player_Move()			//ˆÚ“®ˆ—
{

}

void Field_Draw()
{
	int i;
	DrawBoxAA(0, 0, 336, 480, 0xffffff, FALSE, 0.5f);
	for (i = 1; i < FieldLineWide; i++)
	{
		DrawLineAA((i * 48), 0, (i * 48), 600, 0xffffff, 1.0f);
	}
	for (i = 1; i < FieldLineHight; i++)
	{
		DrawLineAA(0, (i * 48), 336, (i * 48), 0xffffff, 1.0f);
	}

}