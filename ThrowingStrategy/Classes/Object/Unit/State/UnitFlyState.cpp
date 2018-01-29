//************************************************/
//* @file  :UnitFlyState.cpp
//* @brief :ユニットの飛ぶ状態
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "UnitFlyState.h"

#include <SL_Lerp.h>
#include "UnitRoamState.h"
#include "../../../Main/SL_MyStepTimer.h"

using namespace ShunLib;

void UnitFlyState::Enter(Unit * unit)
{
	//1秒あたり1進む設定
	m_timeLimit = (m_data.start - m_data.end).Length() / m_data.power;
	m_timeCnt = 0.0f;

	//速度を制限しない
	unit->Data().ShouldLimitVel(false);
	unit->Data().UseGravity(false);

	//方向を設定
	m_dir = m_data.end - m_data.start;
	m_dir.Normalize();

	//投げ方が設定されていない場合
	if (m_data.Lerp() == NULL) { m_data.type = ObjectConstantNumber::THROW_TYPE::LINE; }

}

void UnitFlyState::Execute(Unit * unit)
{
	unit->Transform().Velocity(m_dir * m_data.power);

	//移動
	unit->Move();

	//時間をカウント
	//パワーの分だけ早く進める
	m_timeCnt += MyStepTimer::GetInstance()->GetElapsedSeconds();

	//移動しきったら状態切替
	if (m_timeCnt > m_timeLimit){
		unit->ChangeState(new UnitRoamState);
	}
}

void UnitFlyState::Exit(Unit * unit)
{
	//速度を制限しない
	unit->Data().ShouldLimitVel(true);
	unit->Data().UseGravity(true);
}
