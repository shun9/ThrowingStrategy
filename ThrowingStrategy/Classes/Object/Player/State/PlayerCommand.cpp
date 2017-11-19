//************************************************/
//* @file  :PlayerCommand.cpp
//* @brief :�v���C���[�̃R�}���h�܂Ƃ�
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "PlayerCommand.h"
#include "../Player.h"

#include <cmath>
#include <complex>
#include <SL_Conversion.h>
#include "../../Unit/Unit.h"
#include "../../ObjectStruct.h"

void PlayerPickUpCommand::Execute(Player * player)
{
	auto hitList = player->Collider()->HitList();

	for (auto& v : hitList)
	{
		//�G�`�[���͎��ĂȂ�
		if (v->Team() != player->Team()){
			continue;
		}

		//���Ɏ����Ă��郆�j�b�g�͑ΏۊO
		if (player->HasChild(v)){
			continue;
		}

		//���j�b�g�ȊO�͎��ĂȂ�
		if (v->Type() == OBJECT_LIST::UNIT){
			player->AddChild(v);
			dynamic_cast<Unit*>(v)->ToBeLifted();
			break;
		}
	}
}

void PlayerPutCommand::Execute(Player * player)
{
	//���j�b�g���������Ă�����u��
	ObjectBase* child;
	if (player->HasChild(UNIT,&child))
	{
		player->RemoveChild(child);
		ObjectBase::ROOT_OBJECT->AddChild(child);
	}
}

void PlayerThrowCommand::Execute(Player * player)
{
	using namespace std;

	ObjectBase* child;
	if (player->HasChild(OBJECT_LIST::UNIT, &child))
	{
		player->RemoveChild(child);
		ObjectBase::ROOT_OBJECT->AddChild(child);

		//(x , z)
		complex<float> v(0.0f, 1.0f);

		//�v���C���[�̌����Ă�������ɗ͂�������
		v *= std::exp(complex<float>(0.0f,ShunLib::ToRadian(player->Rotation().m_y)));
		
		//������
		FlyingData data;
		data.start = child->WorldPos();
		data.end = ShunLib::Vec3(v.real(), child->Velocity().m_y, v.imag())*player->Power();
		data.power = player->Power();
		data.type = THROW_TYPE::LINE;
		dynamic_cast<Unit*>(child)->ToBeThrow(data);
	}
}
