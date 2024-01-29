#include "Skil.h"
#include "Field.h"
#include "InputControl.h"
#include "SceneManager.h"
#include "DxLib.h"

int skil;
int skilnum;
int gard;
int timeimage;
float timeangle;

void Skil_Initialize()
{
	skil = 0;
	gard = LoadGraph("image/gard.png");
	timeimage = LoadGraph("image/NewTime.png");
	timeangle = 0.0f;
}

void Skil_Update()
{
	if (skil != 0)
	{
		switch (skilnum)
		{
		case 0:
			for (int i = 0; i < FieldWide; i++)
			{
				DrawGraph(0 + (TroutSize * i), 680, gard, TRUE);
			}
			break;

		case 1:
			timeangle += DX_PI_F / 48.0f;
			DrawRotaGraph(550, 500, 1.0, timeangle, timeimage, TRUE);
			break;
		}
	}
}

void Skil_On()
{
	skil = 1;
}

void Skil_Off()
{
	skil = 0;
}

int GetSkil()
{
	return skil;
}

int GetSkilnum()
{
	return skilnum;
}

int Skil_ChangeInitialize()
{
	skilnum = 0;
	return 0;
}

void Skil_ChangeUpdate()
{
	InputControl::Update();
	if (InputControl::GetKeyDown(KEY_INPUT_J) == true)
	{
		Change_Scene(E_TITLE);
	}

	if (InputControl::GetKeyDown(KEY_INPUT_W) == true)
	{
		if (skilnum <= 0)
		{
			skilnum = 0;
		}
		else
		{
			skilnum--;
		}
	}

	if (InputControl::GetKeyDown(KEY_INPUT_S) == true)
	{
		if (skilnum >= 2)
		{
			skilnum = 2;
		}
		else
		{
			skilnum++;
		}
	}
}

void Skil_ChangeDraw()
{
	DrawFormatString(340, 340, 0xffffff, "WALL");
	DrawFormatString(340, 380, 0xffffff, "TIMESTOP");
	DrawFormatString(340, 420, 0xffffff, "TARGET");
	DrawCircle(320, 350 + (skilnum * 40), 10, GetColor(255, 0, 0));
}