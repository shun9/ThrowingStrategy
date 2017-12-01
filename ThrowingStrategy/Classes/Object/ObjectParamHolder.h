//************************************************/
//* @file  :ObjectDataHolder.h
//* @brief :オブジェクトのゲームパラメータの一覧を保持するクラス
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <SL_Singleton.h>
#include <SL_Model.h>

//オブジェクトのパラメーターを取得する
#define OBJ_PARAM(type) ObjectParamHolder::GetInstance()->GetParam(type)


//ユニットのデータ
struct ObjectParam
{
public:
	int maxHP;
	float power;
	float spd;
	std::shared_ptr<ShunLib::Model> model;
};

class ObjectParamHolder : public ShunLib::Singleton<ObjectParamHolder>
{
	friend ShunLib::Singleton<ObjectParamHolder>;
private:
	//データ一覧
	std::vector<ObjectParam> m_dataList;

public:
	//データの取得
	const ObjectParam& GetParam(int dataNum) {
		return m_dataList.at(dataNum);
	}

private:
	ObjectParamHolder();
	~ObjectParamHolder() {}
};