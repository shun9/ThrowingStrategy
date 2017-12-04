//************************************************/
//* @file  :Collider.cpp
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"
#include "../../Util/Debugger/DebugMacro.h"

using namespace ShunLib;

//基底コンストラクタ
//当たり判定を管理するクラスに登録
ICollider::ICollider() :
	m_parent(nullptr),
	m_shape(nullptr),
	m_callBack(NULL),
	m_isEntity(true),
	m_isDebugDraw(true)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

//基底コンストラクタ
//当たり判定を管理するクラスから削除
ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

//デバッグ用描画
void ICollider::DebugRender()
{
	if (m_isDebugDraw){
		m_shape->Render();
	}
}

void ShunLib::ICollider::Accept(ShunLib::Visitor * visitor)
{
	visitor->Visit(this);
	for (auto& v : m_hitList) {
		visitor->Visit(v);
	}
}

void ShunLib::ICollider::AddChildCollider(ICollider * child)
{
	m_childrenCollider.push_back(child);
	CollisionManager::GetInstance()->RemoveCollider(child);
}


//球状の当たり判定の更新
void SphereCollider::Update()
{
	if (m_parent != nullptr){
		Vec3 pos = m_parent->WorldPos();

		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
	}
}

//箱状の当たり判定の更新
void BoxCollider::Update()
{
	if (m_parent != nullptr)
	{
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
		Shape()->Size(m_parent->Scale());
	}
}
