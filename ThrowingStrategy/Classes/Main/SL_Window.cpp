//************************************************/
//* @file  :SL_Window.cpp
//* @brief :�E�B���h�E�N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_Window.h"
#include "SL_Graphics.h"
#include <SL_KeyManager.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT ShunLib::Window::Create(HINSTANCE hInst)
{
	//�E�B���h�E���@0�ŏ�����
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	//�E�B���h�E�̏���ݒ�
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = m_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//�E�B���h�E�̓o�^
	RegisterClassEx(&wc);

	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = static_cast<LONG>(m_width);
	rc.bottom = static_cast<LONG>(m_height);

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E���쐬
	m_hWnd = CreateWindow(m_name, m_name, WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0, 0, hInst, 0);

	//�쐬�Ɏ��s������G���[
	if (!m_hWnd)return E_FAIL;

	//�E�B���h�E����ʂɕ\��
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

/// <summary>
/// �E�B���h�E�v���V�[�W��
/// �EOS���烁�b�Z�[�W���󂯎�菈��������
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	switch (iMag)
	{
	//�L�[�������ꂽ
	case WM_KEYDOWN:
		ShunLib::KeyManager::ProcessMessage(iMag, wParam, lParam);
		switch ((char)wParam)
		{
		//Esc�L�[�͏I��
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	//�L�[����n��
	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		ShunLib::KeyManager::ProcessMessage(iMag, wParam, lParam);
		break;

		//�E�B���h�E�������ꂽ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	//�s�v�ȃ��b�Z�[�W��OS�ɏ���������
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}
