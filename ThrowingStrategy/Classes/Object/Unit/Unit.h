//************************************************/
//* @file  :Unit.h
//* @brief :��������郆�j�b�g
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
	//���j�b�g�̎��
	UNIT_LIST m_unitType;

	//�����蔻��
	SphereCollider* m_collider;
	SphereCollider* m_attackRange;
	SphereCollider* m_chaseRange;

	//HP�Q�[�W
	HPGauge* m_hpGauge;

	float m_attackInterval;

public:
	Unit();
	~Unit()override {}

	//�������@�I��
	void Initialize()override;
	void Finalize()override;

	//�����j�b�g�Ɏ����グ����
	void ToBeLifted();

	//�����j�b�g�ɒu�����
	void ToBePlaced();

	//�����j�b�g�ɓ�������
	void ToBeThrow(const FlyingData& data);

	//�����蔻����g�p����
	void EnableCollider();

	//�����蔻����g�p���Ȃ�
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