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

