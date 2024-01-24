#include "RankingScene.h"
#include "DxLib.h"
#include "InputControl.h"
#include "SceneManager.h"

/**********************************
*�}�N����`
**********************************/
#define RANKING_FILE		("dat/rankingdata.csv")
#define RANKING_MAX				(10)
#define RANKING_NAME_LEN	(11)

/**********************************
*�^��`
**********************************/
typedef struct
{
	int rank;						//�����N
	char name[RANKING_NAME_LEN];	//���O
	int score;						//�X�R�A
}T_RANKING;

typedef struct
{
	int x;
	int y;
}T_CURSOR;

/**********************************
*�O���[�o���ϐ��錾
**********************************/
T_RANKING Ranking_Data[RANKING_MAX];		//�����L���O�f�[�^
T_RANKING New_Score;						//�V�����X�R�A�f�[�^
int DispMode;								//�\�����[�h

InputControl input;

T_CURSOR Cursor;							//�J�[�\���p�ϐ�
int name_num;

/**********************************
*�v���g�^�C�v�錾
**********************************/
void file_read(void);				//�t�@�C���ǂݍ���
void file_write(void);				//�t�@�C����������
void ranking_sort(void);			//�����L���O�\�[�g����
void ranking_input_name(void);		//���O���͏���
void ranking_input_name_draw(void);	//���O���͕`�揈��

/**********************************
*�����L���O���:����������
* ���@��:�Ȃ�
* �߂�l:�G���[���(-1:�ُ�L,-1�ȊO:����I��
**********************************/
int RankingScene_Initialize(void)
{
	int ret = 0;
	file_read();
	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		Cursor.x = 0;
		Cursor.y = 0;
		name_num = 0;
		break;
	case RANKING_DISP_MODE:
	default:
		break;

	}
	return ret;
}

/**********************************
*�����L���O���:�X�V����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void RankingScene_Update(void)
{
	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_input_name();
		break;
	case RANKING_DISP_MODE:
	default:
		if (input.GetKeyDown(KEY_INPUT_K) == true)
		{
			Change_Scene(E_TITLE);
		}
		break;
	}
}

/**********************************
*�����L���O���:�`�揈��
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void RankingScene_Draw(void)
{
	int i;

	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_input_name_draw();
		break;
	case RANKING_DISP_MODE:
	default:
		for (i = 0; i < RANKING_MAX; i++)
		{
			DrawFormatString(20, 10 + (i * 25), GetColor(255, 255, 255), "%2d,%10s,%10d"
				, Ranking_Data[i].rank, Ranking_Data[i].name, Ranking_Data[i].score);
		}
		break;
	}
}

/**********************************
*�����L���O���:��ʕύX����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void Set_RankingMode(int mode)
{
	DispMode = mode;
}

/**********************************
*�����L���O���:�X�R�A�擾����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void Set_RankingScore(int score)
{
	New_Score.score = score;
}

/**********************************
*�����L���O���:�t�@�C���ǂݍ��ݏ���
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void file_read(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("�t�@�C����ǂݍ��݂܂�");
	fopen_s(&fp, RANKING_FILE, "r");

	if (fp == NULL)
	{
		OutputDebugString("�t�@�C�����ǂݍ��߂܂���");
		OutputDebugString("�t�@�C���𐶐����܂�");
		file_write();
	}
	else
	{
		for (i = 0; i < RANKING_MAX; i++)
		{
			fscanf_s(fp, "%2d, %[^,], %10d\n", &Ranking_Data[i].rank,
				Ranking_Data[i].name, RANKING_NAME_LEN, &Ranking_Data[i].score);
		}

		fclose(fp);
	}
}

/**********************************
*�����L���O���:�t�@�C���������ݏ���
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void file_write(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("�t�@�C�����������݂܂�");
	fopen_s(&fp, RANKING_FILE, "w");

	if (fp == NULL)
	{
		OutputDebugString("�t�@�C�����������߂܂���");
	}
	else
	{
		for (i = 0; i < RANKING_MAX; i++)
		{
			//%[^ ]��%s�ɋA��
			fprintf(fp, "%2d,%s,%10d\n", Ranking_Data[i].rank,
				Ranking_Data[i].name, Ranking_Data[i].score);
		}

		fclose(fp);
		for (int i = 0; New_Score.name[i] == '\0'; i++)
		{
			New_Score.name[i] = 0;
		}
	}
}

/**********************************
*�����L���O���:�����L���O�\�[�g����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void ranking_sort(void)
{
	int i, j;			//���[�v�J�E���^
	T_RANKING tmp;		//�ޔ�̈�

	//��ԉ��̃X�R�A���X�V����
	Ranking_Data[RANKING_MAX - 1] = New_Score;

	//�f�[�^�̃\�[�g���s��
	for (i = 0; i < RANKING_MAX; i++)
	{
		for (j = i + 1; j < RANKING_MAX; j++)
		{
			if (Ranking_Data[i].score < Ranking_Data[j].score)
			{
				tmp = Ranking_Data[i];
				Ranking_Data[i] = Ranking_Data[j];
				Ranking_Data[j] = tmp;
			}
		}
	}

	//���ʂ��ォ��ӂ��Ă���
	for (i = 0; i < RANKING_MAX; i++)
	{
		Ranking_Data[i].rank = i + 1;
	}

	//�t�@�C���ɏ������݂��s��
	file_write();
}

/**********************************
*�����L���O���:���O���͏���
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void ranking_input_name(void)
{
	int c;

	//�J�[�\�����쏈��
	if (input.GetKeyDown(KEY_INPUT_A) == true)
	{
		if (Cursor.x > 0)
		{
			Cursor.x--;
		}
	}
	if (input.GetKeyDown(KEY_INPUT_D) == true)
	{
		if (Cursor.x < 12)
		{
			Cursor.x++;
		}
	}
	if (input.GetKeyDown(KEY_INPUT_W) == true)
	{
		if (Cursor.y > 0)
		{
			Cursor.y--;
		}
	}
	if (input.GetKeyDown(KEY_INPUT_S) == true)
	{
		if (Cursor.y < 4)
		{
			Cursor.y++;
		}
	}

	//������I������
	if (input.GetKeyDown(KEY_INPUT_J) == true)
	{
		if (Cursor.y < 2)
		{
			c = 'a' + Cursor.x + (Cursor.y * 13);
			New_Score.name[name_num++] = c;
		}
		else if (Cursor.y < 4)
		{
			c = 'A' + Cursor.x + ((Cursor.y - 2) * 13);
			New_Score.name[name_num++] = c;
		}
		else
		{
			if (Cursor.x < 10)
			{
				c = '0' + Cursor.x;
				New_Score.name[name_num++] = c;
			}
			else if (Cursor.x == 10)
			{
				name_num--;
				New_Score.name[name_num] = '\0';
			}
			else
			{
				DispMode = RANKING_DISP_MODE;
				ranking_sort();
			}
		}
	}
}

/**********************************
*�����L���O���:���O���͕`�揈��
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void ranking_input_name_draw(void)
{
	int i;

	SetFontSize(40);
	DrawFormatString(300, 150, GetColor(255, 255, 255), "���O����͂��Ă�������");

	//�I��p������`��
	for (i = 0; i < 26; i++)
	{
		DrawFormatString((i % 13 * 50) + 300, (i / 13 * 50) + 330, GetColor(255, 255,
			255), "%-3c", 'a' + i);
		DrawFormatString((i % 13 * 50) + 300, (i / 13 * 50) + 430, GetColor(255, 255,
			255), "%-3c", 'A' + i);
	}
	for (i = 0; i < 10; i++)
	{
		DrawFormatString((i % 13 * 50) + 300, 530, GetColor(255, 255, 255), "%-3c", '0' + i);
	}

	DrawFormatString(300, 220, GetColor(255, 255, 255), ">%s", New_Score.name);
	SetFontSize(35);
	DrawFormatString(790, 530, 0xffffff, "��");
	DrawFormatString(840, 530, 0xffffff, "��");
	DrawFormatString(890, 530, 0xffffff, "�I");
	SetFontSize(20);

	//�I�����Ă��镶�����t�H�[�J�X���Ă���
	DrawBox((Cursor.x * 50) + 290, (Cursor.y * 50) + 330,
		(Cursor.x * 50) + 330, (Cursor.y * 50) + 370,
		GetColor(255, 255, 255), FALSE);
}