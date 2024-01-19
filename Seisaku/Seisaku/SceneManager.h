#pragma once

#define D_ERROR	(-1)
#define D_NORMALITY	(0)

enum GAME_MODE
{
	E_TITLE,
	E_GAMEMAIN,
	E_RANKING,
	E_SKIL,
	E_END,
	E_MODE_MAX
};

void SceneManager_Initialize(GAME_MODE mode);	//����������
void SceneManager_Update();						//�X�V����
void SceneManager_Draw();						//�`�揈��
void Change_Scene(GAME_MODE mode);				//�V�[���ύX����
int ErrorCheck();								//�G���[�`�F�b�N