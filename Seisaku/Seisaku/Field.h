#pragma once

#define FieldWide	(12)
#define FieldHight	(18)
#define TroutSize	(720/FieldHight)

enum FieldState
{
	E_Player,
	E_Empty,
	E_Enemy,
	E_Wall,
	E_Castle
};

void CheckDamage();					//�_���[�W���菈��
void Field_Draw();					//�t�B�[���h�`�揈��
void Field_Create();				//�t�B�[���h��������
int check_overlap(int x, int y);	//�ǔ��菈��
int Check_Castile(int h, int w);	//�锻��
void Enemy_MoveField();				//�G�ړ���t�B�[���h����
void Enemy_Field(int n);			//�G�t�B�[���h���萶��
int Check_Enemy(int h, int w);		//�G�������d�Ȃ蔻��
void Player_MoveField();			//�G�ړ���t�B�[���h����
void Player_Field();				//�v���C���[�t�B�[���h���萶��

