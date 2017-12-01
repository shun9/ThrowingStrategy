//************************************************/
//* @file  :DebuggerUI.h
//* @brief :デバッグ用のUIを表示するクラス
//* @date  :2017/11/14
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <functional>
#include <SL_Singleton.h>
#include "DebugMacro.h"
#include "../../Main/SL_Window.h"
#include "../../Main/SL_Graphics.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"

class DebuggerUI : public ShunLib::Singleton<DebuggerUI>
{
	friend ShunLib::Singleton<DebuggerUI>;

private:
	std::vector<std::function<void(void)>>m_drawingStack;

public:
	//テキストの描画命令
	template<typename... NUMBER>
	void DrawDebugText(const char* fmt, NUMBER ...num) {
		Debug m_drawingStack.push_back([=]() {ImGui::Text(fmt, num...); });
	}

	//描画実行
	void Render() {
		Debug ImGui_ImplDX11_NewFrame();

		Debug ImGui::Begin("Debug");
		Debug ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
		Debug ImGui::SetWindowSize(ImVec2(400.0f, 600.0f));

		Debug RenderText();
		Debug ImGui::End();
		
		Debug ImGui::Render();

		Debug m_drawingStack.clear();
		Debug m_drawingStack.shrink_to_fit();
	}

private:
	DebuggerUI() {
		auto win = ShunLib::Window::GetInstance();
		auto gra = ShunLib::Graphics::GetInstance();
		ImGui_ImplDX11_Init(win->Handle(), gra->Device(), gra->DeviceContext());

	}

	~DebuggerUI() {
		ImGui_ImplDX11_Shutdown();
	}

	//描画命令実行
	void RenderText() {
		for (auto& v : m_drawingStack){
			v();
		}
	}
};