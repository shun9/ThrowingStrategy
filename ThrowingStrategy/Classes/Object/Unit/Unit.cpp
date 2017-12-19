//************************************************/
//* @file  :Unit.cpp
//* @brief :��������郆�j�b�g
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitFlyState.h"
#include "State\UnitSteadyState.h"
#include "State\UnitRoamState.h"
#include "../../Physics/PhysicsConstantNumber.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/HPGauge/HPGauge.h"

Unit::Unit():
	StateObject(this, OBJECT_LIST::UNIT),
	m_attackInterval(2.0f)
{
	//�{�̂̓����蔻��̐ݒ�
	m_collider = new SphereCollider();
	m_collider->Parent(this);
	m_collider->PosObj(this);
	m_collider->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Scale(UNIT_CONSTANT::COLLIDER_BODY_SIZE);

	//�U���͈͂̐ݒ�
	m_attackRange = new SphereCollider;
	m_attackRange->PosObj(this);
	m_attackRange->AddChildCollider(m_collider);
	m_attackRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_attackRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_ATTACK_SIZE);
	m_attackRange->IsDebugDraw(false);

	//�ǐՔ͈͂̐ݒ�
	m_chaseRange = new SphereCollider;
	m_chaseRange->PosObj(this);
	m_chaseRange->AddChildCollider(m_attackRange);
	m_chaseRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_chaseRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_CHASE_SIZE);
	m_chaseRange->IsDebugDraw(false);

	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(UNIT_CONSTANT::HP_GAUGE_OFFSET);
}

void Unit::Initialize()
{
	//������Ԑݒ�
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
/// �������
/// </summary>
void Unit::ToBeLifted()
{
	this->ChangeState(new UnitSteadyState);
}

/// <summary>
/// ��������
/// </summary>
void Unit::ToBeThrow(const FlyingData& data)
{
	auto tmp = new UnitFlyState;
	tmp->SetData(data);
	this->ChangeState(tmp);
}