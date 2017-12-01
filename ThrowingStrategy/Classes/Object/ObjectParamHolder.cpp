//************************************************/
//* @file  :ObjectDataHolder.cpp
//* @brief :ユニットデータの一覧を保持するクラス
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "ObjectParamHolder.h"
#include "ObjectConstantNumber.h"

ObjectParamHolder::ObjectParamHolder()
{
	m_dataList.resize(OBJECT_LIST_END);

	ObjectParam data;

	//ルートオブジェクト
	data.maxHP = 99999;
	data.power = 99999.0f;
	data.spd = 99.0f;
	data.model = nullptr;
	m_dataList[ROOT] = data;

	//プレイヤー
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Player.cmo");
	m_dataList[PLAYER] = data;

	//指揮官
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Player.cmo");
	m_dataList[COMMANDER] = data;

	//召喚ユニット
	data.maxHP = 10;
	data.power = 3.0f;
	data.spd = 3.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Ghost.cmo");
	m_dataList[UNIT] = data;

	//ブロック
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Box.cmo");
	m_dataList[BLOCK] = data;

	//防衛対象
	data.maxHP = 20000;
	data.power = 0.0f;
	data.spd = 0.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Octahedron.cmo");
	m_dataList[DEFENSE_TARGET] = data;

	//ユニットを召喚するオブジェクト
	data.maxHP = 10000;
	data.power = 0.0f;
	data.spd = 0.0f;
	data.model = std::make_shared<ShunLib::Model>(L"CModel\\Tube.cmo");
	m_dataList[SUMMONER] = data;

	//ステージ
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	data.model = nullptr;
	m_dataList[STAGE] = data;
}
