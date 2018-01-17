//************************************************/
//* @file  :UnitRRTState.h
//* @brief :���j�b�g��RRT�œ������Ă݂�
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_Timer.h>
#include "../Unit.h"
#include "../../../AI/RRT.h"

class UnitRRTState : public ShunLib::State<Unit>
{
private:
	RRT::Route m_route;
	int m_routeIndex;
	float m_timeCnt;
	float m_routeUpdateInterval;

public:
	UnitRRTState(){}
	~UnitRRTState() {}

	//�J�n����
	void Enter(Unit* unit);

	//���s����
	void Execute(Unit* unit);

	//�I������
	void Exit(Unit* unit);

private:
	//���[�g�X�V
	void UpdateRoute(Unit* unit);
};
