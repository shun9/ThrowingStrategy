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
	//�g�p���Ă����ԂȂ�΍X�V
	for (auto& v: m_uiList)
	{
		if (v->IsEnable()) {
			v->Update();
		}
	}
}

/// <summary>
/// �`��
/// </summary>
void UIManager::Render()
{
	//�g�p���Ă����ԂȂ�Ε`��
	for (auto& v : m_uiList){
		if (v->IsEnable()){
			v->Render();
		}
	}
}
