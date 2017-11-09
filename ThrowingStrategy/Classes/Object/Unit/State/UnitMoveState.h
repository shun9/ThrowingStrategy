//************************************************/
//* @file  :UnitMoveState.h
//* @brief :��������郆�j�b�g�̈ړ����
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"

class UnitMoveState : public ShunLib::State<Unit>
{
public:
	UnitMoveState() {}
	~UnitMoveState() {}

	//�J�n����
	void Enter(Unit* obj);

	//���s����
	void Execute(Unit* obj);

	//�I������
	void Exit(Unit* obj);

};