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
private:
	UNIT_LIST m_unitType;
	ShunLib::SphereCollider* m_collider;
	ShunLib::SphereCollider* m_attackRange;

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
	ShunLib::SphereCollider* AttackRange() { return m_attackRange; }

	/*--Setter--*/
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};