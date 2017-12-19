//************************************************/
//* @file  :SL_Application.cpp
//* @brief :�A�v���P�[�V�����̊��N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_Application.h"

#include <Windows.h>
#include "../Main/SL_Graphics.h"

/// <summary>
/// ���C�����[�v
/// </summary>
void ShunLib::Application::Run()
{
	auto graphics = ShunLib::Graphics::GetInstance();

	//���b�Z�[�W�@0�ŏ�����
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//����������
	this->Initialize();

	//���b�Z�[�W���[�v
	while (msg.message != WM_QUIT) {
		//OS���烁�b�Z�[�W������΃v���V�[�W���ɓn��
		//OS���烁�b�Z�[�W��������΃A�v���P�[�V�������X�V����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			TranslateMessage(&msg);

			//���b�Z�[�W�𑗂�
			DispatchMessage(&msg);
		}
		else {

			//�X�V����
			this->Update();

			//�`�揈��
			graphics->Clear();
			this->Render();
			graphics->Present();
		}
	}

	//�I������
	this->Finalize();
}
