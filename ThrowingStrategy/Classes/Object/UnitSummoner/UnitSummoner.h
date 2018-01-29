//************************************************/
//* @file  :UnitSummoner.h
//* @brief :ユニットを召喚するオブジェクト
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../ObjectConstantNumber.h"
#include "../../Physics/Collision/SL_Collider.h"

class Unit;
class HPGauge;

class UnitSummoner :public StateObject<UnitSummoner>
{
public:
	using UNIT_LIST = ObjectConstantNumber::UNIT_CONSTANT::TYPE_LIST;
	using SUMMONER_CONSTANT = ObjectConstantNumber::SUMMONER_CONSTANT;

private:
	//召喚するユニットの種類
	UNIT_LIST m_unitType;

	//本体の当たり判定
	ShunLib::BoxCollider* m_collider;

	//HPゲージ
	HPGauge* m_hpGauge;

	//召喚間隔
	int m_interval;

public:
	UnitSummoner();
	~UnitSummoner();

	//初期化
	void Initialize()override;
	void Finalize()override;

	//ユニットを召喚
	Unit* Summon();

	/*--Getter--*/
	int Interval() { return m_interval; }

	/*--Setter--*/
	void Interval(int interval) {m_interval = interval;}
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};