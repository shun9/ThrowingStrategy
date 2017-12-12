#pragma once
#include <memory>
#include <SL_Singleton.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"

class ObjectBase;
class Player;
class Commander;
class Unit;
class UnitSummoner;
class DefenseTarget;

class ObjectModelHolder : public ShunLib::Singleton<ObjectModelHolder>
{
	friend  ShunLib::Singleton<ObjectModelHolder>;
public:
	using Model = ShunLib::Model;
	using OBJ_TYPE = ObjectConstantNumber::OBJECT_LIST;
	using UNIT_TYPE = ObjectConstantNumber::UNIT_CONSTANT::TYPE_LIST;
	using TEAM = ObjectConstantNumber::TEAM;

private:
	std::unique_ptr<Model> m_plarerRed;
	std::unique_ptr<Model> m_plarerBlue;
	std::unique_ptr<Model> m_ghostRed;
	std::unique_ptr<Model> m_ghostBlue;
	std::unique_ptr<Model> m_box;
	std::unique_ptr<Model> m_hedoraRed;
	std::unique_ptr<Model> m_hedoraBlue;
	std::unique_ptr<Model> m_tubeRed;
	std::unique_ptr<Model> m_tubeBlue;

public:
	Model* GetModel(ObjectBase* obj);

private:
	ObjectModelHolder();
	~ObjectModelHolder() {}

	Model* GetPlayerModel(Player* player);
	Model* GetCommanderModel(Commander* commander);
	Model* GetUnitModel(Unit* unit);
	Model* GetSummonerModel(UnitSummoner* summoner);
	Model* GetDefenseTargetModel(DefenseTarget* target);
};