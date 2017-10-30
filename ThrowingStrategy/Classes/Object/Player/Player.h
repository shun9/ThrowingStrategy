//************************************************/
//* @file  :Player.h
//* @brief :プレイヤー
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"

class Player :public StateObject<Player>
{
public:
	Player():StateObject(this) {}
	~Player() {}

	////初期化　終了
	void Initialize()override;
	void Finalize()override;
};