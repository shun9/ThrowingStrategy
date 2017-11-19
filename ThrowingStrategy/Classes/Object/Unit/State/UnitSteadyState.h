//************************************************/
//* @file  :UnitSteadyState.h
//* @brief :��������郆�j�b�g�̓����Ȃ����
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../Unit.h"

class UnitSteadyState : public ShunLib::State<Unit>
{
public:
	UnitSteadyState() {}
	~UnitSteadyState() {}

	//�J�n����
	void Enter(Unit* obj);

	//���s����
	void Execute(Unit* obj);

	//�I������
	void Exit(Unit* obj);
};