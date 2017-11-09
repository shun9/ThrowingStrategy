//************************************************/
//* @file  :CommanderMoveState.h
//* @brief :�w�����̈ړ����
//* @date  :2017/10/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "Commander.h"

class CommanderMoveState :public ShunLib::State<Commander>
{
public:
	CommanderMoveState() {}
	~CommanderMoveState() {}

	//�J�n����
	void Enter(Commander* obj);

	//���s����
	void Execute(Commander* obj);

	//�I������
	void Exit(Commander* obj);
};
