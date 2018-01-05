//************************************************/
//* @file  :ObjectFactory.h
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include <SL_Factory.h>

#include "ObjectConstantNumber.h"

//作成するクラス一覧
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

	//１種類のオブジェクト
	ShunLib::Factory<Player> m_playerFactory;
	ShunLib::Factory<Commander> m_commanderFactory;
	ShunLib::Factory<Block> m_blockFactory;
	ShunLib::Factory<DefenseTarget> m_defenseTargetFactory;
	ShunLib::Factory<UnitSummoner> m_summonerFactory;

	//ユニット用
	ShunLib::Factory<Unit> m_unitFactory;

	//ステージ用
	ShunLib::Factory<GroundStage> m_groundStageFactory;

public:
	ObjectBase* CreateObject(OBJECT_TYPE type);

	//ステージの作成
	Stage* CreateStage(STAGE_TYPE type);

	//ユニットの作成
	Unit* CreateUnit(UNIT_TYPE type);

	//指定されたオブジェクトを削除
	void Delete(ObjectBase* obj);

private:
	ObjectFactory() {}
	~ObjectFactory();
};