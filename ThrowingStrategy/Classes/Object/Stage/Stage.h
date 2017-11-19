//************************************************/
//* @file  :Stage.h
//* @brief :ステージの基底クラスと設置するオブジェクト
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
	Stage();
	virtual ~Stage();

	void SetStageType(STAGE_LIST type);
};

