//************************************************/
//* @file  :GroundStage.h
//* @brief :地面のみのステージ
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#pragma once
#include "Stage.h"

class GroundStage : public Stage
{
public:
	GroundStage():
		Stage(STAGE_TYPE::GROUND){};
	~GroundStage() {};


protected:
	//初期化 更新 終了
	void Initialize()override;
	void Update    ()override {}
	void Finalize  ()override;

	//障害物の設置
	void SettingObstacle()override;

	//オブジェクトの設置
	void SettingBlueObject()override;
	void SettingRedObject()override;
};