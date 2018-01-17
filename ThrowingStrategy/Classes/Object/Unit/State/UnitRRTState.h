//************************************************/
//* @file  :UnitRRTState.h
//* @brief :ユニットをRRTで動かしてみた
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_Timer.h>
#include "../Unit.h"
#include "../../../AI/RRT.h"

class UnitRRTState : public ShunLib::State<Unit>
{
private:
	RRT::Route m_route;
	int m_routeIndex;
	float m_timeCnt;
	float m_routeUpdateInterval;

public:
	UnitRRTState(){}
	~UnitRRTState() {}

	//開始処理
	void Enter(Unit* unit);

	//実行処理
	void Execute(Unit* unit);

	//終了処理
	void Exit(Unit* unit);

private:
	//ルート更新
	void UpdateRoute(Unit* unit);
};
