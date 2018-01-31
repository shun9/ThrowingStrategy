//************************************************/
//* @file  :PlayerCommand.cpp
//* @brief :�v���C���[�̃R�}���h�܂Ƃ�
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "PlayerCommand.h"
#include <cmath>

#include <SL_Conversion.h>
#include <SL_ObjectHolder.h>
#include "PlayerState.h"
#include "../Player.h"
#include "../../Unit/Unit.h"
#include "../../ObjectStruct.h"
#include "../../../Util/Visitor/Visitor.h"

using namespace std;
using namespace ShunLib;

/// <summary>
/// �E��
/// </summary>
void PlayerPickUpCommand::Execute(Player * player)
{
	//�����`�[����T��
	SearchTeamVisitor tV(player->Data().Team());
	tV.VisitSameTeam();
	player->Collider()->Accept(&tV);

	//���j�b�g��T��
	SearchUnitVisitor visitor;
	tV.Accept(&visitor);
	auto hitList = visitor.List();

	//���Ă邩�ǂ���
	for (auto& v : hitList){
		//���Ɏ����Ă��郆�j�b�g�͑ΏۊO
		SearchSpecificObjectVisitor sv(v);
		player->Accept(&sv);
		if (sv.IsFound()){
			continue;
		}

		player->AddChild(v);
		v->ToBeLifted();
		player->AlignUnits();
		return;
	}
}


/// <summary>
/// �u��
/// </summary>
void PlayerPutCommand::Execute(Player * player)
{
	SearchUnitVisitor unitV;
	player->Accept(&unitV);

	//���j�b�g���������Ă�����u��
	if (unitV.Count() > 0)
	{
		//�擪�̃��j�b�g��ΏۂƂ���
		Unit* child = unitV.List()[0];

		//�v���C���[�̌����Ă������
		float rad = ToRadian(player->Transform().Rotation().m_y);

		Vec3 pos = player->Transform().Pos() + Vec3(-sin(rad), 0.0f, cos(rad))*player->Transform().Scale().Length();

		player->RemoveChild(child);
		child->SetParent(ShunLib::ObjectHolder::GetInstance()->List(ObjectConstantNumber::STAGE)[0]);
		child->LocalPos(pos);
		child->ToBePlaced();
		player->AlignUnits();
	}
}


/// <summary>
/// ������
/// </summary>
void PlayerThrowCommand::Execute(Player* player)
{
	Unit* child;
	SearchUnitVisitor v;
	player->Accept(&v);

	if (v.Count() > 0)
	{
		child = v.List()[0];

		//�e�q�֌W������
		//�X�e�[�W�ɕt������
		auto list = ObjectHolder::GetInstance()->List(ObjectConstantNumber::STAGE);

		//�X�e�[�W�͕K���P����
		assert(list.size() == 1);

		child->SetParent(list[0]);
		//�v���C���[�̌����Ă�������ɗ͂�������
		float rad = ToRadian(player->Transform().Rotation().m_y);

		//������
		FlyingData data;
		m_flyData.start = child->WorldPos();
		m_flyData.type = ObjectConstantNumber::THROW_TYPE::LINE;
		child->ToBeThrow(m_flyData);

		player->AlignUnits();

		player->ChangeState(new PlayerMoveState);
	}
}

/// <summary>
/// �v���C���[��͂����߂��Ԃɐ؂�ւ���
/// </summary>
void PlayerChangeMoveStateCommand::Execute(Player * obj)
{
	//���j�b�g�������Ă�����؂�ւ���
	if (obj->HavingUnitNum() > 0)
	{
		obj->ChangeState(new PlayerChargeState);
	}
}
