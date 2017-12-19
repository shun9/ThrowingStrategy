//************************************************/
//* @file  :UIManager.h
//* @brief :UI���܂Ƃ߂ĊǗ�����N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UIManager.h"

/// <summary>
/// �X�V
/// </summary>
void UIManager::Update()
{
	for (auto& v: m_uiList)
	{
		v->Update();
	}
}

/// <summary>
/// �`��
/// </summary>
void UIManager::Render()
{
	for (auto& v : m_uiList)
	{
		v->Render();
	}

}
