//************************************************/
//* @file  :PlayerMoveState.cpp
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "PlayerMoveState.h"
#include "../Player.h"
#include "../../../Main/SL_MyStepTimer.h"
#include "PlayerCommand.h"
#include "PlayerKeyCommand.h"


void PlayerMoveState::Enter(Player* player)
{
	m_padInput.SetCommand(BUTTON_LIST::X, new PlayerPickUpCommand);

	m_keyTriggerInput.SetCommand(KEY_LIST::Z, new PlayerPickUpCommand);
	m_keyTriggerInput.SetCommand(KEY_LIST::X, new PlayerPutCommand);
	m_keyTriggerInput.SetCommand(KEY_LIST::C, new PlayerThrowCommand);

	m_keyInput.SetCommand(KEY_LIST::UP, new PlayerMoveUpKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::DOWN, new PlayerMoveDownKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::LEFT, new PlayerMoveLeftKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::RIGHT, new PlayerMoveRightKeyCommand);
}

void PlayerMoveState::Execute(Player* player)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	//キー入力
	auto key = ShunLib::KeyManager::GetInstance();
	auto keyList = m_keyInput.GetKeyList();

	for (auto& v : keyList){
		if (key->IsPushed(v)){
			m_keyInput.HandleInput(v)->Execute(player);
		}
	}

	auto triggerList = m_keyTriggerInput.GetKeyList();
	for (auto& v : triggerList) {
		if (key->IsPushed(v)) {
			m_keyTriggerInput.HandleInput(v)->Execute(player);
		}
	}

	player->Move();
}

void PlayerMoveState::Exit(Player* player)
{

}
