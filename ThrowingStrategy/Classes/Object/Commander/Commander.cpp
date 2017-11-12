//************************************************/
//* @file  :Commander.cpp
//* @brief :�w����
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "Commander.h"
#include "CommanderMoveState.h"

#include <SL_MacroConstants.h>

Commander::Commander() :
	StateObject(this),
	m_capacity(1),
	m_throwingPower(1.0f),
	m_throwingAngle(45.0f)
{
	//�����蔻��̐ݒ�
	m_collider = new ShunLib::BoxCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.5f, 0.0f));

	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(1.0f);
	m_collider->Shape()->Size(ShunLib::Vec3(1.0f,3.0f,1.0f));
}

Commander::~Commander()
{
	SAFE_DELETE(m_collider);
}

void Commander::Initialize()
{
	this->ChangeState(new CommanderMoveState);
	this->Type(COMMANDER);
	StateObject::Initialize();
}

void Commander::Finalize()
{
	StateObject::Finalize();
}
