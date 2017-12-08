//************************************************/
//* @file  :Unit.h
//* @brief :召喚されるユニット
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

struct FlyingData;
class Unit :public StateObject<Unit>
{
public:
	using SphereCollider = ShunLib::SphereCollider;
	using UNIT_LIST = ObjectConstantNumber::UNIT_LIST;

private:
	UNIT_LIST m_unitType;
	SphereCollider* m_collider;
	SphereCollider* m_attackRange;
	SphereCollider* m_chaseRange;

	float m_attackInterval;

public:
	Unit();
	~Unit() {}

	//初期化　終了
	void Initialize()override;
	void Finalize()override;

	//他ユニットに持ち上げられる
	void ToBeLifted();

	//他ユニットに投げられる
	void ToBeThrow(const FlyingData& data);

	/*--Getter--*/
	UNIT_LIST UnitType() { return m_unitType; }
	SphereCollider* AttackRange() { return m_attackRange; }
	SphereCollider* ChaseRange() { return m_chaseRange; }
	float AttackInterval() { return m_attackInterval; }

	/*--Setter--*/
	void UnitType(UNIT_LIST type) { m_unitType = type; }
	void AttackInterval(float interval) { m_attackInterval = interval; }

};