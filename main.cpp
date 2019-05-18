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

	VECTOR playerPos;
	VECTOR playerDirection;
	float playerSpeed = 5.0f;
	int velocity;

	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	int /*playerPosX, playerPosY,*/ playerGraph;
	playerGraph = LoadGraph("data/texture/player.png");
	playerPos.x = 288; 
	playerPos.y = 400;

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
				playerDirection.y = -1.0f;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				playerDirection.y = 1.0f;
			}
			else
			{
				playerDirection.y = 0.0f;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				playerDirection.x = -1.0f;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				playerDirection.x = 1.0f;
			}
			else
			{
				playerDirection.x = 0.0f;
			}

			if (VSize(playerDirection) != 0)
			{
				playerDirection = VNorm(playerDirection);
			}

			VECTOR  verocity = VScale(playerDirection, playerSpeed);
			playerPos = VAdd(playerPos, verocity);

			// �v���C���[����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (playerPos.x < 0)
			{
				playerPos.x = 0;
			}
			if (playerPos.x > 640 - 64)
			{
				playerPos.x = 640 - 64;
			}
			if (playerPos.y < 0)
			{
				playerPos.y = 0;
			}
			if (playerPos.y > 480 - 64)
			{
				playerPos.y = 480 - 64;
			}

			// �v���C���[��`��
			DrawGraph(playerPos.x, playerPos.y, playerGraph, FALSE);
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