//************************************************/
//* @file  :UnitRoamState.cpp
//* @brief :召喚されるユニットのうろつき状態
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "UnitRoamState.h"

#include <cmath>
#include <SL_Conversion.h>
#include <SL_RandomNumber.h>
#include "../../../Main/SL_MyStepTimer.h"

using namespace std;
using namespace ShunLib;

void UnitRoamState::Enter(Unit * obj)
{
	ChangeDirection();
}

void UnitRoamState::Execute(Unit * obj)
{
	auto timer = MyStepTimer::GetInstance();
	m_timeCnt += timer->GetElapsedSeconds();
	
	//一定時間ごとに移動先を変更
	if (m_timeCnt > m_limit){
		//進む方向を変える
		ChangeDirection();

		m_timeCnt = 0.0f;
	}

	//速度設定
	obj->Velocity(m_direction * obj->Spd());

	obj->Move();
}

void UnitRoamState::Exit(Unit * obj)
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
