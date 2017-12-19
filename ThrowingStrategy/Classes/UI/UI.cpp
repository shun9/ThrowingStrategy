//************************************************/
//* @file  :UI.cpp
//* @brief :UI�̊��N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UI.h"
#include "UIManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UI::UI():
	m_pos(Vec3::Zero),
	m_rot(Vec3(90.0f,0.0f,0.0f)),
	m_scale(Vec3::One)
{
	//UI�̊Ǘ��ɒǉ�
	UIManager::GetInstance()->AddUI(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UI::~UI()
{
	//UI�̊Ǘ�����͂���
	UIManager::GetInstance()->RemoveUI(this);
}
