#pragma once

#define FieldWide	(12)
#define FieldHight	(18)
#define TroutSize	(720/FieldHight)

void Player_Initialize();			//����������
void Player_Update();				//�X�V����
void Player_Move();					//�ړ�����
void Player_Draw();					//�`�揈��
void Player_Attack();				//�U������
float Player_GetX();				//X���W�擾����
float Player_GetY();				//Y���W�擾����
void ScoreUP();						//�X�R�A�A�b�v����
int Get_Score();					//�X�R�A�擾����
void Draw_LvUp();
void LvUp_Move();
int Get_ARLv();
int Get_ASLv();
int Get_ADLv();
int Get_PLv();
void play_change(int n);
int Get_play();
int Get_SkilSpan();