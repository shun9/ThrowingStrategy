//************************************************/
//* @file  :PlayerCommand.cpp
//* @brief :プレイヤーのコマンドまとめ
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
/// 拾う
/// </summary>
void PlayerPickUpCommand::Execute(Player * player)
{
	SearchUnitVisitor visitor;
	player->Collider()->Accept(&visitor);
	auto hitList = visitor.List();

	for (auto& v : hitList)
	{
		//敵チームは持てない
		if (v->Team() != player->Team()){
			continue;
		}

		//既に持っているユニットは対象外
		if (player->HasChild(v)){
			continue;
		}

		//ユニット以外は持てない
		if (v->Type() == OBJECT_LIST::UNIT){
			player->AddChild(v);
			//v->LocalPos(Vec3(0.0f,2.0f*(player->HavingUnitNum()+1.0f),0.0f));
			player->AlignUnits();
			v->ToBeLifted();
			return;
		}
	}
}


/// <summary>
/// 置く
/// </summary>
void PlayerPutCommand::Execute(Player * player)
{
	//ユニットを所持していたら置く
	ObjectBase* child;
	if (player->HasChild(UNIT,&child))
	{		
		//プレイヤーの向いている方向
		float rad = ToRadian(player->Rotation().m_y);

		Vec3 pos = player->Pos() + Vec3(-sin(rad), 0.0f, cos(rad))*player->Scale().Length();

		player->RemoveChild(child);
		child->LocalPos(pos);
		ObjectBase::ROOT_OBJECT->AddChild(child);
		player->AlignUnits();
	}
}


/// <summary>
/// 投げる
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
		ObjectBase::ROOT_OBJECT->AddChild(child);

		//プレイヤーの向いている方向に力を加える
		float rad = ToRadian(player->Rotation().m_y);
			
		//投げる
		FlyingData data;
		data.start = child->WorldPos();
		data.end = player->WorldPos() + (Vec3(-sin(rad), 0.0f, cos(rad)).Normalize() *player->Power());
		data.power = player->Power();
		data.type = THROW_TYPE::LINE;
		child->ToBeThrow(data);	
	
		player->AlignUnits();
	}
}
