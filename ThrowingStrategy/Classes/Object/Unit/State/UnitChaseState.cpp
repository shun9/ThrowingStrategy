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
	//���j�b�g����ł��߂��I�u�W�F�N�g
	auto target = SearchTarget(unit);

	//�����������Ă��Ȃ����
	//��Ԃ�؂�ւ���
	if (target == nullptr){
		unit->ChangeState(new UnitRoamState);
		return;
	}

	//���j�b�g����^�[�Q�b�g�֌������x�N�g��
	Vec3 dir = target->WorldPos() - unit->WorldPos();
	dir.Normalize();

	//���j�b�g�̑��x��ݒ�@�ړ�
	unit->Transform().Velocity(dir * unit->Data().Spd());
	unit->Move();

	//�U���͈͓��ɂ���ʃ`�[���̃I�u�W�F�N�g��T��
	SearchTeamVisitor tV(unit->Data().Team());
	tV.VisitAnotherTeam();
	unit->AttackRange()->Accept(&tV);

	//�U���͈͂ɕʃ`�[���̃I�u�W�F�N�g��������U����ԂɈڍs
	if (tV.Count() > 0){
		unit->ChangeState(new UnitAttackState);
		return;
	}
}

void UnitChaseState::Exit(Unit * unit)
{

}

/// <summary>
/// ���j�b�g����ł��߂��G�`�[���I�u�W�F�N�g��T��
/// </summary>
/// <param name="unit">���j�b�g</param>
/// <returns>�G�`�[���I�u�W�F�N�g</returns>
ObjectBase* UnitChaseState::SearchTarget(Unit * unit)
{
	//�������Ă���I�u�W�F�N�g����
	//�ʂ̃`�[���̃I�u�W�F�N�g��T��
	SearchTeamVisitor tV(unit->Data().Team());
	tV.VisitAnotherTeam();
	unit->ChaseRange()->Accept(&tV);

	//�ʃ`�[���̃I�u�W�F�N�g����
	//�ł��߂��ɂ���I�u�W�F�N�g��T��
	Vec3 unitPos = unit->WorldPos();
	SearchNearestObjectVisitor nV(unitPos);
	tV.Accept(&nV);

	return nV.Object();
}
