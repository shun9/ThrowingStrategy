//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[
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

	////�������@�I��
	void Initialize()override;
	void Finalize()override;
};