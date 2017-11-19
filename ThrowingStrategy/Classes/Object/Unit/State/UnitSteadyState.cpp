//************************************************/
//* @file  :UnitSteadyState.cpp
//* @brief :¢Š«‚³‚ê‚éƒ†ƒjƒbƒg‚Ì“®‚©‚È‚¢ó‘Ô
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "UnitSteadyState.h"

void UnitSteadyState::Enter(Unit * obj)
{
	//obj->IsPhysically(false);
}

void UnitSteadyState::Execute(Unit * obj)
{
	obj->Move();
}

void UnitSteadyState::Exit(Unit * obj)
{
	//obj->IsPhysically(true);

}
