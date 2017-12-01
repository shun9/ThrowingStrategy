//************************************************/
//* @file  :SummonerSteadyState.h
//* @brief :��������I�u�W�F�N�g�̑ҋ@���
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#include "SummonerSteadyState.h"
#include "SummonerSummonState.h"

void SummonerSteadyState::Enter(UnitSummoner * summoner)
{
	m_timer.SetTime(600);
}

void SummonerSteadyState::Execute(UnitSummoner * summoner)
{
	m_timer.Update();

	if (m_timer.IsEnded()){
		summoner->ChangeState(new SummonerSummonState);
	}
}

void SummonerSteadyState::Exit(UnitSummoner * summoner)
{
	m_timer.ResetCount();
}
