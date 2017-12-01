//************************************************/
//* @file  :SummonerSummonState.h
//* @brief :召喚するオブジェクトの召喚中状態
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../UnitSummoner.h"

class SummonerSummonState : public ShunLib::State<UnitSummoner>
{
public:
	SummonerSummonState() {}
	~SummonerSummonState() {}

	//開始処理
	void Enter(UnitSummoner* summoner);

	//実行処理
	void Execute(UnitSummoner* summoner);

	//終了処理
	void Exit(UnitSummoner* summoner);
};