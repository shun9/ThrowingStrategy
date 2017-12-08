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
	StateObject(this, OBJECT_LIST::COMMANDER),
	m_capacity(1),
	m_throwingPower(1.0f),
	m_throwingAngle(45.0f)
{
	//‰ŠúÝ’è
	this->Pos(ShunLib::Vec3(-5.0f,0.0f,0.0f));

	//“–‚½‚è”»’è‚ÌÝ’è
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->PosObj(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.0f, 0.0f));

	//“–‚½‚è”»’è‚ÌŒ`ó‚ÌÝ’è
	m_collider->Shape()->Scale(1.0f);
}

Commander::~Commander()
{
	SAFE_DELETE(m_collider);
}

void Commander::Initialize()
{
	StateObject::Initialize();
	this->ChangeState(new CommanderMoveState);
}

void Commander::Finalize()
{
	StateObject::Finalize();
}
