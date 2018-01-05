//************************************************/
//* @file  :Player.cpp
//* @brief :プレイヤー
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <SL_MacroConstants.h>
#include "State\PlayerMoveState.h"
#include "../../UI/HPGauge/HPGauge.h"
#include "../../Util/Visitor/Visitor.h"

#include "../../Game/Scene/SL_SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:StateObject(this,OBJECT_LIST::PLAYER)
{
	//当たり判定の設定
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(PLAYER_CONSTANT::COLLIDER_OFFSET);

	//当たり判定の形状の設定
	m_collider->Shape()->Scale(PLAYER_CONSTANT::COLLIDER_SIZE);

	//HPゲージの設定
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(PLAYER_CONSTANT::HP_GAUGE_OFFSET);
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_hpGauge);
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	//初期状態を設定
	ChangeState(new PlayerMoveState);

	//基底クラスの初期化
	StateObject::Initialize();
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	StateObject::Finalize();
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
		list[i]->LocalPos(PLAYER_CONSTANT::HAVING_OFFSET(i));
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


/// <summary>
/// 持っているユニットの一覧を返す
/// </summary>
std::vector<Unit*>& Player::HavingUnitList()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	return v.List();
}