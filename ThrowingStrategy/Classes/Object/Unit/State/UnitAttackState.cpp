//************************************************/
//* @file  :UnitAttackState.cpp
//* @brief :��������郆�j�b�g�̍U�����
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "UnitAttackState.h"
#include "UnitChaseState.h"

#include <cmath>
#include <SL_Conversion.h>
#include "../../../Util/Visitor/Visitor.h"

using namespace ShunLib;

void UnitAttackState::Enter(Unit* unit)
{
	SearchStateObjectVisitor sV;
	SearchAnotherTeamVisitor aV(unit->Team());
	unit->AttackRange()->Accept(&sV);
	sV.Accept(&aV);

	//�������Ă���I�u�W�F�N�g�����݂���Ȃ��
	//�^�[�Q�b�g�ɐݒ�
	if (aV.Count() > 0) {
		m_target = aV.List()[0];
	}

	m_intervalTimer.SetTime(60);
}

void UnitAttackState::Execute(Unit* unit)
{
	//�^�[�Q�b�g��������Ή������Ȃ�
	if (m_target == nullptr){
		unit->ChangeState(new UnitChaseState);
		return;
	}

	//�^�C�}�[�X�V
	m_intervalTimer.Update();

	//���j�b�g����^�[�Q�b�g�֌������x�N�g��
	Vec3 dir = m_target->Pos() - unit->Pos();
	
	//�U���͈͂���O�ꂽ��߂�
	SearchSpecificObjectVisitor v(m_target);
	unit->AttackRange()->Accept(&v);
	if (!v.IsFound()){
		unit->ChangeState(new UnitChaseState);
		return;
	}

	//X,Z�̓񎟌��Ō�������
	//���グ����A�������邱�Ƃ͂Ȃ�
	dir.m_y = 0.0f;
	float rot = ToAngle(std::atan2(dir.m_z, dir.m_x)) - 90.0f;

	//���j�b�g�̌�����ς���
	Vec3 uRot = unit->Rotation();
	uRot.m_y = rot;
	unit->Rotation(uRot);

	//���Ԋu�Ń^�[�Q�b�g�ɍU��
	if (m_intervalTimer.IsEnded()){
		m_intervalTimer.ResetCount();
		m_target->TakeDamage((int)(unit->Power()));
	}
}

void UnitAttackState::Exit(Unit* unit)
{

}
