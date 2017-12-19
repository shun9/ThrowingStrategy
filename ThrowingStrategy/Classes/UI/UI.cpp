//************************************************/
//* @file  :UI.cpp
//* @brief :UIの基底クラス
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UI.h"
#include "UIManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
UI::UI():
	m_pos(Vec3::Zero),
	m_rot(Vec3(90.0f,0.0f,0.0f)),
	m_scale(Vec3::One)
{
	//UIの管理に追加
	UIManager::GetInstance()->AddUI(this);
}

/// <summary>
/// デストラクタ
/// </summary>
UI::~UI()
{
	//UIの管理からはずす
	UIManager::GetInstance()->RemoveUI(this);
}
