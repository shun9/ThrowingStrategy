//************************************************/
//* @file  :PlayerCommand.cpp
//* @brief :プレイヤーのコマンドまとめ
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
/// 拾う
/// </summary>
void PlayerPickUpCommand::Execute(Player * player)
{
	//同じチームを探す
	SearchTeamVisitor tV(player->Data().Team());
	tV.VisitSameTeam();
	player->Collider()->Accept(&tV);

	//ユニットを探す
	SearchUnitVisitor visitor;
	tV.Accept(&visitor);
	auto hitList = visitor.List();

	//持てるかどうか
	for (auto& v : hitList){
		//既に持っているユニットは対象外
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
/// 置く
/// </summary>
void PlayerPutCommand::Execute(Player * player)
{
	SearchUnitVisitor unitV;
	player->Accept(&unitV);

	//ユニットを所持していたら置く
	if (unitV.Count() > 0)
	{
		//先頭のユニットを対象とする
		Unit* child = unitV.List()[0];

		//プレイヤーの向いている方向
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
/// 投げる
/// </summary>
void PlayerThrowCommand::Execute(Player* player)
{
	Unit* child;
	SearchUnitVisitor v;
	player->Accept(&v);

	if (v.Count() > 0)
	{
		child = v.List()[0];

		//親子関係を解除
		//ステージに付け直す
		auto list = ObjectHolder::GetInstance()->List(ObjectConstantNumber::STAGE);

		//ステージは必ず１つ存在
		assert(list.size() == 1);

		child->SetParent(list[0]);
		//プレイヤーの向いている方向に力を加える
		float rad = ToRadian(player->Transform().Rotation().m_y);

		//投げる
		FlyingData data;
		m_flyData.start = child->WorldPos();
		m_flyData.type = ObjectConstantNumber::THROW_TYPE::LINE;
		child->ToBeThrow(m_flyData);

		player->AlignUnits();

		player->ChangeState(new PlayerMoveState);
	}
}

/// <summary>
/// プレイヤーを力をためる状態に切り替える
/// </summary>
void PlayerChangeMoveStateCommand::Execute(Player * obj)
{
	//ユニットを持っていたら切り替える
	if (obj->HavingUnitNum() > 0)
	{
		obj->ChangeState(new PlayerChargeState);
	}
}
