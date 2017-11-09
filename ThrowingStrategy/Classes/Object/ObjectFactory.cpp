//************************************************/
//* @file  :ObjectFactory.cpp
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#include "ObjectFactory.h"
#include "Player\Player.h"
#include "Commander\Commander.h"
#include "Unit\Unit.h"

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
	case PLAYER:
		obj = m_playerFactory.Create();
		break;

	case COMMANDER:
		obj = m_commanderFactory.Create();
		break;

	case UNIT:
		obj = m_unitFactory.Create();
		break;

	default:
		break;
	}

	return obj;
}
