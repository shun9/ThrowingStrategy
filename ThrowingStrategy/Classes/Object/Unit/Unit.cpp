//************************************************/
//* @file  :Unit.cpp
//* @brief :召喚されるユニット
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitFlyState.h"
#include "State\UnitSteadyState.h"
#include "State\UnitRoamState.h"
#include "../../Physics/PhysicsConstantNumber.h"
#include "../../Main/SL_MyStepTimer.h"

void Unit::Initialize()
{
	//チーム設定(仮)　※いずれ消す
	this->Team(TEAM::RED);

	//基本情報設定
	this->ChangeState(new UnitRoamState);
	this->Type(OBJECT_LIST::UNIT);
	this->HP(this->MaxHP());
	
	//基底クラスの初期化
	StateObject::Initialize();

	//当たり判定の設定
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_collider->Shape()->Scale(1.0f);

	//攻撃範囲の設定
	m_attackRange = new ShunLib::SphereCollider;
	m_attackRange->Parent(this);
	m_attackRange->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_attackRange->Shape()->Scale(4.0f);
	m_attackRange->IsDebugDraw(false);
}


void Unit::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_attackRange);
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