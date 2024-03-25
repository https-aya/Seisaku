#include "Enemy.h"
#include "Player.h"
#include "Field.h"
#include "Castle.h"
#include "Skil.h"
#include "DxLib.h"


#define WaitTime  (200)

struct EnemyPattern
{
	char type;
	float EnemyX;
	float EnemyY;
	int Wait;
	int waitcount;
	int random;
	int HP;
	float enemy_vector_X;
	float enemy_vector_Y;
};
EnemyPattern enemy[50];
int enemyattack_count;
int enemycriatecount;
int criatedelay;

void Enemy_Initialize()
{
	enemyattack_count = 0;
	enemycriatecount = 0;
	criatedelay = 0;
	enemykill_clear();
}

void Enemy_Update()
{
	if (Get_play() == 1)
	{
		if (enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay == 0)
		{
			int k;
			k = GetRand(10);
			enemy[enemycriatecount].EnemyX = 20 + (TroutSize * k);
			enemy[enemycriatecount].EnemyY = 20;
			if (Check_Enemy(enemy[enemycriatecount].EnemyY / TroutSize,
				enemy[enemycriatecount].EnemyX / TroutSize) == FALSE)
			{
				Enemy_Create(enemycriatecount);
				enemycriatecount++;
				k = GetRand(5) + 1;
				criatedelay = k * 60 - (2 * Get_Wave());
			}
		}
		else if (enemycriatecount < MAX_ENEMY * Get_Wave() && criatedelay > 0)
		{
			criatedelay--;
		}
		if (GetSkilnum() == 1 && GetSkil() != 0)
		{
			for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
			{
				enemy[k].Wait = 0;
			}
		}
		else
		{
			for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
			{
				if (GetSkilnum() == 2 && GetSkil() != 0)
				{
					if (Player_GetX() / TroutSize != enemy[k].EnemyX / TroutSize || Player_GetY() / TroutSize != enemy[k].EnemyY / TroutSize)
					{
						if (enemy[k].HP > 0)
						{
							enemy[k].Wait++;
							switch (enemy[k].type)
							{
							case E_QUICK:
								if (enemy[k].Wait > (WaitTime / 1.6) - (2 * Get_Wave()))
								{
									CastleHit(k);
									enemy[k].Wait = 0;
									break;
								}

							default:
								if (enemy[k].Wait > WaitTime - (2 * Get_Wave()))
								{
									CastleHit(k);
									enemy[k].Wait = 0;
									break;
								}
							}
						}
					}
				}
				else
				{
					if (enemy[k].HP > 0)
					{
						enemy[k].Wait++;
						switch (enemy[k].type)
						{
						case E_QUICK:
							if (enemy[k].Wait > (WaitTime / 1.6) - (2 * Get_Wave()))
							{
								CastleHit(k);
								enemy[k].Wait = 0;
							}
							break;
						case E_STRAIGHT:
							if (enemy[k].waitcount <= 0)
							{
								if (enemy[k].Wait > (WaitTime / 2.5) - (2 * Get_Wave()))
								{
									CastleHit(k);
									enemy[k].Wait = 0;
								}
							}
							else if (enemy[k].Wait > WaitTime - (2 * Get_Wave()))
							{
								enemy[k].waitcount--;
								enemy[k].Wait = 0;
							}
							break;
						default:
							if (enemy[k].Wait > WaitTime - (2 * Get_Wave()))
							{
								CastleHit(k);
								enemy[k].Wait = 0;
							}
							break;
						}
					}
					else if (enemy[k].type == E_BOME)
					{
						if (Check_Castile(enemy[k].EnemyX / TroutSize, (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
						{
							Castle_Damage();
						}
					}
				}
			}
			Enemy_Draw();
		}
	}
}

void Enemy_Draw()
{
	for (int k = 0; k < MAX_ENEMY * Get_Wave(); k++)
	{
		if (enemy[k].HP > 0)
		{
			switch (enemy[k].type)
			{
			case E_NOMAL:
				DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff0000, TRUE);
				break;

			case E_CROSS:
				switch (enemy[k].HP)
				{
				case 4:
				case 2:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x00ff00, TRUE);
					break;
				case 3:
				case 1:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x0000ff, TRUE);
					break;
				}
				break;
			case E_QUICK:
				switch (enemy[k].HP)
				{
				case 4:
				case 2:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xfedcba, TRUE);
					break;

				case 3:
				case 1:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xffacdb, TRUE);
					break;
				}
				break;

			case E_JCROSS:
				switch (enemy[k].HP)
				{
				case 3:
				case 6:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x123456, TRUE);
					break;
				case 2:
				case 5:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x654321, TRUE);
					break;
				case 1:
				case 4:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xabcdef, TRUE);
					break;
				}
				break;
			case E_STRAIGHT:
				switch (enemy[k].HP)
				{
				case 3:
				case 6:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x558386, TRUE);
					break;
				case 2:
				case 5:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xad5c7e6, TRUE);
					break;
				case 1:
				case 4:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x88aee5d, TRUE);
					break;
				}
				break;
			case E_BOME:
				switch (enemy[k].HP)
				{
				case 3:
				case 6:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x45dfa4e, TRUE);
					break;
				case 2:
				case 5:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xff7a7fe, TRUE);
					break;
				case 1:
				case 4:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xafeecfa4, TRUE);
					break;
				}
				break;
			case E_GUARD:
				switch (enemy[k].HP)
				{
				case 6:
				case 12:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x4ad3e7b, TRUE);
					break;
				case 5:
				case 11:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x8cbdaef, TRUE);
					break;
				case 4:
				case 10:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0xa3f1768c, TRUE);
					break;
				case 3:
				case 9:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x8a7c59df, TRUE);
					break;
				case 2:
				case 8:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x00a8e44d, TRUE);
					break;
				case 1:
				case 7:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x7c5a4d44, TRUE);
					break;
				}
				break;
			case E_ZIGZAG:
				switch (enemy[k].HP)
				{
				case 6:
				case 3:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x88ddea44, TRUE);
					break;
				case 5:
				case 2:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x98fa7a0a, TRUE);
					break;
				case 4:
				case 1:
					DrawCircleAA(enemy[k].EnemyX, enemy[k].EnemyY, TroutSize / 2, 100, 0x98cda7f4, TRUE);
					break;
				}
				break;
			}
		}
		Enemy_Field(k);
	}
}

void Enemy_Create(int i)
{
	enemy[i].Wait = 0;
	int j = 0;
	if (Get_Wave() <= 3 || Get_Wave() >= 30 && Get_Wave() <= 33)
	{
		j = 0;
	}
	else if (Get_Wave() <= 6 || Get_Wave() >= 34 && Get_Wave() <= 36)
	{
		j = GetRand(5);
	}
	else if (Get_Wave() <= 9 || Get_Wave() >= 37 && Get_Wave() <= 39)
	{
		j = GetRand(8);
	}
	else if (Get_Wave() <= 12 || Get_Wave() >= 40 && Get_Wave() <= 42)
	{
		j = GetRand(11);
	}
	else if (Get_Wave() <= 15 || Get_Wave() >= 43 && Get_Wave() <= 45)
	{
		j = GetRand(14);
	}
	else if (Get_Wave() <= 18 || Get_Wave() >= 46 && Get_Wave() <= 48)
	{
		j = GetRand(17);
	}
	else if (Get_Wave() <= 21 || Get_Wave() >= 49 && Get_Wave() <= 51)
	{
		j = GetRand(20);
	}
	else if (Get_Wave() <= 24 || Get_Wave() >= 52)
	{
		j = GetRand(23);
	}
			


	switch (j)
	{
	case 3:
	case 4:
	case 5:
		enemy[i].type = E_CROSS;
		enemy[i].enemy_vector_X = TroutSize;
		enemy[i].enemy_vector_Y = TroutSize;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 4;
		}
		else
		{
			enemy[i].HP = 2;
		}
		break;

	case 6:
	case 7:
	case 8:
		enemy[i].type = E_BOME;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 6;
		}
		else
		{
			enemy[i].HP = 3;
		}
		break;

	case 9:
	case 10:
	case 11:
		enemy[i].type = E_JCROSS;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 6;
		}
		else
		{
			enemy[i].HP = 3;
		}
		break;

	case 12:
	case 13:
	case 14:
		enemy[i].type = E_QUICK;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 4;
		}
		else
		{
			enemy[i].HP = 2;
		}
		break;

	case 15:
	case 16:
	case 17:
		enemy[i].type = E_STRAIGHT;
		if (Get_Wave() >= 30)
		{
			enemy[i].waitcount = 2;
			enemy[i].HP = 6;
		}
		else
		{
			enemy[i].waitcount = 4;
			enemy[i].HP = 3;
		}
		break;

	case 18:
	case 19:
	case 20:
		enemy[i].type = E_GUARD;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 12;
		}
		else
		{
			enemy[i].HP = 6;
		}
		break;

	case 21:
	case 22:
	case 23:
		enemy[i].type = E_ZIGZAG;
		enemy[i].random = 0;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 6;
		}
		else
		{
			enemy[i].HP = 3;
		}
		break;

	default:
		enemy[i].type = E_NOMAL;
		if (Get_Wave() >= 30)
		{
			enemy[i].HP = 2;
		}
		else
		{
			enemy[i].HP = 1;
		}
		break;
	}
	Enemy_Field(i);
	Enemy_Draw();
}


void Enemy_DecreaseHP(int n,int d)
{
	enemy[n].HP -= d;
}

int Enemy_GetHP(int n)
{
	return enemy[n].HP;
}

float Enemy_GetX(int n)
{
	return enemy[n].EnemyX;
}

float Enemy_GetY(int n)
{
	return enemy[n].EnemyY;
}

int GetEnemyattack_count()
{
	return enemyattack_count;
}

void CastleHit(int k)
{
	if (Check_Castile((enemy[k].EnemyY / TroutSize + 1), (enemy[k].EnemyX / TroutSize)) == TRUE)
	{
		if (GetSkil() != 0 && GetSkilnum() == 0)
		{
			enemy[k].HP = 0;
			enemyattack_count++;
			Skil_Off();
		}
		else
		{
			enemy[k].HP = 0;
			enemyattack_count++;
			Castle_Damage();
		}
	}
	else
	{
		Enemy_Move(k,GetSkil(),GetSkilnum());
	}
}

void Enemy_Move(int k,int skil,int skilnum)
{
	if (skilnum==2 && skil != 0)
	{
		if (check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize)) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE &&
			check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize)) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize), (enemy[k].EnemyX / TroutSize) + 1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize)+1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize)) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) + 1, (enemy[k].EnemyX / TroutSize) - 1) == FALSE &&
			Check_Enemy((enemy[k].EnemyY / TroutSize) , (enemy[k].EnemyX / TroutSize) - 1) == FALSE)
		{
			Enemy_MoveField();
			if (Player_GetX() > enemy[k].EnemyX)
			{
				enemy[k].EnemyX += TroutSize;
			}
			else if (Player_GetX() < enemy[k].EnemyX)
			{
				enemy[k].EnemyX -= TroutSize;
			}
			if (Player_GetY() > enemy[k].EnemyY)
			{
				enemy[k].EnemyY += TroutSize;
			}
		}
	}
	else
	{
		switch (enemy[k].type)
		{
		case E_CROSS:
			if (enemy[k].enemy_vector_X == TroutSize && check_overlap((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == TRUE || enemy[k].enemy_vector_X == -TroutSize && check_overlap((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
			{
				Enemy_MoveField();
				enemy[k].EnemyX += enemy[k].enemy_vector_X;
				enemy[k].EnemyY += enemy[k].enemy_vector_Y;
			}
			if (check_overlap((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE && check_player((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE)
			{
				enemy[k].enemy_vector_X = -TroutSize;
			}
			if (check_overlap((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE && check_player((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 1) == FALSE || enemy[k].EnemyX - TroutSize <= 0)
			{
				enemy[k].enemy_vector_X = TroutSize;
			}
			break;

		case E_JCROSS:
			enemy[k].random = GetRand(1);
			if (enemy[k].random == 0)
			{
				if (check_overlap((enemy[k].EnemyX / TroutSize) + 1, (enemy[k].EnemyY / TroutSize) + 2) == TRUE)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize * 2;
					enemy[k].EnemyX += TroutSize;
					break;
				}
			}
			if (enemy[k].random == 1)
			{
				if (check_overlap((enemy[k].EnemyX / TroutSize) - 1, (enemy[k].EnemyY / TroutSize) + 2) == TRUE && enemy[k].EnemyX - TroutSize >= 0)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize * 2;
					enemy[k].EnemyX -= TroutSize;
					break;
				}
			}

		case E_STRAIGHT:
			if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
			{
				Enemy_MoveField();
				enemy[k].EnemyY += TroutSize;
			}
			else
			{
				if (Get_Wave() >= 30)
				{
					enemy[k].waitcount = 2;
				}
				else
				{
					enemy[k].waitcount = 4;
				}
			}
			break;

		case E_ZIGZAG:
			if (enemy[k].random == 0)
			{
				if (check_overlap((enemy[k].EnemyX / TroutSize + 1), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize;
					enemy[k].EnemyX += TroutSize;
				}
				enemy[k].random = 1;
			}
			else
			{
				if (check_overlap((enemy[k].EnemyX / TroutSize - 1), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
				{
					Enemy_MoveField();
					enemy[k].EnemyY += TroutSize;
					enemy[k].EnemyX -= TroutSize;
				}
				enemy[k].random = 0;
			}
			break;
		default:
			if (check_overlap((enemy[k].EnemyX / TroutSize), (enemy[k].EnemyY / TroutSize) + 1) == TRUE)
			{
				Enemy_MoveField();
				enemy[k].EnemyY += TroutSize;
			}
			break;
		}
	}
}