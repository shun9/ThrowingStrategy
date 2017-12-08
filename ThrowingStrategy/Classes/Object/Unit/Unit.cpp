//************************************************/
//* @file  :Unit.cpp
//* @brief :召喚されるユニット
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitFlyState.h"
#include "State\UnitSteadyState.h"
#include "State\UnitRoamState.h"
#include "../../Physics/PhysicsConstantNumber.h"
#include "../../Main/SL_MyStepTimer.h"

Unit::Unit():
	StateObject(this, OBJECT_LIST::UNIT),
	m_attackInterval(2.0f)
{
	//チーム設定(仮)　※いずれ消す
	this->Team(TEAM::BLUE);

	//基本情報設定
	this->ChangeState(new UnitRoamState);

	//基底クラスの初期化
	StateObject::Initialize();

	//本体の当たり判定の設定
	m_collider = new SphereCollider();
	m_collider->Parent(this);
	m_collider->PosObj(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_collider->Shape()->Scale(1.0f);

	//攻撃範囲の設定
	m_attackRange = new SphereCollider;
	m_attackRange->PosObj(this);
	m_attackRange->AddChildCollider(m_collider);
	m_attackRange->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_attackRange->Shape()->Scale(2.0f);
	m_attackRange->IsDebugDraw(false);

	//追跡範囲の設定
	m_chaseRange = new SphereCollider;
	m_chaseRange->PosObj(this);
	m_chaseRange->AddChildCollider(m_attackRange);
	m_chaseRange->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_chaseRange->Shape()->Scale(4.0f);
	m_chaseRange->IsDebugDraw(false);
}

void Unit::Initialize()
{
}


void Unit::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_attackRange);
	SAFE_DELETE(m_chaseRange);
}

/// <summary>
/// 持たれる
/// </summary>
void Unit::ToBeLifted()
{
	this->ChangeState(new UnitSteadyState);
}

/// <summary>
/// 投げられる
/// </summary>
void Unit::ToBeThrow(const FlyingData& data)
{
	auto tmp = new UnitFlyState;
	tmp->SetData(data);
	this->ChangeState(tmp);
}