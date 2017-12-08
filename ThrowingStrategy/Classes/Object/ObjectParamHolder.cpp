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
	m_dataList.resize(ObjectConstantNumber::OBJECT_LIST_END);

	ObjectParam data;

	//ルートオブジェクト
	data.maxHP = 99999;
	data.power = 99999.0f;
	data.spd = 99.0f;
	m_dataList[ObjectConstantNumber::ROOT] = data;

	//プレイヤー
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	m_dataList[ObjectConstantNumber::PLAYER] = data;

	//指揮官
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	m_dataList[ObjectConstantNumber::COMMANDER] = data;

	//召喚ユニット
	data.maxHP = 10;
	data.power = 3.0f;
	data.spd = 3.0f;
	m_dataList[ObjectConstantNumber::UNIT] = data;

	//ブロック
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::BLOCK] = data;

	//防衛対象
	data.maxHP = 20000;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::DEFENSE_TARGET] = data;

	//ユニットを召喚するオブジェクト
	data.maxHP = 10000;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::SUMMONER] = data;

	//ステージ
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::STAGE] = data;
}
