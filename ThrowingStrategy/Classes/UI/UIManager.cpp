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
	//使用している状態ならば更新
	for (auto& v: m_uiList)
	{
		if (v->IsEnable()) {
			v->Update();
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void UIManager::Render()
{
	//使用している状態ならば描画
	for (auto& v : m_uiList){
		if (v->IsEnable()){
			v->Render();
		}
	}
}
