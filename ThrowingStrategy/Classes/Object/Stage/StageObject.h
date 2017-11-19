//************************************************/
//* @file  :StageObject.h
//* @brief :ステージに配置するオブジェクトのまとめ
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include "../ObjectBase.h"
#include "../../Physics/Collision/SL_Collider.h"

//箱
class Block : public ObjectBase
{
private:
	ShunLib::BoxCollider* m_collider;

public:
	Block();
	~Block();
};
