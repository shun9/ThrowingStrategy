//************************************************/
//* @file  :Collider.cpp
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

void ShunLib::SphereCollider::Update()
{
	if (m_parent != nullptr)
	{	
		CastShape()->CenterPoint(m_parent->Pos() + this->Offset());
	}
}

ShunLib::ICollider::ICollider() :
	m_parent(nullptr),
	m_shape(nullptr),
	m_callBack(NULL)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

ShunLib::ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

void ShunLib::ICollider::DebugRender()
{
}
