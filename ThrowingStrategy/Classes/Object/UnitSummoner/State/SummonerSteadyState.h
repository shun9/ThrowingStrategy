//************************************************/
//* @file  :SummonerSteadyState.h
//* @brief :召喚するオブジェクトの待機状態
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_Timer.h>
#include "../UnitSummoner.h"

class SummonerSteadyState : public ShunLib::State<UnitSummoner>
{
private:
	ShunLib::Timer m_timer;

public:
	SummonerSteadyState() {}
	~SummonerSteadyState() {}

	//開始処理
	void Enter(UnitSummoner* summoner);

	//実行処理
	void Execute(UnitSummoner* summoner);

	//終了処理
	void Exit(UnitSummoner* summoner);
};