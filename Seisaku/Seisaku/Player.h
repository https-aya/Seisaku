#pragma once


#define FieldWide	(8)
#define FieldHight	(12)
#define TroutSize	(480/FieldHight)

enum FieldState
{
	E_Player,
	E_Empty,
	E_Enemy,
	E_Wall,
	E_Attack
};

void Player_Initialize();			//����������
void Player_Update();				//�X�V����
void Player_Move();					//�ړ�����
void Player_Draw();					//�`�揈��
void Player_Attack();				//�U������
void CheckDamage();
void Field_Draw();					//�t�B�[���h�`�揈��
void Field_Create();				//�t�B�[���h��������
void Enemy_MoveField();				//�G�ړ���t�B�[���h����
int check_overlap(int x, int y);	//�ǔ��菈��

