//-----------------------------------------------------------------------------
// @brief  ���C������.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);		// �𑜓x��640*480�Acolor��16bit�ɐݒ�.
	ChangeWindowMode(TRUE);			// �E�C���h�E���[�h��.

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	int playerX, playerY, playerGraph;
	playerGraph = LoadGraph("data/texture/player.png");
	playerX = 288; 
	playerY = 400;

	// �Q�[�����[�v.
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//------------------------------//
		// �v���C���[�̑��샋�[�`��
		//------------------------------//
		{
			// ���L�[�������Ă�����v���C���[���ړ�������
			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				playerY -= 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				playerY += 3;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				playerX -= 3;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				playerX += 3;
			}

			// �v���C���[����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (playerX < 0)
			{
				playerX = 0;
			}
			if (playerX > 640 - 64)
			{
				playerX = 640 - 64;
			}
			if (playerY < 0)
			{
				playerY = 0;
			}
			if (playerY > 480 - 64)
			{
				playerY = 480 - 64;
			}

			// �v���C���[��`��
			DrawGraph(playerX, playerY, playerGraph, FALSE);
		}

		//------------------------------//
		// �G�l�~�[�̈ړ����[�`��
		//------------------------------//
		{
		}

		// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0)
		{
			break;
		}
		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}