//************************************************/
//* @file  :Stage.cpp
//* @brief :ステージの基底クラスと設置するオブジェクト
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "Stage.h"
#include "StageObject.h"
#include "../ObjectFactory.h"

Stage::Stage()
{
	this->Type(STAGE);
}

Stage::~Stage()
{

}

void Stage::SetStageType(STAGE_LIST type)
{
	auto factory = ObjectFactory::GetInstance();
	ObjectBase* b = factory->Create(OBJECT_LIST::BLOCK);
	b->Pos(ShunLib::Vec3(0.0f, -1.0f, 0.0f));
	b->Scale(ShunLib::Vec3(100.0f, 1.0f, 100.0f));

	this->AddChild(b);
}
