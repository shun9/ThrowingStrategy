//************************************************/
//* @file  :Stage.cpp
//* @brief :ステージの基底クラスと設置するオブジェクト
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#include "Stage.h"
#include "StageObject.h"
#include "../ObjectFactory.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="type">ステージの種類</param>
Stage::Stage(STAGE_TYPE type):
	m_stageType(type),
	ObjectBase(OBJECT_LIST::STAGE)
{

}

Stage::~Stage()
{

}