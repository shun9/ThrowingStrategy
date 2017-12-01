//************************************************/
//* @file  :Unit.cpp
//* @brief :��������郆�j�b�g
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
	//�`�[���ݒ�(��)�@�����������
	this->Team(TEAM::RED);

	//��{���ݒ�
	this->ChangeState(new UnitRoamState);
	this->Type(OBJECT_LIST::UNIT);
	this->HP(this->MaxHP());
	
	//���N���X�̏�����
	StateObject::Initialize();

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.6f, 0.0f));
	m_collider->Shape()->Scale(1.0f);

	//�U���͈͂̐ݒ�
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