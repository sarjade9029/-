//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(640, 480, 16);		// 解像度を640*480、colorを16bitに設定.
	ChangeWindowMode(TRUE);			// ウインドウモードに.

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	VECTOR playerPos;
	VECTOR playerDirection;
	float playerSpeed = 5.0f;
	int velocity;

	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	int /*playerPosX, playerPosY,*/ playerGraph;
	playerGraph = LoadGraph("data/texture/player.png");
	playerPos.x = 288; 
	playerPos.y = 400;

	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//------------------------------//
		// プレイヤーの操作ルーチン
		//------------------------------//
		{
			// 矢印キーを押していたらプレイヤーを移動させる
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

			// プレイヤーが画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
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

			// プレイヤーを描画
			DrawGraph(playerPos.x, playerPos.y, playerGraph, FALSE);
		}

		//------------------------------//
		// エネミーの移動ルーチン
		//------------------------------//
		{
		}

		// 裏画面の内容を表画面にコピーする（描画の確定）.
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}