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
	//�����ݒ�
	this->Team(TEAM::RED);
	this->Pos(ShunLib::Vec3(-5.0f,0.0f,0.0f));
	this->Type(OBJECT_LIST::COMMANDER);

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.0f, 0.0f));

	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(1.0f);
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
