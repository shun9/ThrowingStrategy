//************************************************/
//* @file  :PlayerChargeState.cpp
//* @brief :プレイヤーの移動状態
//* @date  :2018/01/25
//* @author:S.Katou
//************************************************/
#include "PlayerChargeState.h"

#include <SL_Math.h>
#include <SL_KeyManager.h>
#include "PlayerCommand.h"
#include "../Player.h"

void PlayerChargeState::Enter(Player * player)
{
	m_power = 0.0f;
	m_keyRelease.SetCommand(KEY_LIST::C, new PlayerThrowCommand);
}

void PlayerChargeState::Execute(Player * player)
{
	//パワーをチャージしていく
	//プレイヤーの限界値を超えないようにする
	m_power = ShunLib::Min((m_power + 0.1f), player->Data().Power());

	auto key = ShunLib::KeyManager::GetInstance();

	for (auto& v: m_keyRelease.GetKeyList()){
		//押されていなければ実行
		//この状態にはキーが押されている状態で入ってくる
		if (!key->IsPushed(v)){
			//投げるときはパワーを設定
			auto command = dynamic_cast<PlayerThrowCommand*>(m_keyRelease.HandleInput(v));
			if (command != nullptr) {
				command->SetPower(m_power);
			}

			//コマンド実行
			m_keyRelease.HandleInput(v)->Execute(player);
		}
	}
}

void PlayerChargeState::Exit(Player * player)
{

}
