//************************************************/
//* @file  :UnitRoamState.h
//* @brief :召喚されるユニットのうろつき状態
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"

class UnitRoamState : public ShunLib::State<Unit>
{
private:
	float m_timeCnt;
	float m_limit;

	ShunLib::Vec3 m_direction;

public:
	UnitRoamState():
		m_timeCnt(0.0f),
		m_limit(3.0f){}
	~UnitRoamState() {}

	//開始処理
	void Enter(Unit* obj);

	//実行処理
	void Execute(Unit* obj);

	//終了処理
	void Exit(Unit* obj);

private:
	void ChangeDirection();
};