//************************************************/
//* @file  :SL_Application.cpp
//* @brief :アプリケーションの基底クラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_Application.h"

#include <Windows.h>
#include "../Main/SL_Graphics.h"

/// <summary>
/// メインループ
/// </summary>
void ShunLib::Application::Run()
{
	auto graphics = ShunLib::Graphics::GetInstance();

	//メッセージ　0で初期化
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//初期化処理
	this->Initialize();

	//メッセージループ
	while (msg.message != WM_QUIT) {
		//OSからメッセージがあればプロシージャに渡す
		//OSからメッセージが無ければアプリケーションを更新する
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//仮想キーメッセージを文字メッセージへ変換
			TranslateMessage(&msg);

			//メッセージを送る
			DispatchMessage(&msg);
		}
		else {

			//更新処理
			this->Update();

			//描画処理
			graphics->Clear();
			this->Render();
			graphics->Present();
		}
	}

	//終了処理
	this->Finalize();
}
