//************************************************/
//* @file  :UnitSteadyState.h
//* @brief :召喚されるユニットの動かない状態
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../Unit.h"

class UnitSteadyState : public ShunLib::State<Unit>
{
public:
	UnitSteadyState() {}
	~UnitSteadyState() {}

	//開始処理
	void Enter(Unit* obj);

	//実行処理
	void Execute(Unit* obj);

	//終了処理
	void Exit(Unit* obj);
};