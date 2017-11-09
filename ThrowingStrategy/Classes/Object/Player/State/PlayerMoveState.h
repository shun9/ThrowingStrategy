//************************************************/
//* @file  :PlayerMoveState.h
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
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
	//�J�n����
	void Enter(Player* player);

	//���s����
	void Execute(Player* player);

	//�I������
	void Exit(Player* player);

};