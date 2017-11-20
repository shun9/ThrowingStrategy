//************************************************/
//* @file  :ObjectFactory.cpp
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "ObjectFactory.h"
#include "Player\Player.h"
#include "Commander\Commander.h"
#include "Unit\Unit.h"
#include "DefenseTarget\DefenseTarget.h"
#include "Stage\Stage.h"
#include "Stage\StageObject.h"

/// <summary>
/// オブジェクトの生成
/// </summary>
/// <param name="num">オブジェクトの番号</param>
/// <returns>生成したオブジェクト</returns>
ObjectBase* ObjectFactory::Create(OBJECT_LIST num)
{
	ObjectBase* obj = nullptr;

	switch (num)
	{
	case PLAYER:	     obj = m_playerFactory.Create();break;
	case COMMANDER:	     obj = m_commanderFactory.Create();break;
	case UNIT:		     obj = m_unitFactory.Create();break;
	case BLOCK:		     obj = m_blockFactory.Create(); break;
	case DEFENSE_TARGET: obj = m_defenseTargetFactory.Create(); break;
	case STAGE:		     obj = m_stageFactory.Create(); break;
	default:break;
	}

	return obj;
}


ObjectFactory::~ObjectFactory()
{
	m_playerFactory.AllDelete();
	m_commanderFactory.AllDelete();
	m_unitFactory.AllDelete();
	m_blockFactory.AllDelete();
	m_defenseTargetFactory.AllDelete();
	m_stageFactory.AllDelete();
}
