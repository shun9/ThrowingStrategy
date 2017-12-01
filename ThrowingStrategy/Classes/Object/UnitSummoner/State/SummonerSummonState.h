//************************************************/
//* @file  :SummonerSummonState.h
//* @brief :��������I�u�W�F�N�g�̏��������
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "../UnitSummoner.h"

class SummonerSummonState : public ShunLib::State<UnitSummoner>
{
public:
	SummonerSummonState() {}
	~SummonerSummonState() {}

	//�J�n����
	void Enter(UnitSummoner* summoner);

	//���s����
	void Execute(UnitSummoner* summoner);

	//�I������
	void Exit(UnitSummoner* summoner);
};