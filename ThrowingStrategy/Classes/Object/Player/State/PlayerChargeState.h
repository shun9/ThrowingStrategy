//************************************************/
//* @file  :PlayerChargeState.h
//* @brief :�v���C���[�̈ړ����
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
	//�L�[��������Ă���
	//�L�[�𗣂�����n��
	ShunLib::CommandInput<BUTTON_LIST, Player>m_padRelease;
	ShunLib::CommandInput<KEY_LIST, Player>m_keyRelease;

	//�`���[�W�����p���[
	float m_power;

public:
	PlayerChargeState() {}
	~PlayerChargeState() {}

	//�J�n����
	void Enter(Player* player);

	//���s����
	void Execute(Player* player);

	//�I������
	void Exit(Player* player);
};