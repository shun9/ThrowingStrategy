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

using namespace ShunLib;

void UnitAttackState::Enter(Unit* unit)
{
	auto hitList = unit->AttackRange()->HitList();

	//�������Ă���I�u�W�F�N�g��������Ή������Ȃ�
	if (!hitList.empty()){
		m_target = hitList[0];
	}
}

void UnitAttackState::Execute(Unit* unit)
{
	//�^�[�Q�b�g��������Ή������Ȃ�
	if (m_target == nullptr){
		unit->ChangeState(new UnitRoamState);
	}

	//���j�b�g����^�[�Q�b�g�֌������x�N�g��
	Vec3 dir = m_target->Pos() - unit->Pos();
	
	//�U���͈͂���O�ꂽ��߂�
	if (dir.Length() > unit->AttackRange()->Shape()->Scale()){
		unit->ChangeState(new UnitRoamState);
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
