//************************************************/
//* @file  :ObjectBase.h
//* @brief :オブジェクトの基底クラス
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <SL_Math.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"

class ObjectBase : public ObjectData
{
private:
	using Matrix = ShunLib::Matrix;

private:
	//子オブジェクト
	std::vector<ObjectBase*>m_children;

	//親オブジェクト
	ObjectBase* m_parent;

public:
	ObjectBase():
		m_parent(nullptr)
	{}
	virtual ~ObjectBase() {}

	//親を設定
	void SetParent(ObjectBase* parent) {
		m_parent = parent;
	}

	//子を追加
	void AddChild(ObjectBase* child) { 
		m_children.push_back(child); 
		child->SetParent(this);
	}

	//子を削除
	void RemoveChild(ObjectBase* child){
		auto tmpChild = std::find(m_children.begin(), m_children.end(), child);
		if (tmpChild != m_children.end()) {
			m_children.erase(tmpChild);
			child->SetParent(this);
		}
	}

	//移動させる
	void Move();

	//描画 上:ルート用　下:子用
	void Render(const Matrix& view, const Matrix& proj);
	void Render(const Matrix& parentWorld, const Matrix& view, const Matrix& proj);

	//初期化 更新  派生クラスの最後に呼ぶ
	virtual void Initialize() {	for (auto& v : m_children) { v->Initialize(); }}
	virtual void Update() { for (auto& v : m_children) { v->Update(); } }
	
	//終了  派生クラスの最後に呼ぶ
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }
};