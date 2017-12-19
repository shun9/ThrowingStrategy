//************************************************/
//* @file  :UIManager.h
//* @brief :UIをまとめて管理するクラス
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include "UI.h"

class UIManager : public ShunLib::Singleton<UIManager>
{
	friend ShunLib::Singleton<UIManager>;

private:
	std::vector<UI*>m_uiList;

public:
	//更新　描画
	void Update();
	void Render();

	//UIを追加
	void AddUI(UI* ui) { m_uiList.push_back(ui); };

	//UIを削除
	void RemoveUI(UI* ui) {
		auto tmp = std::find(m_uiList.begin(), m_uiList.end(), ui);
		if (tmp != m_uiList.end()) {
			m_uiList.erase(tmp);
		}
	}

private:
	UIManager() {}
	~UIManager() {}
};
