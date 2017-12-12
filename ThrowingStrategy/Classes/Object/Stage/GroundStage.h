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

	//初期化
	void Initialize()override;

	//終了 
	void Finalize()override;

protected:
	//障害物の設置
	void SettingObstacle()override;

	//オブジェクトの設置
	void SettingBlueObject()override;
	void SettingRedObject()override;
};