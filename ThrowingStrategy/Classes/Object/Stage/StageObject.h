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

protected:
	//初期化 更新 描画 終了
	void Initialize()override {};
	void Update    ()override {};
	void Finalize  ()override {};

};
