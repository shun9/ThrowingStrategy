//************************************************/
//* @file  :UnitSummoner.h
//* @brief :���j�b�g����������I�u�W�F�N�g
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
	//�������郆�j�b�g�̎��
	UNIT_LIST m_unitType;

	//�{�̂̓����蔻��
	ShunLib::BoxCollider* m_collider;

	//HP�Q�[�W
	HPGauge* m_hpGauge;

	//�����Ԋu
	int m_interval;

public:
	UnitSummoner();
	~UnitSummoner();

	//������
	void Initialize()override;
	void Finalize()override;

	//���j�b�g������
	Unit* Summon();

	/*--Getter--*/
	int Interval() { return m_interval; }

	/*--Setter--*/
	void Interval(int interval) {m_interval = interval;}
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};