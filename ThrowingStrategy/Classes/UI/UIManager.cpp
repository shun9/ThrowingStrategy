//************************************************/
//* @file  :UIManager.h
//* @brief :UIをまとめて管理するクラス
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UIManager.h"

/// <summary>
/// 更新
/// </summary>
void UIManager::Update()
{
	for (auto& v: m_uiList)
	{
		v->Update();
	}
}

/// <summary>
/// 描画
/// </summary>
void UIManager::Render()
{
	for (auto& v : m_uiList)
	{
		v->Render();
	}

}
