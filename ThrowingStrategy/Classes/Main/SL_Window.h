#pragma once
#include <Windows.h>

#include <SL_Singleton.h>

namespace ShunLib
{
	class Window :public Singleton<Window>
	{
		friend Singleton<Window>;

	private:
		//�E�B���h�E�T�C�Y
		float m_width;  //��
		float m_height; //�c

		WCHAR* m_name;//�E�B���h�E��
		HWND m_hWnd;  //�E�B���h�E�n���h��

	public:
		//�E�B���h�E�쐬
		HRESULT Create(HINSTANCE);

		//�v���V�[�W��
		LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//���b�Z�[�W���[�v
		void Run();

		//Setter
		void Width(float width) { m_width = width; }
		void Height(float height) { m_height = height; }
		void Name(WCHAR* name) { m_name = name; }

		//Getter
		float Width() { return m_width; }
		float Height() { return m_height; }
		WCHAR* Name() { return m_name; }
		HWND Handle() { return m_hWnd; };

	private:
		//�R���X�g���N�^���f�X�g���N�^
		//�V���O���g���̂��߉B��
		Window() :
			m_width(640.0f),
			m_height(480.0f),
			m_name(L"�^�C�g��") {}

		~Window() {	}


	};
}