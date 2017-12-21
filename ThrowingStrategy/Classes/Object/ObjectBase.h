//************************************************/
//* @file  :ObjectBase.h
//* @brief :ゲームオブジェクトの基底クラス
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#pragma once
#include "../NewShunLib/SL_ObjectNode.h"
#include "ObjectConstantNumber.h"
#include "ObjectData.h"

class ObjectBase : public ShunLib::ObjectNode
{
public:
	using OBJECT_LIST = ObjectConstantNumber::OBJECT_LIST;

protected:
	//オブジェクトのゲーム用データ
	ObjectData m_data;

public:
	//コンストラクタ
	//オブジェクトの種類を渡す
	ObjectBase(OBJECT_LIST type);

	//デストラクタ
	virtual ~ObjectBase();

	//移動させる
	void Move();

	/*--Getter & Setter--*/
	ObjectData& Data() { return m_data; }

protected:
	//初期化 更新 描画 終了
	//描画のみ共通処理
	virtual void Initialize()override = 0;
	virtual void Update    ()override = 0;
	virtual void Render    ()override;
	virtual void Finalize  ()override = 0;
};