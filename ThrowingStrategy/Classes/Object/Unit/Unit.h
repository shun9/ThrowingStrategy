//************************************************/
//* @file  :Unit.h
//* @brief :召喚されるユニット
//* @date  :2017/01/11
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

struct FlyingData;
class HPGauge;

class Unit :public StateObject<Unit>
{
public:
	using SphereCollider = ShunLib::SphereCollider;
	using UNIT_CONSTANT = ObjectConstantNumber::UNIT_CONSTANT;
	using UNIT_LIST = ObjectConstantNumber::UNIT_CONSTANT::TYPE_LIST;

private:
	//ユニットの種類
	UNIT_LIST m_unitType;

	//当たり判定
	SphereCollider* m_collider;
	SphereCollider* m_attackRange;
	SphereCollider* m_chaseRange;

	//HPゲージ
	HPGauge* m_hpGauge;

	float m_attackInterval;

public:
	Unit();
	~Unit()override {}

	//初期化　終了
	void Initialize()override;
	void Finalize()override;

	//他ユニットに持ち上げられる
	void ToBeLifted();

	//他ユニットに置かれる
	void ToBePlaced();

	//他ユニットに投げられる
	void ToBeThrow(const FlyingData& data);

	//当たり判定を使用する
	void EnableCollider();

	//当たり判定を使用しない
	void DisableCollider();

	/*--Getter--*/
	UNIT_LIST UnitType() { return m_unitType; }
	SphereCollider* AttackRange() { return m_attackRange; }
	SphereCollider* ChaseRange() { return m_chaseRange; }
	float AttackInterval() { return m_attackInterval; }

	/*--Setter--*/
	void UnitType(UNIT_LIST type) { m_unitType = type; }
	void AttackInterval(float interval) { m_attackInterval = interval; }

};