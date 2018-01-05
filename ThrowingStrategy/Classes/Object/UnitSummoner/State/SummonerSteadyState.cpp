//************************************************/
//* @file  :SummonerSteadyState.h
//* @brief :召喚するオブジェクトの待機状態
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#include "SummonerSteadyState.h"
#include "SummonerSummonState.h"

#include "../../../Main/SL_MyStepTimer.h"

void SummonerSteadyState::Enter(UnitSummoner * summoner)
{
	//時間設定　現在は適当な値
	m_timer.SetTime(summoner->Interval());
}

void SummonerSteadyState::Execute(UnitSummoner * summoner)
{
	//タイマーの更新
	m_timer.Update();

	//時間が来たら召喚する
	if (m_timer.IsEnded()){
		summoner->ChangeState(new SummonerSummonState);
	}
}

void SummonerSteadyState::Exit(UnitSummoner * summoner)
{
	m_timer.ResetCount();
}
