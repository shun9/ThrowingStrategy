//************************************************/
//* @file  :PlayerChargeState.cpp
//* @brief :�v���C���[�̈ړ����
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
/// ������
/// </summary>
void PlayerChargeState::Enter(Player * player)
{
	m_power = 0.0f;

	//�p���[�Q�[�W��\������
	player->GetPowerGauge()->IsEnable(true);

	//�ړ����̕����̕ύX�𖳌�
	player->Data().ShouldChangeDir(false);

	//�L�[�𗣂����Ƃ��ɃR�}���h���s
	//���̏�Ԃɂ̓L�[��������Ă����Ԃœ����Ă���
	m_keyRelease.SetCommand(KEY_LIST::C, new PlayerThrowCommand);

	//�ړ��L�[
	m_keyInput.SetCommand(KEY_LIST::UP, new PlayerMoveUpKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::DOWN, new PlayerMoveDownKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::LEFT, new PlayerMoveLeftKeyCommand);
	m_keyInput.SetCommand(KEY_LIST::RIGHT, new PlayerMoveRightKeyCommand);
}

/// <summary>
/// ���s
/// </summary>
void PlayerChargeState::Execute(Player * player)
{
	//�L�[�֘A
	auto key = ShunLib::KeyManager::GetInstance();

	//�����Ă�Ԉړ�
	for (auto& v : m_keyInput.GetKeyList()) {
		if (key->IsPushed(v)) {
			m_keyInput.HandleInput(v)->Execute(player);
		}
	}

	//�ړ�
	player->Move();

	//�p���[���`���[�W���Ă���
	//�v���C���[�̌��E�l�𒴂��Ȃ��悤�ɂ���
	m_power = ShunLib::Min((m_power + 0.05f), player->Data().Power());
	player->GetPowerGauge()->Power(m_power);

	//�v���C���[�̌����Ă�������ɗ͂�������
	float rad = ToRadian(player->Transform().Rotation().m_y);

	//���e�n�_
	Vec3 pos = player->WorldPos() + (Vec3(-sin(rad), 0.0f, cos(rad)).Normalize()*m_power);
	m_throwCursor.Pos(pos);

	for (auto& v: m_keyRelease.GetKeyList()){
		//������Ă��Ȃ���Ύ��s
		//���̏�Ԃɂ̓L�[��������Ă����Ԃœ����Ă���
		if (!key->IsPushed(v)){
			//������Ƃ��̓p���[��ݒ�
			auto command = dynamic_cast<PlayerThrowCommand*>(m_keyRelease.HandleInput(v));
			if (command != nullptr) {
				command->SetEndPoint(pos);
				command->SetPower(m_power);
			}

			//�R�}���h���s
			m_keyRelease.HandleInput(v)->Execute(player);
		}
	}
}

/// <summary>
/// �I��
/// </summary>
void PlayerChargeState::Exit(Player * player)
{
	//�ړ����̕����̕ύX�𖳌�
	player->Data().ShouldChangeDir(true);

	//�p���[�Q�[�W���\��
	player->GetPowerGauge()->Power(0.0f);
	player->GetPowerGauge()->IsEnable(false);
}
