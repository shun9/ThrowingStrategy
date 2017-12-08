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

UnitSummoner::UnitSummoner():
	StateObject(this) ,
	m_interval(120)
{
	this->Team(ObjectConstantNumber::BLUE);
	this->Type(ObjectConstantNumber::SUMMONER);
	this->UnitType(ObjectConstantNumber::NORMAL);

	m_collider = new ShunLib::BoxCollider;
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.0f, 0.0f));
	m_collider->Shape()->Size(ShunLib::Vec3(2.0f,0.2f,2.0f));
	this->ChangeState(new SummonerSteadyState);
}

UnitSummoner::~UnitSummoner()
{
	DELETE_POINTER(m_collider);
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
	
	//���[�g�ɕR�Â�
	ObjectBase::ROOT_OBJECT->AddChild(unit);

	//������
	unit->Initialize();
	
	//�����ʒu�ݒ�
	unit->Pos(this->Pos());

	//�����`�[�������ɂ���
	unit->Team(this->Team());

	return unit;
}
