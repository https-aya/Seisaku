#include "EndScene.h"
#include "DxLib.h"

int wait_count;

int EndScene_Initialize()
{
	wait_count = 0;
	return 0;
}

void EndScene_Update()
{
	wait_count++;
}

void EndScene_Draw()
{
	DrawFormatString(20, 20, 0xffffff, "END");
}

int Get_EndTime()
{
	if (wait_count > 300)
	{
		return true;
	}
	return false;
}
