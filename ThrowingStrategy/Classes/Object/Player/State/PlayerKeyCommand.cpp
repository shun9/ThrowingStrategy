//************************************************/
//* @file  :PlayerKeyCommand.cpp
//* @brief :�v���C���[�̃L�[�{�[�h�p�R�}���h�܂Ƃ�
//* @date  :2017/11/15
//* @author:S.Katou
//************************************************/
#include "PlayerKeyCommand.h"
#include "../Player.h"

void PlayerMoveUpKeyCommand::Execute(Player * obj)
{
	auto v = obj->Velocity();
	v.m_z -= obj->Spd();
	obj->Velocity(v);
}

void PlayerMoveDownKeyCommand::Execute(Player * obj)
{
	auto v = obj->Velocity();
	v.m_z += obj->Spd();
	obj->Velocity(v);
}

void PlayerMoveRightKeyCommand::Execute(Player * obj)
{
	auto v = obj->Velocity();
	v.m_x += obj->Spd();
	obj->Velocity(v);
}

void PlayerMoveLeftKeyCommand::Execute(Player * obj)
{
	auto v = obj->Velocity();
	v.m_x -= obj->Spd();
	obj->Velocity(v);
}
