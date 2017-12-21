//************************************************/
//* @file  :CommanderMoveState.cpp
//* @brief :ŽwŠöŠ¯‚ÌˆÚ“®ó‘Ô
//* @date  :2017/10/31
//* @author:S.Katou
//************************************************/
#include "CommanderMoveState.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../Util/Debugger/DebuggerUI.h"

void CommanderMoveState::Enter(Commander * obj)
{

}

void CommanderMoveState::Execute(Commander * obj)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	auto pos = obj->Transform().Pos();

	pos.m_x += 1.0f * timer->GetElapsedSeconds();

	obj->Transform().Pos(pos);

	DebuggerUI::GetInstance()->DrawDebugText("Commander HP : %d", obj->Data().HP());
}

void CommanderMoveState::Exit(Commander * obj)
{
}
