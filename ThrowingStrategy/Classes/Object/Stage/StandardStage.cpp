//************************************************/
//* @file  :StandardStage.cpp
//* @brief :ギミックの無いステージ
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#include "StandardStage.h"
#include <SL_Colors.h>
#include "StageObject.h"
#include "../ObjectFactory.h"
#include "../UnitSummoner/UnitSummoner.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// 初期化
/// </summary>
void StandardStage::Initialize()
{
	//障害物の設置
	SettingObstacle();

	//オブジェクトの設置
	SettingBlueObject();
	SettingRedObject();
}

/// <summary>
/// 終了
/// </summary>
void StandardStage::Finalize()
{
}

/// <summary>
/// 障害物の設置
/// </summary>
void StandardStage::SettingObstacle()
{
	//ステージ枠の設置
	SettingFrameOfStage();

	//壁の設置
	SettingWall();
}

/// <summary>
/// 青チームの設置
/// </summary>
void StandardStage::SettingBlueObject()
{
	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();

	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//所属チーム
	ObjectConstantNumber::TEAM team = ObjectConstantNumber::BLUE;

	//プレイヤー作成
	//プレイヤーは青チーム
	auto p = factory->CreateObject(ObjectConstantNumber::PLAYER);
	camera->FollowTarget(p);
	camera->ChangeMode(FOLLOW_CAMERA);
	p->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 35.0f));
	p->Data().Team(team);
	p->SetParent(this);

	//ユニット召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 30.0f));
	summoner->Data().Team(team);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(1000);
	summoner->SetParent(this);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 40.0f));
	target->Data().Team(team);
	target->SetParent(this);

}

/// <summary>
/// 赤チームの設置
/// </summary>
void StandardStage::SettingRedObject()
{
	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//所属チーム
	ObjectConstantNumber::TEAM team = ObjectConstantNumber::RED;

	//召喚オブジェクト
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, -30.0f));
	summoner->Data().Team(team);
	summoner->SetParent(this);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(2000);

	//防衛対象
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, -40.0f));
	target->Data().Team(team);
	target->SetParent(this);
}

/// <summary>
/// 壁の設置
/// </summary>
void StandardStage::SettingWall()
{
	auto factory = ObjectFactory::GetInstance();

	//壁
	auto obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(10.0f, 4.0f, 1.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);

	this->AddChild(obj);

	//壁
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(20.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 4.0f, 10.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);
	this->AddChild(obj);

	//壁
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(-20.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(10.0f, 4.0f, 1.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);
	this->AddChild(obj);

}

/// <summary>
/// ステージ枠の設置
/// </summary>
void StandardStage::SettingFrameOfStage()
{
	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	//地面
	ObjectBase* obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, -1.0f, 0.0f));
	obj->Transform().Scale(Vec3(100.0f, 1.0f, 100.0f));
	this->AddChild(obj);

	//ステージ枠 右
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(49.0f, 5.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 10.0f, 100.0f));
	this->AddChild(obj);

	//ステージ枠 左
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(-49.0f, 5.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 10.0f, 100.0f));
	this->AddChild(obj);

	//ステージ枠 奥
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 5.0f, 49.0f));
	obj->Transform().Scale(Vec3(100.0f, 10.0f, 1.0f));
	this->AddChild(obj);

	//ステージ枠 手前
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 5.0f, -49.0f));
	obj->Transform().Scale(Vec3(100.0f, 10.0f, 1.0f));
	this->AddChild(obj);
}
