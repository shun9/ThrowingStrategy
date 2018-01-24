//************************************************/
//* @file  :Unit.cpp
//* @brief :召喚されるユニット
//* @date  :2018/01/11
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitState.h"
#include "../../Physics/Collision/SL_CollisionManager.h"
#include "../../Physics/PhysicsConstantNumber.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/HPGauge/HPGauge.h"

Unit::Unit():
	StateObject(this, OBJECT_LIST::UNIT),
	m_attackInterval(2.0f)
{
	using namespace ShunLib;

	//本体の当たり判定の設定
	m_collider = new SphereCollider(COLLIDER_LAYER::RIGID);
	m_collider->Parent(this);
	m_collider->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Scale(UNIT_CONSTANT::COLLIDER_BODY_SIZE);

	//攻撃範囲の設定
	m_attackRange = new SphereCollider(COLLIDER_LAYER::TRIGGER);
	m_attackRange->Parent(this);
	m_attackRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_attackRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_ATTACK_SIZE);
	m_attackRange->ShouldPassInfo(false);
	m_attackRange->IsDebugDraw(false);

	//追跡範囲の設定
	m_chaseRange = new SphereCollider(COLLIDER_LAYER::TRIGGER);
	m_chaseRange->Parent(this);
	m_chaseRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_chaseRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_CHASE_SIZE);
	m_chaseRange->ShouldPassInfo(false);
	m_chaseRange->IsDebugDraw(false);

	//HPゲージ
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(UNIT_CONSTANT::HP_GAUGE_OFFSET);
}

void Unit::Initialize()
{
	//初期状態設定
	this->ChangeState(new UnitRoamState);

	StateObject::Initialize();
}


void Unit::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_attackRange);
	SAFE_DELETE(m_chaseRange);
	SAFE_DELETE(m_hpGauge);
}

/// <summary>
/// 持たれる
/// </summary>
void Unit::ToBeLifted()
{
	//何もしない状態
	this->ChangeState(new UnitSteadyState);

	//すべての速度を0にする
	m_data.UseGravity(false);
	m_transform.Velocity(ShunLib::Vec3::Zero);

	//一番下のユニットと投げられたユニットが衝突し
	//位置がずれるため持たれている間は当たり判定を使用しない
	DisableCollider();
}

/// <summary>
/// 置かれる
/// </summary>
void Unit::ToBePlaced()
{
	//何もしない状態
	this->ChangeState(new UnitRoamState);

	//重力を使用
	m_data.UseGravity(true);

	//当たり判定を使用
	EnableCollider();
}

/// <summary>
/// 投げられる
/// </summary>
void Unit::ToBeThrow(const FlyingData& data)
{
	//投げられた時の情報を設定
	auto tmp = new UnitFlyState;
	tmp->SetData(data);
	this->ChangeState(tmp);

	//当たり判定を使用
	EnableCollider();
}

/// <summary>
/// 当たり判定を使用する
/// </summary>
void Unit::EnableCollider()
{
	m_collider->IsEnable(true);
	m_attackRange->IsEnable(true);
	m_chaseRange->IsEnable(true);
}

/// <summary>
/// 当たり判定を使用しない
/// </summary>
void Unit::DisableCollider()
{
	m_collider->IsEnable(false);
	m_attackRange->IsEnable(false);
	m_chaseRange->IsEnable(false);
}
