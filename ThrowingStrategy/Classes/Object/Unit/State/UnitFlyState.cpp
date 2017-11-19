//************************************************/
//* @file  :UnitFlyState.cpp
//* @brief :ユニットの飛ぶ状態
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "UnitFlyState.h"

#include <SL_Lerp.h>
#include "UnitMoveState.h"
#include "../../../Main/SL_MyStepTimer.h"

void UnitFlyState::Enter(Unit * unit)
{
	//1秒あたり1進む設定
	m_timeLimit = (m_data.start - m_data.end).Length();
	m_timeCnt = 0.0f;

	//投げ方が設定されていない場合
	if (m_data.Lerp() == NULL) { m_data.type = THROW_TYPE::LINE; }
}

void UnitFlyState::Execute(Unit * unit)
{
	using namespace ShunLib;

	//補間によって位置を出す
	Vec3 v = Vec3::Larp(m_data.start, m_data.end, m_timeCnt/m_timeLimit, m_data.Lerp());
	unit->Pos(v);

	//時間をカウント
	//パワーの分だけ早く進める
	m_timeCnt += MyStepTimer::GetInstance()->GetElapsedSeconds() * m_data.power;

	//移動しきったら状態切替
	if (m_timeCnt > m_timeLimit){
		unit->ChangeState(new UnitMoveState);
	}
}

void UnitFlyState::Exit(Unit * unit)
{
}
