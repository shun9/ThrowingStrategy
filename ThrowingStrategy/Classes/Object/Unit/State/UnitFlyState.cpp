//************************************************/
//* @file  :UnitFlyState.cpp
//* @brief :���j�b�g�̔�ԏ��
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "UnitFlyState.h"

#include <SL_Lerp.h>
#include "UnitRoamState.h"
#include "../../../Main/SL_MyStepTimer.h"

using namespace ShunLib;

void UnitFlyState::Enter(Unit * unit)
{
	//1�b������1�i�ސݒ�
	m_timeLimit = (m_data.start - m_data.end).Length();
	m_timeCnt = 0.0f;

	//���������ݒ肳��Ă��Ȃ��ꍇ
	if (m_data.Lerp() == NULL) { m_data.type = ObjectConstantNumber::THROW_TYPE::LINE; }
}

void UnitFlyState::Execute(Unit * unit)
{
	//��Ԃɂ���Ĉʒu���o��
	Vec3 v = Vec3::Larp(m_data.start, m_data.end, m_timeCnt / m_timeLimit, m_data.Lerp());
	unit->Transform().Pos(v);

	//���Ԃ��J�E���g
	//�p���[�̕����������i�߂�
	m_timeCnt += MyStepTimer::GetInstance()->GetElapsedSeconds() * m_data.power;

	//�ړ������������Ԑؑ�
	if (m_timeCnt > m_timeLimit){
		unit->ChangeState(new UnitRoamState);
	}
}

void UnitFlyState::Exit(Unit * unit)
{
}
