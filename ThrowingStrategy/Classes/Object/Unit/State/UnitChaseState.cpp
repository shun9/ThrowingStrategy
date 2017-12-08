//************************************************/
//* @file  :UnitChaseState.cpp
//* @brief :召喚ユニットの追跡状態
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#include "UnitChaseState.h"
#include "UnitAttackState.h"
#include "UnitRoamState.h"

#include "../Unit.h"

#include "../../../Util/Visitor/Visitor.h"

void UnitChaseState::Enter(Unit * unit)
{

}

void UnitChaseState::Execute(Unit* unit)
{
	//当たっているオブジェクトから
	//別のチームのオブジェクトを探す
	SearchAnotherTeamVisitor aV(unit->Team());
	unit->ChaseRange()->Accept(&aV);

	//別チームのオブジェクトから
	//最も近くにいるオブジェクトを探す
	Vec3 unitPos = unit->WorldPos();
	SearchNearestObjectVisitor nV(unitPos);
	aV.Accept(&nV);
	auto target = nV.Object();

	//何も当たっていなければ
	//状態を切り替える
	if (target == nullptr){
		unit->ChangeState(new UnitRoamState);
		return;
	}
	
	Vec3 dir = target->WorldPos() - unitPos;
	dir.Normalize();

	unit->Velocity(dir * unit->Spd());

	unit->Move();

	aV.Reset();
	unit->AttackRange()->Accept(&aV);

	if (aV.Count() > 0){
		unit->ChangeState(new UnitAttackState);
		return;
	}
}

void UnitChaseState::Exit(Unit * unit)
{

}
