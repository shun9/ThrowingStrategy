//************************************************/
//* @file  :UnitChaseState.h
//* @brief :召喚ユニットの追跡状態
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_Math.h>

class Unit;

class UnitChaseState : public ShunLib::State<Unit>
{
public:
	using Vec3 = ShunLib::Vec3;

public:
	UnitChaseState() {}
	~UnitChaseState() {}

	//開始処理
	void Enter(Unit* unit);

	//実行処理
	void Execute(Unit* unit);

	//終了処理
	void Exit(Unit* unit);
};