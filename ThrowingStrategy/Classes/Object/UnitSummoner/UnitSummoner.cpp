//************************************************/
//* @file  :UnitSummoner.h
//* @brief :ユニットを召喚するオブジェクト
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#include "UnitSummoner.h"
#include "State\SummonerSteadyState.h"

#include "../ObjectFactory.h"
#include "../Unit/Unit.h"
#include "../../UI/HPGauge/HPGauge.h"

UnitSummoner::UnitSummoner():
	StateObject(this, ObjectConstantNumber::SUMMONER) ,
	m_interval(120)
{
	this->UnitType(UNIT_LIST::NORMAL);

	//当たり判定設定
	m_collider = new ShunLib::BoxCollider;
	m_collider->Parent(this);
	m_collider->ChaseObj(this);
	m_collider->Offset(SUMMONER_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Size(SUMMONER_CONSTANT::COLLIDER_SIZE);

	//HPゲージ設定
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(SUMMONER_CONSTANT::HP_GAUGE_OFFSET);
}

UnitSummoner::~UnitSummoner()
{
	DELETE_POINTER(m_hpGauge);
	DELETE_POINTER(m_collider);
}

/// <summary>
/// 初期化
/// </summary>
void UnitSummoner::Initialize()
{
	//初期状態設定
	this->ChangeState(new SummonerSteadyState);

	StateObject::Initialize();
}

/// <summary>
/// ユニットを召喚する
/// </summary>
Unit* UnitSummoner::Summon()
{
	//ユニット作成
	auto unit = ObjectFactory::GetInstance()->CreateUnit(UNIT_LIST::NORMAL);

	//種類を設定
	unit->UnitType(m_unitType);

	//初期化
	unit->Initialize();

	//召喚位置設定
	unit->Transform().Pos(m_transform.Pos());

	//同じチーム所属にする
	unit->Data().Team(m_data.Team());

	return unit;
}
