//************************************************/
//* @file  :UnitMoveState.h
//* @brief :召喚されるユニットの移動状態
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"

class UnitMoveState : public ShunLib::State<Unit>
{
public:
	UnitMoveState() {}
	~UnitMoveState() {}

	//開始処理
	void Enter(Unit* obj);

	//実行処理
	void Execute(Unit* obj);

	//終了処理
	void Exit(Unit* obj);

};