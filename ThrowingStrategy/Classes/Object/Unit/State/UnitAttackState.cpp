//************************************************/
//* @file  :UnitAttackState.cpp
//* @brief :��������郆�j�b�g�̍U�����
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "UnitAttackState.h"
#include "UnitRoamState.h"

#include <cmath>
#include <SL_Conversion.h>
#include "../../../Util/Visitor/Visitor.h"

using namespace ShunLib;

void UnitAttackState::Enter(Unit* unit)
{
	SearchStateObjectVisitor v;
	unit->AttackRange()->Accept(&v);

	//�������Ă���I�u�W�F�N�g�����݂���Ȃ��
	//�^�[�Q�b�g�ɐݒ�
	if (v.Count() > 0) {
		m_target = v.List()[0];
	}
}

void UnitAttackState::Execute(Unit* unit)
{
	//�^�[�Q�b�g��������Ή������Ȃ�
	if (m_target == nullptr){
		unit->ChangeState(new UnitRoamState);
		return;
	}

	//���j�b�g����^�[�Q�b�g�֌������x�N�g��
	Vec3 dir = m_target->Pos() - unit->Pos();
	
	//�U���͈͂���O�ꂽ��߂�
	SearchSpecificObjectVisitor v(m_target);
	unit->AttackRange()->Accept(&v);
	if (!v.IsFound()){
		unit->ChangeState(new UnitRoamState);
		return;
	}

	//X,Z�̓񎟌��Ō�������
	//���グ����A�������邱�Ƃ͂Ȃ�
	dir.m_y = 0.0f;

	float rot = ToAngle(std::atan2(dir.m_z, dir.m_x)) - 90.0f;

	Vec3 uRot = unit->Rotation();
	uRot.m_y = rot;
	unit->Rotation(uRot);
}

void UnitAttackState::Exit(Unit* unit)
{

}