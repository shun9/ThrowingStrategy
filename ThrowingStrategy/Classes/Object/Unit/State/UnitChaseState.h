//************************************************/
//* @file  :UnitChaseState.h
//* @brief :�������j�b�g�̒ǐՏ��
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>

class Unit;

class UnitChaseState : public ShunLib::State<Unit>
{
public:
	UnitChaseState() {}
	~UnitChaseState() {}

	//�J�n����
	void Enter(Unit* unit);

	//���s����
	void Execute(Unit* unit);

	//�I������
	void Exit(Unit* unit);
};