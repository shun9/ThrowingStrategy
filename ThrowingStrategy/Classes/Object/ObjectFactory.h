//************************************************/
//* @file  :ObjectFactory.h
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once
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
	ObjectBase* CreateObject(ObjectConstantNumber::OBJECT_LIST type);

	//ステージの作成
	Stage* CreateStage(ObjectConstantNumber::STAGE_LIST type);

	//ユニットの作成
	Unit* CreateUnit(ObjectConstantNumber::UNIT_LIST type);

	//指定されたオブジェクトを削除
	void Delete(ObjectBase* obj);

private:
	ObjectFactory() {}
	~ObjectFactory();
};