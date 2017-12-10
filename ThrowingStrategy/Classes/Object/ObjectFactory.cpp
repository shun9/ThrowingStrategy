//************************************************/
//* @file  :ObjectFactory.cpp
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "ObjectFactory.h"
#include "Player\Player.h"
#include "Commander\Commander.h"
#include "Unit\Unit.h"
#include "DefenseTarget\DefenseTarget.h"
#include "Stage\GroundStage.h"
#include "Stage\StageObject.h"
#include "UnitSummoner\UnitSummoner.h"

/// <summary>
/// �I�u�W�F�N�g�̐���
/// </summary>
/// <param name="num">�I�u�W�F�N�g�̎��</param>
/// <returns>���������I�u�W�F�N�g</returns>
ObjectBase* ObjectFactory::CreateObject(ObjectConstantNumber::OBJECT_LIST type)
{
	ObjectBase* obj = nullptr;

	switch (type)
	{
	case ObjectConstantNumber::PLAYER:			 obj = m_playerFactory.Create();break;
	case ObjectConstantNumber::COMMANDER:	     obj = m_commanderFactory.Create();break;
	case ObjectConstantNumber::UNIT:		     obj = m_unitFactory.Create();break;
	case ObjectConstantNumber::BLOCK:		     obj = m_blockFactory.Create(); break;
	case ObjectConstantNumber::DEFENSE_TARGET:	 obj = m_defenseTargetFactory.Create(); break;
	case ObjectConstantNumber::SUMMONER:		 obj = m_summonerFactory.Create(); break;
	default:break;
	}

	return obj;
}

/// <summary>
/// �X�e�[�W�쐬
/// </summary>
/// <param name="type">�X�e�[�W�̎��</param>
Stage* ObjectFactory::CreateStage(ObjectConstantNumber::STAGE_LIST type)
{
	Stage* stage = nullptr;

	switch (type)
	{
	case ObjectConstantNumber::GROUND:
		stage = m_groundStageFactory.Create();
		break;
	default:
		break;
	}
	return stage;
}


/// <summary>
/// ���j�b�g�̍쐬
/// </summary>
/// <param name="type">���j�b�g�̎��</param>
Unit* ObjectFactory::CreateUnit(ObjectConstantNumber::UNIT_LIST type)
{
	Unit* unit = nullptr;

	switch (type)
	{
	case ObjectConstantNumber::NORMAL:
		unit = m_unitFactory.Create();
		break; 
	default:
		break;
	}
	return unit;
}

/// <summary>
/// �w�肳�ꂽ�I�u�W�F�N�g���폜
/// </summary>
/// <param name="obj">�폜����I�u�W�F�N�g</param>
void ObjectFactory::Delete(ObjectBase * obj)
{
	switch (obj->Type())
	{
	case ObjectConstantNumber::PLAYER:			 m_playerFactory.Delete(dynamic_cast<Player*>(obj)); break;
	case ObjectConstantNumber::COMMANDER:	     m_commanderFactory.Delete(dynamic_cast<Commander*>(obj)); break;
	case ObjectConstantNumber::UNIT:		     m_unitFactory.Delete(dynamic_cast<Unit*>(obj)); break;
	case ObjectConstantNumber::BLOCK:		     m_blockFactory.Delete(dynamic_cast<Block*>(obj)); break;
	case ObjectConstantNumber::DEFENSE_TARGET:	 m_defenseTargetFactory.Delete(dynamic_cast<DefenseTarget*>(obj)); break;
	case ObjectConstantNumber::SUMMONER:		 m_summonerFactory.Delete(dynamic_cast<UnitSummoner*>(obj)); break;
	default:break;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectFactory::~ObjectFactory()
{
	m_playerFactory.AllDelete();
	m_commanderFactory.AllDelete();
	m_unitFactory.AllDelete();
	m_blockFactory.AllDelete();
	m_defenseTargetFactory.AllDelete();
	m_groundStageFactory.AllDelete();
	m_summonerFactory.AllDelete();
}
