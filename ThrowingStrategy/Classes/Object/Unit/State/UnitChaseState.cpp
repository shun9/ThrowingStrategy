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
	//ユニットから最も近いオブジェクト
	auto target = SearchTarget(unit);

	//何も当たっていなければ
	//状態を切り替える
	if (target == nullptr){
		unit->ChangeState(new UnitRoamState);
		return;
	}

	//ユニットからターゲットへ向かうベクトル
	Vec3 dir = target->WorldPos() - unit->WorldPos();
	dir.Normalize();

	//ユニットの速度を設定　移動
	unit->Transform().Velocity(dir * unit->Data().Spd());
	unit->Move();

	//攻撃範囲内にいる別チームのオブジェクトを探す
	SearchAnotherTeamVisitor aV(unit->Data().Team());
	aV.Reset();
	unit->AttackRange()->Accept(&aV);

	//攻撃範囲に別チームのオブジェクトがいたら攻撃状態に移行
	if (aV.Count() > 0){
		unit->ChangeState(new UnitAttackState);
		return;
	}
}

void UnitChaseState::Exit(Unit * unit)
{

}

/// <summary>
/// ユニットから最も近い敵チームオブジェクトを探す
/// </summary>
/// <param name="unit">ユニット</param>
/// <returns>敵チームオブジェクト</returns>
ObjectBase* UnitChaseState::SearchTarget(Unit * unit)
{
	//当たっているオブジェクトから
	//別のチームのオブジェクトを探す
	SearchAnotherTeamVisitor aV(unit->Data().Team());
	unit->ChaseRange()->Accept(&aV);

	//別チームのオブジェクトから
	//最も近くにいるオブジェクトを探す
	Vec3 unitPos = unit->WorldPos();
	SearchNearestObjectVisitor nV(unitPos);
	aV.Accept(&nV);

	return nV.Object();
}
