//************************************************/
//* @file  :StandardStage.h
//* @brief :ギミックの無いステージ
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "Stage.h"

class StandardStage : public Stage
{
public:
	using Vec3 = ShunLib::Vec3;

public:
	StandardStage() :
		Stage(STAGE_TYPE::STANDARD) {}
	~StandardStage() {}

protected:
	//初期化 更新 終了
	void Initialize()override;
	void Update()override {}
	void Finalize()override;

	//障害物の設置
	void SettingObstacle()override;

	//オブジェクトの設置
	void SettingBlueObject()override;
	void SettingRedObject()override;

private:
	//壁の設置
	void SettingWall();

	//ステージの枠設置
	void SettingFrameOfStage();
};
