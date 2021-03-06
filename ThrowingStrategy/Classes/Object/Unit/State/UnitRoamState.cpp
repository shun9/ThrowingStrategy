//************************************************/
//* @file  :UnitRoamState.cpp
//* @brief :召喚されるユニットのうろつき状態
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "UnitRoamState.h"
#include "UnitChaseState.h"

#include <cmath>
#include <SL_Conversion.h>
#include <SL_RandomNumber.h>
#include "../../../Main/SL_MyStepTimer.h"
#include "../../../Util/Visitor/Visitor.h"

using namespace std;
using namespace ShunLib;

void UnitRoamState::Enter(Unit * unit)
{
	ChangeDirection();
}

void UnitRoamState::Execute(Unit * unit)
{
	//時間を計測
	auto timer = MyStepTimer::GetInstance();
	m_timeCnt += timer->GetElapsedSeconds();
	
	//一定時間ごとに移動先を変更
	if (m_timeCnt > m_limit){
		//進む方向を変える
		ChangeDirection();

		m_timeCnt = 0.0f;
	}

	//速度設定 移動
	unit->Velocity(m_direction * unit->Spd());
	unit->Move();

	//追跡範囲に敵がいた場合
	SearchAnotherTeamVisitor v(unit->Team());
	unit->ChaseRange()->Accept(&v);
	if (v.Count() > 0) {
		unit->ChangeState(new UnitChaseState);
	}
}

void UnitRoamState::Exit(Unit * unit)
{

}

void UnitRoamState::ChangeDirection()
{
	RandomNumber rn;

	//進む方向をランダムに設定
	float rad = ToRadian(rn(0.0f, 360.0f));

	//速度設定
	m_direction = Vec3(-sin(rad), 0.0f, cos(rad)).Normalize();
}
