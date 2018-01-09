//************************************************/
//* @file  :UnitFlyState.h
//* @brief :ユニットの飛ぶ状態
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"
#include "../../ObjectStruct.h"

class UnitFlyState : public ShunLib::State<Unit>
{
private:
	//飛行用データ
	FlyingData m_data;

	//時間
	float m_timeLimit;
	float m_timeCnt;

public:
	UnitFlyState():
		m_timeLimit(1.0f),
		m_timeCnt(0.0f)
	{}
	~UnitFlyState() {}

	//開始処理
	void Enter(Unit* obj);

	//実行処理
	void Execute(Unit* obj);

	//終了処理
	void Exit(Unit* obj);

	//データ設定
	void SetData(const FlyingData& data) { m_data = data; }
};