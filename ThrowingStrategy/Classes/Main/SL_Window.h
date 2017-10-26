#pragma once
#include <Windows.h>

#include <SL_Singleton.h>

namespace ShunLib
{
	class Window :public Singleton<Window>
	{
		friend Singleton<Window>;

	private:
		//ウィンドウサイズ
		float m_width;  //横
		float m_height; //縦

		WCHAR* m_name;//ウィンドウ名
		HWND m_hWnd;  //ウィンドウハンドル

	public:
		//ウィンドウ作成
		HRESULT Create(HINSTANCE);

		//プロシージャ
		LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//メッセージループ
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
		//コンストラクタ＆デストラクタ
		//シングルトンのため隠蔽
		Window() :
			m_width(640.0f),
			m_height(480.0f),
			m_name(L"タイトル") {}

		~Window() {	}


	};
}