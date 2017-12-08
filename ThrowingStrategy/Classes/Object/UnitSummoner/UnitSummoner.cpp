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

UnitSummoner::UnitSummoner():
	StateObject(this) ,
	m_interval(120)
{
	this->Team(ObjectConstantNumber::BLUE);
	this->Type(ObjectConstantNumber::SUMMONER);
	this->UnitType(ObjectConstantNumber::NORMAL);

	m_collider = new ShunLib::BoxCollider;
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.0f, 0.0f));
	m_collider->Shape()->Size(ShunLib::Vec3(2.0f,0.2f,2.0f));
	this->ChangeState(new SummonerSteadyState);
}

UnitSummoner::~UnitSummoner()
{
	DELETE_POINTER(m_collider);
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
	
	//ルートに紐づけ
	ObjectBase::ROOT_OBJECT->AddChild(unit);

	//初期化
	unit->Initialize();
	
	//召喚位置設定
	unit->Pos(this->Pos());

	//同じチーム所属にする
	unit->Team(this->Team());

	return unit;
}
