//************************************************/
//* @file  :Collider.cpp
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

//球状の当たり判定の更新
void ShunLib::ICollider::Update()
{
	if (m_parent != nullptr)
	{	
		Shape()->CenterPoint(m_parent->Pos() + this->Offset());
	}
}

//基底コンストラクタ
//当たり判定を管理するクラスに登録
ShunLib::ICollider::ICollider() :
	m_parent(nullptr),
	m_shape(nullptr),
	m_callBack(NULL)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

//基底コンストラクタ
//当たり判定を管理するクラスから削除
ShunLib::ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

//デバッグ用描画
void ShunLib::ICollider::DebugRender()
{
	m_shape->Render();
}
