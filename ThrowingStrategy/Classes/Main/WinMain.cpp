//************************************************/
//* @file  :WinMain.cpp
//* @brief :ここからプログラムが始まる
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include <Windows.h>
#include <memory>
#include <crtdbg.h>
#include <Keyboard.h>
#include "SL_Window.h"
#include "SL_Graphics.h"
#include "../Game/MyGame.h"
#include "../Util/DestroySingleton.h"
#include <SL_SingletonDestroyer.h>

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT InitWindow(HINSTANCE hInst);
HRESULT InitGraphics();

/// <summary>
/// エントリーポイント
/// ・ここからプログラムが始まる
/// ・ウィンドウを作成
/// ・メッセージループの実装
/// </summary>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmpShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto window = ShunLib::Window::GetInstance();

	ShunLib::Application* game = new MyGame();

	//ウィンドウ作成
	if (SUCCEEDED(InitWindow(hInst)))
	{
		//DirectX関連の初期化
		if (SUCCEEDED(InitGraphics()))
		{
			game->Run();
		}
	}

	delete game;

	//シングルトンの削除
	ShunLib::SingletonDestroyer::DestoroySingleton();

	//終了
	return 0;
}


/// <summary>
/// ウィンドウプロシージャ
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();
	return window->MsgProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// ウィンドウ初期化
/// </summary>
HRESULT InitWindow(HINSTANCE hInst)
{
	auto window = ShunLib::Window::GetInstance();
	auto graphic = ShunLib::Graphics::GetInstance();

	//ウィンドウ情報設定
	window->Width(800.0f);
	window->Height(600.0f);
	window->Name(L"投げる");

	//ウィンドウ作成
	if (SUCCEEDED(window->Create(hInst)))
	{
		return S_OK;
	}

	return E_FAIL;
}

/// <summary>
/// 描画関連初期化
/// </summary>
HRESULT InitGraphics()
{
	auto graphics = ShunLib::Graphics::GetInstance();

	//シェーダーの読み込み
	if (SUCCEEDED(graphics->InitD3D()))
	{
		return S_OK;
	}

	return E_FAIL;
}
