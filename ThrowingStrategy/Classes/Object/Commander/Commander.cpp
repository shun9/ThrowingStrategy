//************************************************/
//* @file  :Commander.cpp
//* @brief :ŽwŠöŠ¯
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
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
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
