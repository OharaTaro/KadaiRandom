#include "DxLib.h"

#include "game.h"
#include "CardDeck.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	///////////////////////////////////////////////////
	// 問題
	///////////////////////////////////////////////////

	// 通信を使った対戦を想定した実装を行う
	// プレイヤーの使うカードであるdeck0	と
	// 対戦相手の使うカードであるdeck1		がある

	// お互いのプレイヤーでカードを同じ順にしたい
	// そのためにプレイヤー側(deck0)で並び順を決定して
	// それを対戦相手(deck1)に渡して同じ並び順を生成する

	// 通信はエラーが発生したり時間がかかるため
	// できる限り渡すデータを小さくしたい
	// 渡すデータのサイズをできる限り小さくせよ
	
	// CardDeck::createDeck()内で渡すデータのサイズをprintfDxで表示しているのでそれを小さくする
	// (問題文の時点で416バイト)
	// 通信で他の機器にデータを渡す想定なのでメモリは共有していない想定で(ポインタで値を渡せない)

	CardDeck deck0{ 0 };
	CardDeck deck1{ 1 };

	// ランダムな並び順を生成
	deck0.createRandomDeck();
	// deck0からデータを受け取って同じ並び順を生成
	deck1.createDeck(deck0.getSendData());



	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		deck0.draw();
		deck1.draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}