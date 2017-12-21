//************************************************/
//* @file  :UnitSummoner.h
//* @brief :���j�b�g����������I�u�W�F�N�g
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#include "UnitSummoner.h"
#include "State\SummonerSteadyState.h"

#include "../ObjectFactory.h"
#include "../Unit/Unit.h"
#include "../../UI/HPGauge/HPGauge.h"

UnitSummoner::UnitSummoner():
	StateObject(this, ObjectConstantNumber::SUMMONER) ,
	m_interval(120)
{
	this->UnitType(UNIT_LIST::NORMAL);

	//�����蔻��ݒ�
	m_collider = new ShunLib::BoxCollider;
	m_collider->Parent(this);
	m_collider->ChaseObj(this);
	m_collider->Offset(SUMMONER_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Size(SUMMONER_CONSTANT::COLLIDER_SIZE);

	//HP�Q�[�W�ݒ�
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(SUMMONER_CONSTANT::HP_GAUGE_OFFSET);
}

UnitSummoner::~UnitSummoner()
{
	DELETE_POINTER(m_hpGauge);
	DELETE_POINTER(m_collider);
}

/// <summary>
/// ������
/// </summary>
void UnitSummoner::Initialize()
{
	//������Ԑݒ�
	this->ChangeState(new SummonerSteadyState);

	StateObject::Initialize();
}

/// <summary>
/// ���j�b�g����������
/// </summary>
Unit* UnitSummoner::Summon()
{
	//���j�b�g�쐬
	auto unit = ObjectFactory::GetInstance()->CreateUnit(UNIT_LIST::NORMAL);

	//��ނ�ݒ�
	unit->UnitType(m_unitType);

	//������
	unit->Initialize();

	//�����ʒu�ݒ�
	unit->Transform().Pos(m_transform.Pos());

	//�����`�[�������ɂ���
	unit->Data().Team(m_data.Team());

	return unit;
}
