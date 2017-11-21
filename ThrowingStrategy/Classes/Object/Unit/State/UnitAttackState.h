//************************************************/
//* @file  :UnitAttackState.h
//* @brief :��������郆�j�b�g�̍U�����
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../Unit.h"

class UnitAttackState : public ShunLib::State<Unit>
{
private:
	ObjectBase* m_target;

public:
	UnitAttackState():
		m_target(nullptr) {}
	~UnitAttackState() {}

	//�J�n����
	void Enter(Unit* unit);

	//���s����
	void Execute(Unit* unit);

	//�I������
	void Exit(Unit* unit);
};
