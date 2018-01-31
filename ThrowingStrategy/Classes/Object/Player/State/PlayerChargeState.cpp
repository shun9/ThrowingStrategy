//************************************************/
//* @file  :PlayerChargeState.cpp
//* @brief :プレイヤーの移動状態
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "PlayerChargeState.h"

#include <SL_Math.h>
#include <SL_Conversion.h>
#include <SL_KeyManager.h>
#include "PlayerCommand.h"
#include "PlayerKeyCommand.h"
#include "../Player.h"
#include "../../../UI/PowerGauge/PowerGauge.h"
#include "../../../Util/Debugger/DebuggerUI.h"

using namespace ShunLib;

/// <summary>
/// 初期化
/// </summary>
void PlayerChargeState::Enter(Player * player)
{
	m_power = 0.0f;

	//パワーゲージを表示する
	player->GetPowerGauge()->IsEnable(true);

	//移動中の方向の変更を無効
	player->Data().ShouldChangeDir(false);

	//キーを離したときにコマンド実行
	//この状態にはキーが押されている状態で入ってくる
	m_keyRelease.SetCommand(KEY_LIST::C, new PlayerThrowCommand);

	//移動キー
	m_keyInput.SetCommand(KEY_LIST::UP, new PlayerMoveUpKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::DOWN, new PlayerMoveDownKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::LEFT, new PlayerMoveLeftKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::RIGHT, new PlayerMoveRightKeyCommand);
}

/// <summary>
/// 実行
/// </summary>
void PlayerChargeState::Execute(Player * player)
{
	//キー関連
	auto key = ShunLib::KeyManager::GetInstance();

	//押してる間移動
	for (auto& v : m_keyInput.GetKeyList()) {
		if (key->IsPushed(v)) {
			m_keyInput.HandleInput(v)->Execute(player);
		}
	}

	//移動
	player->Move();

	//パワーをチャージしていく
	//プレイヤーの限界値を超えないようにする
	m_power = ShunLib::Min((m_power + 0.05f), player->Data().Power());
	player->GetPowerGauge()->Power(m_power);

	//プレイヤーの向いている方向に力を加える
	float rad = ToRadian(player->Transform().Rotation().m_y);

	//着弾地点
	Vec3 pos = player->WorldPos() + (Vec3(-sin(rad), 0.0f, cos(rad)).Normalize()*m_power);
	m_throwCursor.Pos(pos);

	for (auto& v: m_keyRelease.GetKeyList()){
		//押されていなければ実行
		//この状態にはキーが押されている状態で入ってくる
		if (!key->IsPushed(v)){
			//投げるときはパワーを設定
			auto command = dynamic_cast<PlayerThrowCommand*>(m_keyRelease.HandleInput(v));
			if (command != nullptr) {
				command->SetEndPoint(pos);
				command->SetPower(m_power);
			}

			//コマンド実行
			m_keyRelease.HandleInput(v)->Execute(player);
		}
	}
}

/// <summary>
/// 終了
/// </summary>
void PlayerChargeState::Exit(Player * player)
{
	//移動中の方向の変更を無効
	player->Data().ShouldChangeDir(true);

	//パワーゲージを非表示
	player->GetPowerGauge()->Power(0.0f);
	player->GetPowerGauge()->IsEnable(false);
}
