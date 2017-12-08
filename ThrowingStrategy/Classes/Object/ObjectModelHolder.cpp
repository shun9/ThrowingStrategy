#include "ObjectModelHolder.h"
#include "Player\Player.h"
#include "Commander\Commander.h"
#include "Unit\Unit.h"
#include "UnitSummoner\UnitSummoner.h"
#include "DefenseTarget\DefenseTarget.h"

ShunLib::Model* ObjectModelHolder::GetModel(ObjectBase* obj)
{
	ShunLib::Model* model = nullptr;

	switch (obj->Type())
	{
	case OBJ_TYPE::PLAYER			: model = GetPlayerModel(dynamic_cast<Player*>(obj)); break;
	case OBJ_TYPE::COMMANDER		: model = GetCommanderModel(dynamic_cast<Commander*>(obj)); break;
	case OBJ_TYPE::UNIT				: model = GetUnitModel(dynamic_cast<Unit*>(obj)); break;
	case OBJ_TYPE::BLOCK			: model = m_box.get(); break; 
	case OBJ_TYPE::DEFENSE_TARGET	: model = GetDefenseTargetModel(dynamic_cast<DefenseTarget*>(obj)); break;
	case OBJ_TYPE::SUMMONER			: model = GetSummonerModel(dynamic_cast<UnitSummoner*>(obj)); break;
	default:break;
	}
	return model;
}

ObjectModelHolder::ObjectModelHolder()
{
	m_plarerBlue = std::make_unique<ShunLib::Model>(L"CModel\\Player.cmo");
	m_plarerRed  = std::make_unique<ShunLib::Model>(L"CModel\\PlayerB.cmo");
	m_ghostBlue  = std::make_unique<ShunLib::Model>(L"CModel\\Ghost.cmo");
	m_ghostRed   = std::make_unique<ShunLib::Model>(L"CModel\\Ghost2.cmo");
	m_box        = std::make_unique<ShunLib::Model>(L"CModel\\Box.cmo");
	m_hedoraRed  = std::make_unique<ShunLib::Model>(L"CModel\\Hedora.cmo");
	m_hedoraBlue = std::make_unique<ShunLib::Model>(L"CModel\\Hedora2.cmo");
	m_tubeBlue   = std::make_unique<ShunLib::Model>(L"CModel\\Tube.cmo");
	m_tubeRed    = std::make_unique<ShunLib::Model>(L"CModel\\Tube2.cmo");
}

/// <summary>
/// プレイヤーのモデルを返す
/// </summary>
ShunLib::Model* ObjectModelHolder::GetPlayerModel(Player * player){

	ShunLib::Model* model = nullptr;
	switch (player->Team())
	{
	case TEAM::BLUE:
		model = m_plarerBlue.get();
		break;
	case TEAM::RED:
		model = m_plarerRed.get();
		break;
	default:
		break;
	}
	return model;
}

/// <summary>
/// 指揮官のモデルを返す
/// </summary>
ShunLib::Model * ObjectModelHolder::GetCommanderModel(Commander * commander)
{
	ShunLib::Model* model = nullptr;
	switch (commander->Team())
	{
	case TEAM::BLUE:
		model = m_plarerBlue.get();
		break;
	case TEAM::RED:
		model = m_plarerRed.get();
		break;
	default:
		break;
	}

	return model;
}

/// <summary>
/// ユニットのモデルを返す
/// </summary>
ShunLib::Model * ObjectModelHolder::GetUnitModel(Unit * unit)
{
	ShunLib::Model* model = nullptr;
	switch (unit->Team())
	{
	case TEAM::BLUE:
		model = m_ghostBlue.get();
		break;
	case TEAM::RED:
		model = m_ghostRed.get();
		break;
	default:
		break;
	}

	return model;
}

/// <summary>
/// ユニット召喚オブジェクトのモデルを返す
/// </summary>
ShunLib::Model * ObjectModelHolder::GetSummonerModel(UnitSummoner * summoner)
{
	ShunLib::Model* model = nullptr;
	switch (summoner->Team())
	{
	case TEAM::BLUE:
		model = m_tubeBlue.get();
		break;
	case TEAM::RED:
		model = m_tubeRed.get();
		break;
	default:
		break;
	}

	return model;
}

/// <summary>
/// 防衛対象のモデルを返す
/// </summary>
ShunLib::Model * ObjectModelHolder::GetDefenseTargetModel(DefenseTarget * target)
{
	ShunLib::Model* model = nullptr;
	switch (target->Team())
	{
	case TEAM::BLUE:
		model = m_hedoraBlue.get();
		break;
	case TEAM::RED:
		model = m_hedoraRed.get();
		break;
	default:
		break;
	}

	return model;
}
