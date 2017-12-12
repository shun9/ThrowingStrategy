//************************************************/
//* @file  :SummonerSteadyState.h
//* @brief :��������I�u�W�F�N�g�̑ҋ@���
//* @date  :2017/11/28
//* @author:S.Katou
//************************************************/
#include "SummonerSteadyState.h"
#include "SummonerSummonState.h"

void SummonerSteadyState::Enter(UnitSummoner * summoner)
{
	//���Ԑݒ�@���݂͓K���Ȓl
	m_timer.SetTime(300);
}

void SummonerSteadyState::Execute(UnitSummoner * summoner)
{
	//�^�C�}�[�̍X�V
	m_timer.Update();

	//���Ԃ������珢������
	if (m_timer.IsEnded()){
		summoner->ChangeState(new SummonerSummonState);
	}
}

void SummonerSteadyState::Exit(UnitSummoner * summoner)
{
	m_timer.ResetCount();
}
