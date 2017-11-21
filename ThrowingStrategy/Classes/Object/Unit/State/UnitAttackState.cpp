//************************************************/
//* @file  :UnitAttackState.cpp
//* @brief :召喚されるユニットの攻撃状態
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "UnitAttackState.h"
#include "UnitRoamState.h"

#include <cmath>
#include <SL_Conversion.h>

using namespace ShunLib;

void UnitAttackState::Enter(Unit* unit)
{
	auto hitList = unit->AttackRange()->HitList();

	//当たっているオブジェクトが無ければ何もしない
	if (!hitList.empty()){
		m_target = hitList[0];
	}
}

void UnitAttackState::Execute(Unit* unit)
{
	//ターゲットが無ければ何もしない
	if (m_target == nullptr){
		unit->ChangeState(new UnitRoamState);
	}

	//ユニットからターゲットへ向かうベクトル
	Vec3 dir = m_target->Pos() - unit->Pos();
	
	//攻撃範囲から外れたら戻る
	if (dir.Length() > unit->AttackRange()->Shape()->Scale()){
		unit->ChangeState(new UnitRoamState);
	}

	//X,Zの二次元で向き直す
	//見上げたり、見下げることはない
	dir.m_y = 0.0f;

	float rot = ToAngle(std::atan2(dir.m_z, dir.m_x)) - 90.0f;

	Vec3 uRot = unit->Rotation();
	uRot.m_y = rot;
	unit->Rotation(uRot);
}

void UnitAttackState::Exit(Unit* unit)
{

}
