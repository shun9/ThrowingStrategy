//************************************************/
//* @file  :Stage.h
//* @brief :ステージの基底クラス
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include "../ObjectBase.h"

//ステージの基底
class Stage : public ObjectBase
{
public:
	using STAGE_TYPE = ObjectConstantNumber::STAGE_LIST;

protected:
	//ステージの種類
	ObjectConstantNumber::STAGE_LIST m_stageType;

public:
	Stage(STAGE_TYPE type);
	virtual ~Stage();

protected:
	//障害物の設置
	virtual void SettingObstacle() = 0;

	//オブジェクトの設置
	virtual void SettingBlueObject() = 0;
	virtual void SettingRedObject() = 0;
};

