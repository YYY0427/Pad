#include <DxLib.h>
#include "Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Window���[�h�ݒ�
	ChangeWindowMode(Game::window_mode);

	// Window���ݒ�
	SetMainWindowText(Game::title_text);

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::screen_width, Game::screen_height, Game::color_depth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	XINPUT_STATE state = {};

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʂ̃N���A
		ClearDrawScreen();

		GetJoypadXInputState(DX_INPUT_PAD1, &state);

		DrawFormatString(10, 10, 0xffffff, "LTrigger = %d\n", state.LeftTrigger);
		DrawFormatString(10, 30, 0xffffff, "RTrigger = %d\n", state.RightTrigger);
		DrawFormatString(10, 50, 0xffffff, "LLeverX = %d\n", state.ThumbLX);
		DrawFormatString(10, 70, 0xffffff, "LLeverY = %d\n", state.ThumbLY);

		if (state.RightTrigger > 128)
		{
			// Pad��h�炷
			StartJoypadVibration(DX_INPUT_PAD1, 1000, 2000, -1);
		}

		// ����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// Esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
