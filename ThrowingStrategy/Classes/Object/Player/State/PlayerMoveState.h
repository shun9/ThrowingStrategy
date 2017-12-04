//************************************************/
//* @file  :PlayerMoveState.h
//* @brief :�v���C���[�̈ړ����
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_CommandInput.h>
#include <SL_State.h>
#include <SL_KeyManager.h>
#include "../../../Util/SL_GamePadManager.h"

class Player;

class PlayerMoveState : public ShunLib::State<Player>
{
private:
	using BUTTON_LIST = ShunLib::GamePadManager::BUTTON_LIST;
	using KEY_LIST = ShunLib::KeyManager::KEY_CODE;

private:
	ShunLib::CommandInput<BUTTON_LIST, Player>m_padInput;
	ShunLib::CommandInput<KEY_LIST, Player>m_keyInput;
	ShunLib::CommandInput<KEY_LIST, Player>m_keyTriggerInput;

public:
	PlayerMoveState() {}
	~PlayerMoveState() {}

	//�J�n����
	void Enter(Player* player);

	//���s����
	void Execute(Player* player);

	//�I������
	void Exit(Player* player);

};