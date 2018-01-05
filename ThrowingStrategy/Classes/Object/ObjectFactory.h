//************************************************/
//* @file  :ObjectFactory.h
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include <SL_Factory.h>

#include "ObjectConstantNumber.h"

//�쐬����N���X�ꗗ
class ObjectBase;
class Player;
class Commander;
class Unit;
class Block;
class DefenseTarget;
class Stage;
class GroundStage;
class UnitSummoner;

class ObjectFactory : public ShunLib::Singleton<ObjectFactory>
{
	friend ShunLib::Singleton<ObjectFactory>;
public:
	using ObjectList = std::vector<ObjectBase*>;
	using UNIT_TYPE = ObjectConstantNumber::UNIT_CONSTANT::TYPE_LIST;
	using STAGE_TYPE = ObjectConstantNumber::STAGE_LIST;
	using OBJECT_TYPE = ObjectConstantNumber::OBJECT_LIST;

private:
	std::vector<ObjectList> m_objectList;

	//�P��ނ̃I�u�W�F�N�g
	ShunLib::Factory<Player> m_playerFactory;
	ShunLib::Factory<Commander> m_commanderFactory;
	ShunLib::Factory<Block> m_blockFactory;
	ShunLib::Factory<DefenseTarget> m_defenseTargetFactory;
	ShunLib::Factory<UnitSummoner> m_summonerFactory;

	//���j�b�g�p
	ShunLib::Factory<Unit> m_unitFactory;

	//�X�e�[�W�p
	ShunLib::Factory<GroundStage> m_groundStageFactory;

public:
	ObjectBase* CreateObject(OBJECT_TYPE type);

	//�X�e�[�W�̍쐬
	Stage* CreateStage(STAGE_TYPE type);

	//���j�b�g�̍쐬
	Unit* CreateUnit(UNIT_TYPE type);

	//�w�肳�ꂽ�I�u�W�F�N�g���폜
	void Delete(ObjectBase* obj);

private:
	ObjectFactory() {}
	~ObjectFactory();
};