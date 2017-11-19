//************************************************/
//* @file  :UnitSteadyState.cpp
//* @brief :召喚されるユニットの動かない状態
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
