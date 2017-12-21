//************************************************/
//* @file  :PlayerCommand.cpp
//* @brief :�v���C���[�̃R�}���h�܂Ƃ�
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "PlayerCommand.h"
#include "../Player.h"

#include <cmath>
#include <SL_Conversion.h>
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
	//�Ⴄ�`�[����T��
	SearchAnotherTeamVisitor aV(player->Data().Team());
	player->Collider()->Accept(&aV);

	//�Ⴄ�`�[���̒����烆�j�b�g��T��
	SearchUnitVisitor visitor;
	aV.Accept(&visitor);
	auto hitList = visitor.List();

	//���Ă邩�ǂ���
	for (auto& v : hitList)
	{
		//���Ɏ����Ă��郆�j�b�g�͑ΏۊO
		SearchSpecificObjectVisitor sv(v);
		player->Accept(&sv);
		if (sv.IsFound()){
			continue;
		}

		player->AddChild(v);
		player->AlignUnits();
		v->ToBeLifted();
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
		ObjectBase* child = unitV.List()[0];

		//�v���C���[�̌����Ă������
		float rad = ToRadian(player->Transform().Rotation().m_y);

		Vec3 pos = player->Transform().Pos() + Vec3(-sin(rad), 0.0f, cos(rad))*player->Transform().Scale().Length();

		player->RemoveChild(child);
		child->LocalPos(pos);
		player->AlignUnits();
	}
}


/// <summary>
/// ������
/// </summary>
void PlayerThrowCommand::Execute(Player * player)
{
	Unit* child;
	SearchUnitVisitor v;
	player->Accept(&v);

	if (v.Count() > 0)
	{
		child = v.List()[0];

		player->RemoveChild(child);

		//�v���C���[�̌����Ă�������ɗ͂�������
		float rad = ToRadian(player->Transform().Rotation().m_y);

		//������
		FlyingData data;
		data.start = child->WorldPos();
		data.end = player->WorldPos() + (Vec3(-sin(rad), 0.0f, cos(rad)).Normalize() *player->Data().Power());
		data.power = player->Data().Power();
		data.type = ObjectConstantNumber::THROW_TYPE::LINE;
		child->ToBeThrow(data);

		player->AlignUnits();
	}
}
