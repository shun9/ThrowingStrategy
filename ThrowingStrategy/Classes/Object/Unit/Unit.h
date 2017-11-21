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
private:
	UNIT_LIST m_unitType;
	ShunLib::SphereCollider* m_collider;
	ShunLib::SphereCollider* m_attackRange;

public:
	Unit():StateObject(this) {}
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
	ShunLib::SphereCollider* AttackRange() { return m_attackRange; }

	/*--Setter--*/
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};