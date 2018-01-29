//************************************************/
//* @file  :PlayerChargeState.cpp
//* @brief :�v���C���[�̈ړ����
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
	//�p���[���`���[�W���Ă���
	//�v���C���[�̌��E�l�𒴂��Ȃ��悤�ɂ���
	m_power = ShunLib::Min((m_power + 0.1f), player->Data().Power());

	auto key = ShunLib::KeyManager::GetInstance();

	for (auto& v: m_keyRelease.GetKeyList()){
		//������Ă��Ȃ���Ύ��s
		//���̏�Ԃɂ̓L�[��������Ă����Ԃœ����Ă���
		if (!key->IsPushed(v)){
			//������Ƃ��̓p���[��ݒ�
			auto command = dynamic_cast<PlayerThrowCommand*>(m_keyRelease.HandleInput(v));
			if (command != nullptr) {
				command->SetPower(m_power);
			}

			//�R�}���h���s
			m_keyRelease.HandleInput(v)->Execute(player);
		}
	}
}

void PlayerChargeState::Exit(Player * player)
{

}
