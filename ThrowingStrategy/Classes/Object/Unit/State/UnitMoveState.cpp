//************************************************/
//* @file  :UnitMoveState.cpp
//* @brief :¢Š«‚³‚ê‚éƒ†ƒjƒbƒg‚ÌˆÚ“®ó‘Ô
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#include "UnitMoveState.h"
#include "../../../Main/SL_MyStepTimer.h"

void UnitMoveState::Enter(Unit * obj)
{

}

void UnitMoveState::Execute(Unit * obj)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	auto pos = obj->Pos();
	pos.m_x -= 0.1f * timer->GetElapsedSeconds();
	obj->Pos(pos);
}

void UnitMoveState::Exit(Unit * obj)
{

}
