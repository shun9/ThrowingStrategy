//************************************************/
//* @file  :PlayerMoveState.cpp
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayerMoveState.h"
#include "../Player.h"
#include "../../../Main/SL_MyStepTimer.h"
#include <SL_KeyManager.h>

void PlayerMoveState::Enter(Player* player)
{

}

void PlayerMoveState::Execute(Player* player)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();
	auto key = ShunLib::KeyManager::GetInstance();

	using KEY_CODE = ShunLib::KeyManager::KEY_CODE;

	//���x�̕ύX
	//�e�X�g�p�̉��̏���
	auto v = player->Velocity();
	if (key->IsPushed(KEY_CODE::S))
	{
		v.m_z += player->Spd();
	}
	if (key->IsPushed(KEY_CODE::W))
	{
		v.m_z -= player->Spd();
	}
	if (key->IsPushed(KEY_CODE::A))
	{
		v.m_x -= player->Spd();
	}
	if (key->IsPushed(KEY_CODE::D))
	{
		v.m_x += player->Spd();
	}

	//���x��ݒ肵�Ĉړ�
	player->Velocity(v);
	player->Move();
}

void PlayerMoveState::Exit(Player* player)
{

}
