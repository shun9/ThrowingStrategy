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
}

void GroundStage::Finalize()
{

}

/// <summary>
/// 障害物の設置
/// </summary>
void GroundStage::SettingObstacle() {
	auto factory = ObjectFactory::GetInstance();
	ObjectBase* b = factory->CreateObject(OBJECT_LIST::BLOCK);
	b->Transform().Pos(ShunLib::Vec3(0.0f, -1.0f, 0.0f));
	b->Transform().Scale(ShunLib::Vec3(100.0f, 1.0f, 100.0f));

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
	p->Transform().Pos(ShunLib::Vec3(-25.0f, 0.0f, 0.0f));
	p->Data().Team(ObjectConstantNumber::BLUE);
	p->SetParent(this);

	//ユニット召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Transform().Pos(ShunLib::Vec3(-20.0f, 0.0f, 0.0f));
	summoner->Data().Team(p->Data().Team());
	dynamic_cast<UnitSummoner*>(summoner)->Interval(1000);
	summoner->SetParent(this);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(-30.0f, 0.0f, 0.0f));
	target->Data().Team(p->Data().Team());
	target->SetParent(this);
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
	summoner->Transform().Pos(ShunLib::Vec3(20.0f, 0.0f, 0.0f));
	summoner->Data().Team(ObjectConstantNumber::TEAM::RED);
	summoner->SetParent(this);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(2000);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(30.0f, 0.0f, 0.0f));
	target->Data().Team(ObjectConstantNumber::TEAM::RED);
	target->SetParent(this);
}
