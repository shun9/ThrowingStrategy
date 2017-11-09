//************************************************/
//* @file  :ObjectDataHolder.cpp
//* @brief :ユニットデータの一覧を保持するクラス
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "ObjectParamHolder.h"
#include "ObjectConstantNumber.h"

ObjectParamHolder::ObjectParamHolder()
{
	m_dataList.resize(OBJECT_LIST_END);

	ObjectParam data;
	data.maxHP = 100;
	data.power = 3;
	data.spd = 1.0f;
	data.model= std::make_shared<ShunLib::Model>(L"CModel\\Player.cmo");
	m_dataList[PLAYER] = data;

	data.maxHP = 100;
	data.power = 3;
	data.spd = 1.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Player.cmo");
	m_dataList[COMMANDER] = data;

	data.maxHP = 10;
	data.power = 3;
	data.spd = 1.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Ghost.cmo");
	m_dataList[UNIT] = data;
}
