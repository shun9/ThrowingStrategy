//************************************************/
//* @file  :ObjectFactory.cpp
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#include "ObjectFactory.h"
#include "Player\Player.h"

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

	default:
		break;
	}

	return obj;
}
