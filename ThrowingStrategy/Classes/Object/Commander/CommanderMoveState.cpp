//************************************************/
//* @file  :CommanderMoveState.cpp
//* @brief :ŽwŠöŠ¯‚ÌˆÚ“®ó‘Ô
//* @date  :2017/10/31
//* @author:S.Katou
//************************************************/
#include "CommanderMoveState.h"
#include "../../Main/SL_MyStepTimer.h"

void CommanderMoveState::Enter(Commander * obj)
{

}

void CommanderMoveState::Execute(Commander * obj)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	auto pos = obj->Pos();

	pos.m_x += 1.0f * timer->GetElapsedSeconds();

	obj->Pos(pos);
}

void CommanderMoveState::Exit(Commander * obj)
{
}
