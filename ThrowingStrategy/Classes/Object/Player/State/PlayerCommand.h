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

class PlayerPickUpCommand :public ShunLib::Command<Player>
{
public:
	PlayerPickUpCommand() {}
	~PlayerPickUpCommand() {}

	void Execute(Player* obj);

};

class PlayerPutCommand :public ShunLib::Command<Player>
{
public:
	PlayerPutCommand() {}
	~PlayerPutCommand() {}

	void Execute(Player* obj);
};

class PlayerThrowCommand :public ShunLib::Command<Player>
{
public:
	PlayerThrowCommand() {}
	~PlayerThrowCommand() {}

	void Execute(Player* obj);
};