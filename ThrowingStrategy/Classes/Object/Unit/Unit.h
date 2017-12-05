//************************************************/
//* @file  :Unit.h
//* @brief :��������郆�j�b�g
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

struct FlyingData;
class Unit :public StateObject<Unit>
{
	using SphereCollider = ShunLib::SphereCollider;
private:
	UNIT_LIST m_unitType;
	SphereCollider* m_collider;
	SphereCollider* m_attackRange;
	SphereCollider* m_chaseRange;

public:
	Unit():StateObject(this) {}
	~Unit() {}

	//�������@�I��
	void Initialize()override;
	void Finalize()override;

	//�����j�b�g�Ɏ����グ����
	void ToBeLifted();

	//�����j�b�g�ɓ�������
	void ToBeThrow(const FlyingData& data);

	/*--Getter--*/
	UNIT_LIST UnitType() { return m_unitType; }
	SphereCollider* AttackRange() { return m_attackRange; }
	SphereCollider* ChaseRange() { return m_chaseRange; }

	/*--Setter--*/
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};