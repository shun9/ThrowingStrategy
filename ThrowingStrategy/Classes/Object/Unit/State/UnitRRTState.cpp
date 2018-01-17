//************************************************/
//* @file  :UnitRRTState.cpp
//* @brief :���j�b�g��RRT�œ������Ă݂�
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#include "UnitRRTState.h"
#include <SL_ObjectHolder.h>
#include "../../../Util/Visitor/Visitor.h"
#include "../../../Main/SL_MyStepTimer.h"

using namespace ShunLib;

void UnitRRTState::Enter(Unit * unit)
{
	m_timeCnt = 0.0f;
	m_routeUpdateInterval = 10.0f;

	//���[�g�X�V
	UpdateRoute(unit);
}

void UnitRRTState::Execute(Unit * unit)
{
	//���Ԃ��v��
	auto timer = MyStepTimer::GetInstance();
	m_timeCnt += timer->GetElapsedSeconds();

	//��莞�Ԃ��ƂɃ��[�g���X�V
	if (m_timeCnt > m_routeUpdateInterval) {

		//���[�g�X�V
		UpdateRoute(unit);

		m_timeCnt = 0.0f;
	}

	//���x�ݒ� �ړ�
	unit->Transform().Velocity(m_route[m_routeIndex] * unit->Data().Spd());
	unit->Move();
	m_routeIndex++;
}

void UnitRRTState::Exit(Unit * unit)
{

}

/// <summary>
/// ���[�g�̍X�V
/// </summary>
void UnitRRTState::UpdateRoute(Unit* unit)
{
	auto objHolder = ObjectHolder::GetInstance();

	//�G�̖h�q�Ώۂ��^�[�Q�b�g�ɐݒ�
	SearchTeamVisitor st(unit->Data().Team());
	st.VisitAnotherTeam();
	objHolder->Accept(ObjectConstantNumber::DEFENSE_TARGET, &st);

	//���[�g����
	RRT rrt(unit->Transform().Pos(), st.List()[0]->Transform().Pos(), unit->Data().Spd()*60);
	rrt.Is2D(true);
	rrt.CreateRoute();

	//���[�g�擾
	m_route = rrt.GetRoute();

	m_routeIndex = 0;
}
