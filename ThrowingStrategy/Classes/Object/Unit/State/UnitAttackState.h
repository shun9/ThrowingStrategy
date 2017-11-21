//************************************************/
//* @file  :UnitAttackState.h
//* @brief :召喚されるユニットの攻撃状態
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../Unit.h"

class UnitAttackState : public ShunLib::State<Unit>
{
private:
	ObjectBase* m_target;

public:
	UnitAttackState():
		m_target(nullptr) {}
	~UnitAttackState() {}

	//開始処理
	void Enter(Unit* unit);

	//実行処理
	void Execute(Unit* unit);

	//終了処理
	void Exit(Unit* unit);
};
