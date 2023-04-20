#include <DxLib.h>
#include "Game.h"

#if false
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Windowモード設定
	ChangeWindowMode(Game::window_mode);

	// Window名設定
	SetMainWindowText(Game::title_text);

	// 画面サイズの設定
	SetGraphMode(Game::screen_width, Game::screen_height, Game::color_depth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	XINPUT_STATE state = {};

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		GetJoypadXInputState(DX_INPUT_PAD1, &state);

		DrawFormatString(10, 10, 0xffffff, "LTrigger = %d\n", state.LeftTrigger);
		DrawFormatString(10, 30, 0xffffff, "RTrigger = %d\n", state.RightTrigger);
		DrawFormatString(10, 50, 0xffffff, "LLeverX = %d\n", state.ThumbLX);
		DrawFormatString(10, 70, 0xffffff, "LLeverY = %d\n", state.ThumbLY);

		if (state.RightTrigger > 128)
		{
			// Padを揺らす
			StartJoypadVibration(DX_INPUT_PAD1, 1000, 2000, -1);
		}

		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// Escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
#else

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Windowモード設定
	ChangeWindowMode(Game::window_mode);

	// Window名設定
	SetMainWindowText(Game::title_text);

	// 画面サイズの設定
	SetGraphMode(Game::screen_width, Game::screen_height, Game::color_depth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	DINPUT_JOYSTATE input;

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

		DrawFormatString(0, 0, GetColor(255, 255, 255), "X:%d Y:%d Z:%d", input.X, input.Y, input.Z);
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Rx:%d Ry:%d Rz:%d", input.Rx, input.Ry, input.Rz);
		DrawFormatString(0, 32, GetColor(255, 255, 255), "Slider 0:%d 1:%d", input.Slider[0], input.Slider[1]);
		DrawFormatString(0, 48, GetColor(255, 255, 255), "POV 0:%d 1:%d 2:%d 3:%d", input.POV[0], input.POV[1], input.POV[2], input.POV[3]);
		DrawString(0, 64, "Button", GetColor(255, 255, 255));

		for (int i = 0; i < 32; i++)
		{
			DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, GetColor(255, 255, 255), "%2d:%d", i, input.Buttons[i]);
		}

		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// Escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
#endif