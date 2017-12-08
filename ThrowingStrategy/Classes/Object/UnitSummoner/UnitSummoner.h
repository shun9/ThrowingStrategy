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

class UnitSummoner :public StateObject<UnitSummoner>
{
public:
	using UNIT_LIST = ObjectConstantNumber::UNIT_LIST;

private:
	UNIT_LIST m_unitType;
	ShunLib::BoxCollider* m_collider;
	int m_interval;

public:
	UnitSummoner();
	~UnitSummoner();

	//���j�b�g������
	Unit* Summon();

	//Setter
	void UnitType(UNIT_LIST type) { m_unitType = type; }
};