//************************************************/
//* @file  :Unit.cpp
//* @brief :��������郆�j�b�g
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

	//�{�̂̓����蔻��̐ݒ�
	m_collider = new SphereCollider(COLLIDER_LAYER::RIGID);
	m_collider->Parent(this);
	m_collider->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Scale(UNIT_CONSTANT::COLLIDER_BODY_SIZE);

	//�U���͈͂̐ݒ�
	m_attackRange = new SphereCollider(COLLIDER_LAYER::TRIGGER);
	m_attackRange->Parent(this);
	m_attackRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_attackRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_ATTACK_SIZE);
	m_attackRange->ShouldPassInfo(false);
	m_attackRange->IsDebugDraw(false);

	//�ǐՔ͈͂̐ݒ�
	m_chaseRange = new SphereCollider(COLLIDER_LAYER::TRIGGER);
	m_chaseRange->Parent(this);
	m_chaseRange->Offset(UNIT_CONSTANT::COLLIDER_OFFSET);
	m_chaseRange->Shape()->Scale(UNIT_CONSTANT::COLLIDER_CHASE_SIZE);
	m_chaseRange->ShouldPassInfo(false);
	m_chaseRange->IsDebugDraw(false);

	//HP�Q�[�W
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
	//�������Ȃ����
	this->ChangeState(new UnitSteadyState);

	//���ׂĂ̑��x��0�ɂ���
	m_data.UseGravity(false);
	m_transform.Velocity(ShunLib::Vec3::Zero);

	//��ԉ��̃��j�b�g�Ɠ�����ꂽ���j�b�g���Փ˂�
	//�ʒu������邽�ߎ�����Ă���Ԃ͓����蔻����g�p���Ȃ�
	DisableCollider();
}

/// <summary>
/// �u�����
/// </summary>
void Unit::ToBePlaced()
{
	//�������Ȃ����
	this->ChangeState(new UnitRoamState);

	//�d�͂��g�p
	m_data.UseGravity(true);

	//�����蔻����g�p
	EnableCollider();
}

/// <summary>
/// ��������
/// </summary>
void Unit::ToBeThrow(const FlyingData& data)
{
	//������ꂽ���̏���ݒ�
	auto tmp = new UnitFlyState;
	tmp->SetData(data);
	this->ChangeState(tmp);

	//�����蔻����g�p
	EnableCollider();
}

/// <summary>
/// �����蔻����g�p����
/// </summary>
void Unit::EnableCollider()
{
	m_collider->IsEnable(true);
	m_attackRange->IsEnable(true);
	m_chaseRange->IsEnable(true);
}

/// <summary>
/// �����蔻����g�p���Ȃ�
/// </summary>
void Unit::DisableCollider()
{
	m_collider->IsEnable(false);
	m_attackRange->IsEnable(false);
	m_chaseRange->IsEnable(false);
}
