//************************************************/
//* @file  :Collider.cpp
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"
#include "../../Util/Debugger/DebugMacro.h"

using namespace ShunLib;

//基底コンストラクタ
//当たり判定を管理するクラスに登録
ICollider::ICollider(int layer) :
	m_layer(layer),
	m_parent(nullptr),
	m_shape(nullptr),
	m_shouldPassParentInfo(true),
	m_isStatic(false),
	m_isEnable(true),
	m_shouldRejection(true),
	m_isDebugDraw(true)
{
	CollisionManager::GetInstance()->AddCollider(layer,this);
}

//基底コンストラクタ
//当たり判定を管理するクラスから削除
ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

/// <summary>
/// 基底の更新
/// </summary>
void ICollider::Update()
{

}

//デバッグ用描画
void ICollider::DebugRender()
{
	//使用しているなら描画
	if (IsEnable()){

		if (m_isDebugDraw) {
			m_shape->Render();
		}
	}
}

/// <summary>
/// ビジターを受け入れる
/// </summary>
void ICollider::Accept(Visitor * visitor)
{
	visitor->Visit(this);
	for (auto& v : m_hitList) {
		visitor->Visit(v);
	}
}

/// <summary>
/// 当たったオブジェクトを返す
/// 当たり判定同士の情報の受け渡しに使用
/// </summary>
ObjectBase * ShunLib::ICollider::HitParent()
{
	if (m_shouldPassParentInfo) {
		return m_parent;
	}
	return nullptr;
}

/// <summary>
/// 使用している状態かどうか
/// </summary>
bool ICollider::IsEnable()
{
	bool isEnable = m_isEnable;
	if (m_parent != nullptr){
		isEnable = (isEnable && m_parent->IsEnable());
	}
	return isEnable;
}


//球状の当たり判定の更新
void SphereCollider::Update()
{
	//基底クラスの更新
	ICollider::Update();

	//位置同期
	if (m_parent != nullptr){
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
	}
}

//箱状の当たり判定の更新
void BoxCollider::Update()
{
	//基底クラスの更新
	ICollider::Update();

	//位置同期
	if (m_parent != nullptr) {
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
		Shape()->Scale(m_parent->Transform().Scale());
	}
}
