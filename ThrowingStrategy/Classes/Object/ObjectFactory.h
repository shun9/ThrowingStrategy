//************************************************/
//* @file  :ObjectFactory.h
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once
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
class UnitSummoner;

class ObjectFactory : public ShunLib::Singleton<ObjectFactory>
{
	friend ShunLib::Singleton<ObjectFactory>;
public:
	ShunLib::Factory<Player> m_playerFactory;
	ShunLib::Factory<Commander> m_commanderFactory;
	ShunLib::Factory<Unit> m_unitFactory;
	ShunLib::Factory<Block> m_blockFactory;
	ShunLib::Factory<DefenseTarget> m_defenseTargetFactory;
	ShunLib::Factory<Stage> m_stageFactory;
	ShunLib::Factory<UnitSummoner> m_summonerFactory;

public:
	ObjectBase* Create(OBJECT_LIST num);

private:
	ObjectFactory() {}
	~ObjectFactory();
};