//************************************************/
//* @file  :SummonerSteadyState.h
//* @brief :��������I�u�W�F�N�g�̑ҋ@���
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_Timer.h>
#include "../UnitSummoner.h"

class SummonerSteadyState : public ShunLib::State<UnitSummoner>
{
private:
	ShunLib::Timer m_timer;

public:
	SummonerSteadyState() {}
	~SummonerSteadyState() {}

	//�J�n����
	void Enter(UnitSummoner* summoner);

	//���s����
	void Execute(UnitSummoner* summoner);

	//�I������
	void Exit(UnitSummoner* summoner);
};