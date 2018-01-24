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
	ShunLib::Vec4 m_color;

public:
	Block();
	~Block();

	//色の設定
	void SetColor(const ShunLib::Vec4& color) { m_color = color; }

protected:
	//初期化 更新 描画 終了
	void Initialize()override {};
	void Update    ()override {};
	void Render    ()override;
	void Finalize  ()override {};
};
