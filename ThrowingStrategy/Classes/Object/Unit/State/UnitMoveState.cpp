//************************************************/
//* @file  :UnitMoveState.cpp
//* @brief :¢Š«‚³‚ê‚éƒ†ƒjƒbƒg‚ÌˆÚ“®ó‘Ô
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#include "UnitMoveState.h"
#include "../../../Main/SL_MyStepTimer.h"
#include "../../../Util/Debugger/DebuggerUI.h"

void UnitMoveState::Enter(Unit * obj)
{

}

void UnitMoveState::Execute(Unit * obj)
{
	DebuggerUI::GetInstance()->DrawDebugText("Rotation unit: (%.2f,%.2f,%.2f)", obj->Rotation().m_x, obj->Rotation().m_y, obj->Rotation().m_z);
	DebuggerUI::GetInstance()->DrawDebugText("Velocity unit: (%.2f,%.2f,%.2f)", obj->Velocity().m_x, obj->Velocity().m_y, obj->Velocity().m_z);
}

void UnitMoveState::Exit(Unit * obj)
{

}
