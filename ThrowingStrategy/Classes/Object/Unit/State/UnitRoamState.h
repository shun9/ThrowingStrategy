//************************************************/
//* @file  :UnitRoamState.h
//* @brief :��������郆�j�b�g�̂�������
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"

class UnitRoamState : public ShunLib::State<Unit>
{
private:
	float m_timeCnt;
	float m_limit;

	ShunLib::Vec3 m_direction;

public:
	UnitRoamState():
		m_timeCnt(0.0f),
		m_limit(3.0f){}
	~UnitRoamState() {}

	//�J�n����
	void Enter(Unit* obj);

	//���s����
	void Execute(Unit* obj);

	//�I������
	void Exit(Unit* obj);

private:
	void ChangeDirection();
};