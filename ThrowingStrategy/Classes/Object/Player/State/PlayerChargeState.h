//************************************************/
//* @file  :PlayerChargeState.h
//* @brief :プレイヤーの移動状態
//* @date  :2018/01/25
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_CommandInput.h>
#include <SL_State.h>
#include <SL_KeyManager.h>
#include "../../../Util/SL_GamePadManager.h"

class Player;

class PlayerChargeState : public ShunLib::State<Player>
{
private:
	using BUTTON_LIST = ShunLib::GamePadManager::BUTTON_LIST;
	using KEY_LIST = ShunLib::KeyManager::KEY_CODE;

private:
	//キーが押されている
	//キーを離したら始動
	ShunLib::CommandInput<BUTTON_LIST, Player>m_padRelease;
	ShunLib::CommandInput<KEY_LIST, Player>m_keyRelease;

	//チャージしたパワー
	float m_power;

public:
	PlayerChargeState() {}
	~PlayerChargeState() {}

	//開始処理
	void Enter(Player* player);

	//実行処理
	void Execute(Player* player);

	//終了処理
	void Exit(Player* player);
};