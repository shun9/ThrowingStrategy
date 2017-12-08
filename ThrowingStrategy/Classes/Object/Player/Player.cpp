//************************************************/
//* @file  :Player.cpp
//* @brief :プレイヤー
//* @date  :2017/12/01
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <functional>
#include <SL_MacroConstants.h>
#include <SL_Math.h>
#include "State\PlayerMoveState.h"
#include "../Unit/Unit.h"
#include "../../Util/Visitor/Visitor.h"
#include "../ObjectMacro.h"

Player::Player()
	:StateObject(this,OBJECT_LIST::PLAYER)
{
	//チーム設定(仮)　※いずれ消す
	this->Team(TEAM::BLUE);

	//基本情報設定
	this->ChangeState(new PlayerMoveState);

	//当たり判定の設定
	m_collider = new ShunLib::SphereCollider();
	m_collider->PosObj(this);
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.0f, 0.0f));
	m_collider->SetCallBack([&](ObjectBase* obj) { this->CollisionCallBack(obj); });

	//当たり判定の形状の設定
	m_collider->Shape()->Scale(1.0f);

}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{	
	//基底クラスの初期化
	StateObject::Initialize();
}

void Player::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
}


/// <summary>
/// ユニットを揃える
/// </summary>
void Player::AlignUnits()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	auto list = v.List();
	for (int i = 0; i < (int)list.size(); i++){
		list[i]->LocalPos(OFFSET_HAVING_UNIT(i));
	}
}

/// <summary>
/// 持っているユニットの数を返す
/// </summary>
int Player::HavingUnitNum()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	return v.Count();
}


std::vector<Unit*>& Player::HavingUnitList()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	return v.List();
}

void Player::CollisionCallBack(ObjectBase* obj){
}
