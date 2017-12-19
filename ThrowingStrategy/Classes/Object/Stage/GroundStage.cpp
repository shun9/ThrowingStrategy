//************************************************/
//* @file  :GroundStage.cpp
//* @brief :地面のみのステージ
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#include "GroundStage.h"
#include "../ObjectFactory.h"
#include "../../Util/SL_Camera.h"
#include "../UnitSummoner/UnitSummoner.h"

void GroundStage::Initialize()
{
	//障害物の設置
	SettingObstacle();

	//青チームの設置
	SettingBlueObject();

	//赤チーム設置
	SettingRedObject();

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
/// 青チームオブジェクトの設置
/// </summary>
void GroundStage::SettingBlueObject()
{
	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();

	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//プレイヤー作成
	//プレイヤーは青チーム
	auto p = factory->CreateObject(ObjectConstantNumber::PLAYER);
	camera->FollowTarget(p);
	camera->ChangeMode(FOLLOW_CAMERA);
	p->Pos(ShunLib::Vec3(-25.0f, 0.0f, 0.0f));
	p->Team(ObjectConstantNumber::BLUE);

	//ユニット召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(-20.0f, 0.0f, 0.0f));
	summoner->Team(p->Team());
	dynamic_cast<UnitSummoner*>(summoner)->Interval(1000);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Pos(ShunLib::Vec3(-30.0f, 0.0f, 0.0f));
	target->Team(p->Team());
}

/// <summary>
/// 赤チームオブジェクトの設置
/// </summary>
void GroundStage::SettingRedObject()
{
	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(20.0f, 0.0f, 0.0f));
	summoner->Team(ObjectConstantNumber::TEAM::RED);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(2000);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Pos(ShunLib::Vec3(30.0f, 0.0f, 0.0f));
	target->Team(ObjectConstantNumber::TEAM::RED);
}
