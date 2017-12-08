//************************************************/
//* @file  :UnitChaseState.cpp
//* @brief :�������j�b�g�̒ǐՏ��
//* @date  :2017/12/04
//* @author:S.Katou
//************************************************/
#include "UnitChaseState.h"
#include "UnitAttackState.h"
#include "UnitRoamState.h"

#include "../Unit.h"

#include "../../../Util/Visitor/Visitor.h"

void UnitChaseState::Enter(Unit * unit)
{

}

void UnitChaseState::Execute(Unit* unit)
{
	//�������Ă���I�u�W�F�N�g����
	//�ʂ̃`�[���̃I�u�W�F�N�g��T��
	SearchAnotherTeamVisitor aV(unit->Team());
	unit->ChaseRange()->Accept(&aV);

	//�ʃ`�[���̃I�u�W�F�N�g����
	//�ł��߂��ɂ���I�u�W�F�N�g��T��
	Vec3 unitPos = unit->WorldPos();
	SearchNearestObjectVisitor nV(unitPos);
	aV.Accept(&nV);
	auto target = nV.Object();

	//�����������Ă��Ȃ����
	//��Ԃ�؂�ւ���
	if (target == nullptr){
		unit->ChangeState(new UnitRoamState);
		return;
	}
	
	Vec3 dir = target->WorldPos() - unitPos;
	dir.Normalize();

	unit->Velocity(dir * unit->Spd());

	unit->Move();

	aV.Reset();
	unit->AttackRange()->Accept(&aV);

	if (aV.Count() > 0){
		unit->ChangeState(new UnitAttackState);
		return;
	}
}

void UnitChaseState::Exit(Unit * unit)
{

}
