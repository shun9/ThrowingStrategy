//************************************************/
//* @file  :CommanderMoveState.h
//* @brief :指揮官の移動状態
//* @date  :2017/10/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "Commander.h"

class CommanderMoveState :public ShunLib::State<Commander>
{
public:
	CommanderMoveState() {}
	~CommanderMoveState() {}

	//開始処理
	void Enter(Commander* obj);

	//実行処理
	void Execute(Commander* obj);

	//終了処理
	void Exit(Commander* obj);
};
