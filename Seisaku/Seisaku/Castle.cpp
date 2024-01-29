#include "Castle.h"
#include "Field.h"
#include "DxLib.h"

int CastleHP;
float CastleX;
float CastleY;
int Castle;
int HP_G;
int HP_Y;
int HP_R;
int wave;


void Castle_Initialize()
{
	CastleX = 0;
	CastleY = 680;
	CastleHP = 10;
	wave = 1;
	Castle = LoadGraph("image/jouheki.png");
	HP_G = LoadGraph("image/hp_g.png");
	HP_Y = LoadGraph("image/hp_y.png");
	HP_R = LoadGraph("image/hp_r.png");
}

void Castle_Update()
{
	Castle_Draw();
	Castle_HpDraw();
}

void Castle_Draw()
{
	int i;
	for (i = 0; i < FieldWide; i++)
	{
		DrawGraph(CastleX + (TroutSize * i), CastleY, Castle, TRUE);
	}
}

void Castle_HpDraw()
{
	int i;
	for (i = 0; i < CastleHP; i++)
	{
		switch (CastleHP)
		{
		case 1:
		case 2:
			DrawGraph(CastleX + (TroutSize * i), 710, HP_R, TRUE);
			break;

		case 3:
		case 4:
		case 5:
			DrawGraph(CastleX + (TroutSize * i), 710, HP_Y, TRUE);
			break;

		default:
			DrawGraph(CastleX + (TroutSize * i), 710, HP_G, TRUE);
			break;
		
		}
	}
}

void Castle_Damage()
{
	CastleHP--;
}

int Castle_GetHp()
{
	return CastleHP;
}

void WaveUp()
{
	if (wave < 5)
	{
		wave++;
	}
}

int Get_Wave()
{
	return wave;
}