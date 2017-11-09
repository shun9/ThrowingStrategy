//************************************************/
//* @file  :Unit.cpp
//* @brief :召喚されるユニット
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#include "Unit.h"
#include "State\UnitMoveState.h"

void Unit::Initialize()
{
	this->ChangeState(new UnitMoveState);
	this->Type(UNIT);
	StateObject::Initialize();
}

void Unit::Finalize()
{
	StateObject::Finalize();
}
