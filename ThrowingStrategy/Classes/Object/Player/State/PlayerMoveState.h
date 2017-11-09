//************************************************/
//* @file  :PlayerMoveState.h
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
class Player;

class PlayerMoveState : public ShunLib::State<Player>
{
public:
	PlayerMoveState() {}
	~PlayerMoveState() {}

public:
	//開始処理
	void Enter(Player* player);

	//実行処理
	void Execute(Player* player);

	//終了処理
	void Exit(Player* player);

};