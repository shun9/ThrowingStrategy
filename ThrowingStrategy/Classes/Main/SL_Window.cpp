//************************************************/
//* @file  :SL_Window.cpp
//* @brief :ウィンドウクラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_Window.h"
#include "SL_Graphics.h"
#include <SL_KeyManager.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT ShunLib::Window::Create(HINSTANCE hInst)
{
	//ウィンドウ情報　0で初期化
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	//ウィンドウの情報を設定
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = m_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//ウィンドウの登録
	RegisterClassEx(&wc);

	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = static_cast<LONG>(m_width);
	rc.bottom = static_cast<LONG>(m_height);

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを作成
	m_hWnd = CreateWindow(m_name, m_name, WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0, 0, hInst, 0);

	//作成に失敗したらエラー
	if (!m_hWnd)return E_FAIL;

	//ウィンドウを画面に表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

/// <summary>
/// ウィンドウプロシージャ
/// ・OSからメッセージを受け取り処理をする
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	switch (iMag)
	{
	//キーが押された
	case WM_KEYDOWN:
		ShunLib::KeyManager::ProcessMessage(iMag, wParam, lParam);
		switch ((char)wParam)
		{
		//Escキーは終了
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	//キー情報を渡す
	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		ShunLib::KeyManager::ProcessMessage(iMag, wParam, lParam);
		break;

		//ウィンドウが消された
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	//不要なメッセージをOSに処理させる
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}
