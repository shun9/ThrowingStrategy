//************************************************/
//* @file  :SummonerSummonState.h
//* @brief :召喚するオブジェクトの召喚中状態
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#include "SummonerSummonState.h"
#include "SummonerSteadyState.h"

void SummonerSummonState::Enter(UnitSummoner* summoner)
{

}

void SummonerSummonState::Execute(UnitSummoner* summoner)
{
	summoner->Summon();
	summoner->ChangeState(new SummonerSteadyState);
}

void SummonerSummonState::Exit(UnitSummoner* summoner)
{

}
