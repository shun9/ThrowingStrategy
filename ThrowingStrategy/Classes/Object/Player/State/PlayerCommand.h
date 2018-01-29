//************************************************/
//* @file  :PlayerCommand.h
//* @brief :プレイヤーのコマンドまとめ
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
/// ユニットを拾う
/// </summary>
class PlayerPickUpCommand :public ShunLib::Command<Player>
{
public:
	PlayerPickUpCommand() {}
	~PlayerPickUpCommand() {}

	void Execute(Player* obj);

};

/// <summary>
/// ユニットを置く
/// </summary>
class PlayerPutCommand :public ShunLib::Command<Player>
{
public:
	PlayerPutCommand() {}
	~PlayerPutCommand() {}

	void Execute(Player* obj);
};

/// <summary>
/// ユニットを投げる
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
/// ユニットを拾う
/// </summary>
class PlayerChangeMoveStateCommand :public ShunLib::Command<Player>
{
public:
	PlayerChangeMoveStateCommand() {}
	~PlayerChangeMoveStateCommand() {}

	void Execute(Player* obj);

};
