//************************************************/
//* @file  :PlayerCommand.h
//* @brief :�v���C���[�̃R�}���h�܂Ƃ�
//* @date  :2017/11/15
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Command.h>

class Player;
class PlayerMoveCommand :public ShunLib::Command<Player>
{
public:
	PlayerMoveCommand() {}
	~PlayerMoveCommand(){}

	void Execute(Player* obj);

};

/// <summary>
/// ���j�b�g���E��
/// </summary>
class PlayerPickUpCommand :public ShunLib::Command<Player>
{
public:
	PlayerPickUpCommand() {}
	~PlayerPickUpCommand() {}

	void Execute(Player* obj);

};

/// <summary>
/// ���j�b�g��u��
/// </summary>
class PlayerPutCommand :public ShunLib::Command<Player>
{
public:
	PlayerPutCommand() {}
	~PlayerPutCommand() {}

	void Execute(Player* obj);
};

/// <summary>
/// ���j�b�g�𓊂���
/// </summary>
class PlayerThrowCommand :public ShunLib::Command<Player>
{
private:
	float m_power;

public:
	PlayerThrowCommand():m_power(0.0f){}
	~PlayerThrowCommand() {}

	void Execute(Player* obj);

	void SetPower(float power) { m_power = power; }
};

/// <summary>
/// ���j�b�g���E��
/// </summary>
class PlayerChangeMoveStateCommand :public ShunLib::Command<Player>
{
public:
	PlayerChangeMoveStateCommand() {}
	~PlayerChangeMoveStateCommand() {}

	void Execute(Player* obj);

};
