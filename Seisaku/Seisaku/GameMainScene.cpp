#include "GameMainScene.h"
#include "Player.h"
#include "Field.h"
#include "Castle.h"
#include "Enemy.h"
#include "Skil.h"
#include "DxLib.h"

int GameMainScene_Initialize()
{
	Castle_Initialize();
	Player_Initialize();
	Enemy_Initialize();
	Skil_Initialize();
	return 0;
}
void GameMainScene_Update()
{
	Player_Update();
	Enemy_Update();
	Castle_Update();
	Skil_Update();
}