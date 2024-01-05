#include "Skil.h"
#include "Field.h"
#include "time.h"
#include "DxLib.h"

int skil;
int gard;

void Skil_Initialize()
{
	skil = 0;
	gard = LoadGraph("image/gard.png");
}

void Skil_Update()
{
	if (skil != 0)
	{
		for (int i = 0; i < FieldWide; i++)
		{
			DrawGraph(0 + (TroutSize * i), 680, gard, TRUE);
		}
	}
}

void Skil_On()
{
	skil = 1;
	clock
	skil = 0;
}