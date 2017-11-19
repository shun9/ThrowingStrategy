//************************************************/
//* @file  :PlayerKeyCommand.h
//* @brief :プレイヤーのキーボード用コマンドまとめ
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Command.h>

class Player;

class PlayerMoveUpKeyCommand :public ShunLib::Command<Player>
{
public:
	PlayerMoveUpKeyCommand() {}
	~PlayerMoveUpKeyCommand() {}

	void Execute(Player* obj);
};

class PlayerMoveDownKeyCommand :public ShunLib::Command<Player>
{
public:
	PlayerMoveDownKeyCommand() {}
	~PlayerMoveDownKeyCommand() {}

	void Execute(Player* obj);
};

class PlayerMoveRightKeyCommand :public ShunLib::Command<Player>
{
public:
	PlayerMoveRightKeyCommand() {}
	~PlayerMoveRightKeyCommand() {}

	void Execute(Player* obj);
};

class PlayerMoveLeftKeyCommand :public ShunLib::Command<Player>
{
public:
	PlayerMoveLeftKeyCommand() {}
	~PlayerMoveLeftKeyCommand() {}

	void Execute(Player* obj);
};
