//************************************************/
//* @file  :UnitAttackState.cpp
//* @brief :召喚されるユニットの攻撃状態
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "UnitAttackState.h"
#include "UnitChaseState.h"

#include <cmath>
#include <SL_Conversion.h>
#include "../../../Util/Visitor/Visitor.h"

using namespace ShunLib;

void UnitAttackState::Enter(Unit* unit)
{
	SearchStateObjectVisitor sV;
	SearchAnotherTeamVisitor aV(unit->Team());
	unit->AttackRange()->Accept(&sV);
	sV.Accept(&aV);

	//当たっているオブジェクトが存在するならば
	//ターゲットに設定
	if (aV.Count() > 0) {
		m_target = aV.List()[0];
	}

	m_intervalTimer.SetTime(60);
}

void UnitAttackState::Execute(Unit* unit)
{
	//ターゲットが無ければ何もしない
	if (m_target == nullptr){
		unit->ChangeState(new UnitChaseState);
		return;
	}

	//タイマー更新
	m_intervalTimer.Update();

	//ユニットからターゲットへ向かうベクトル
	Vec3 dir = m_target->Pos() - unit->Pos();
	
	//攻撃範囲から外れたら戻る
	SearchSpecificObjectVisitor v(m_target);
	unit->AttackRange()->Accept(&v);
	if (!v.IsFound()){
		unit->ChangeState(new UnitChaseState);
		return;
	}

	//X,Zの二次元で向き直す
	//見上げたり、見下げることはない
	dir.m_y = 0.0f;
	float rot = ToAngle(std::atan2(dir.m_z, dir.m_x)) - 90.0f;

	//ユニットの向きを変える
	Vec3 uRot = unit->Rotation();
	uRot.m_y = rot;
	unit->Rotation(uRot);

	//一定間隔でターゲットに攻撃
	if (m_intervalTimer.IsEnded()){
		m_intervalTimer.ResetCount();
		m_target->TakeDamage((int)(unit->Power()));
	}
}

void UnitAttackState::Exit(Unit* unit)
{

}
