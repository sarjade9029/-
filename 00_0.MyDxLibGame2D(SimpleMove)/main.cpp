
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u����������
	if (DxLib_Init() == -1) return -1;

	// ��ʂ��E�C���h�E���[�h�ɂ���.
	ChangeWindowMode(TRUE);

	// x���W.
	int x = 0;

	while (true)
	{
		// ��ʂɊG��\��
		LoadGraphScreen(x, 0, "data/texture/player.png", FALSE);

		// �E�ɓ�����.
		x++;

		// �G�X�P�[�v�L�[���������甲����.
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	// �c�w���C�u�����g�p�̏I��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
