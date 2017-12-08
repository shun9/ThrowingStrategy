//************************************************/
//* @file  :GroundStage.cpp
//* @brief :地面のみのステージ
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#include "GroundStage.h"
#include "../ObjectFactory.h"
#include "../../Util/SL_Camera.h"
#include "../ObjectFactory.h"

void GroundStage::Initialize()
{
	//障害物の設置
	SettingObstacle();

	//オブジェクトの設置
	SettingObject();

	//基底の初期化
	//子の更新
	ObjectBase::Initialize();
}

void GroundStage::Finalize()
{
	ObjectBase::Finalize();
}

/// <summary>
/// 障害物の設置
/// </summary>
void GroundStage::SettingObstacle() {
	auto factory = ObjectFactory::GetInstance();
	ObjectBase* b = factory->CreateObject(OBJECT_LIST::BLOCK);
	b->Pos(ShunLib::Vec3(0.0f, -1.0f, 0.0f));
	b->Scale(ShunLib::Vec3(100.0f, 1.0f, 100.0f));

	this->AddChild(b);
}


/// <summary>
/// オブジェクトの設置
/// </summary>
void GroundStage::SettingObject()
{
	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();

	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//プレイヤーは青チーム
	auto p = factory->CreateObject(ObjectConstantNumber::PLAYER);
	camera->FollowTarget(p);
	camera->ChangeMode(FOLLOW_CAMERA);
	p->Pos(ShunLib::Vec3(-10.0f, 0.0f, 0.0f));
	p->Team(ObjectConstantNumber::BLUE);

	//青チーム召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(-9.0f, 0.0f, 0.0f));
	summoner->Team(p->Team());

	//赤チーム召喚オブジェクト
	summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(9.0f, 0.0f, 0.0f));
	summoner->Team(ObjectConstantNumber::TEAM::RED);
}
