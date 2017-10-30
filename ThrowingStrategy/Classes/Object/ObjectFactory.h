//************************************************/
//* @file  :ObjectFactory.h
//* @brief :オブジェクトを生成するクラス
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Factory.h>

#include "ObjectConstantNumber.h"

//作成するクラス一覧
class ObjectBase;
class Player;

class ObjectFactory : public ShunLib::Singleton<ObjectFactory>
{
	friend ShunLib::Singleton<ObjectFactory>;
public:
	ShunLib::Factory<Player> m_playerFactory;

public:
	ObjectBase* Create(OBJECT_LIST num);
	
private:
	ObjectFactory() {}
	~ObjectFactory() {}
};