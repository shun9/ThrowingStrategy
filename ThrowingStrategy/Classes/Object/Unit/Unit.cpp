//************************************************/
//* @file  :Unit.cpp
//* @brief :��������郆�j�b�g
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitMoveState.h"
#include "State\UnitSteadyState.h"
#include "State\UnitFlyState.h"
#include "../../Physics/PhysicsConstantNumber.h"
#include "../../Main/SL_MyStepTimer.h"

void Unit::Initialize()
{
	this->Team(TEAM::RED);
	this->ChangeState(new UnitMoveState);
	this->Type(OBJECT_LIST::UNIT);
	StateObject::Initialize();

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));

	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(1.0f);
}


void Unit::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
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