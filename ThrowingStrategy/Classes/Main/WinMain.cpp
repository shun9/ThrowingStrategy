//************************************************/
//* @file  :WinMain.cpp
//* @brief :��������v���O�������n�܂�
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include <Windows.h>
#include "SL_Window.h"
#include "SL_Graphics.h"
#include "../Game/SL_MyGame.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT InitWindow(HINSTANCE hInst);
HRESULT InitGraphics();

/// <summary>
/// �G���g���[�|�C���g
/// �E��������v���O�������n�܂�
/// �E�E�B���h�E���쐬
/// �E���b�Z�[�W���[�v�̎���
/// </summary>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmpShow)
{
	auto window = ShunLib::Window::GetInstance();

	ShunLib::Application* game = new ShunLib::MyGame();

	//�E�B���h�E�쐬
	if (SUCCEEDED(InitWindow(hInst)))
	{
		//DirectX�֘A�̏�����
		if (SUCCEEDED(InitGraphics()))
		{
			game->Run();
		}
	}

	delete game;

	ShunLib::Graphics::Destroy();
	ShunLib::Window::Destroy();

	//�I��
	return 0;
}


/// <summary>
/// �E�B���h�E�v���V�[�W��
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();
	return window->MsgProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// �E�B���h�E������
/// </summary>
HRESULT InitWindow(HINSTANCE hInst)
{
	auto window = ShunLib::Window::GetInstance();
	auto graphic = ShunLib::Graphics::GetInstance();

	//�E�B���h�E���ݒ�
	window->Width(800.0f);
	window->Height(600.0f);
	window->Name(L"������");

	//�E�B���h�E�쐬
	if (SUCCEEDED(window->Create(hInst)))
	{
		return S_OK;
	}

	return E_FAIL;
}

/// <summary>
/// �`��֘A������
/// </summary>
HRESULT InitGraphics()
{
	auto graphics = ShunLib::Graphics::GetInstance();

	//�V�F�[�_�[�̓ǂݍ���
	if (SUCCEEDED(graphics->InitD3D()))
	{
		return S_OK;
	}

	return E_FAIL;
}
