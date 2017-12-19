//************************************************/
//* @file  :ObjectBase.h
//* @brief :オブジェクトの基底クラス
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <SL_Math.h>
#include <SL_Model.h>
#include <SL_Visitor.h>
#include "ObjectConstantNumber.h"
#include "ObjectFactory.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"
#include "ObjectTransform.h"

class ObjectBase : public ObjectData , public ShunLib::VisitorNode,public ObjectTransform
{
public:
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;

public:
	//全てのオブジェクトの親
	//全てのオブジェクトをここに紐づける
	static ObjectBase* ROOT_OBJECT;
public:
	static void InitializeRootObject();
	static void FinalizeRootObject();

private:
	//子オブジェクト
	std::vector<ObjectBase*>m_children;

	//親オブジェクト
	ObjectBase* m_parent;

public:
	//コンストラクタ　子用
	ObjectBase(OBJECT_LIST type) :
		ObjectData(type),
		m_parent(nullptr) {
		ROOT_OBJECT->AddChild(this);
	}

	//コンストラクタ　ルート用
	ObjectBase():
		ObjectData(OBJECT_LIST::ROOT),
		m_parent(nullptr) {
	}

	//デストラクタ
	virtual ~ObjectBase();

	//親を設定
	void SetParent(ObjectBase* parent);

	//子を追加
	void AddChild(ObjectBase* child);

	//子を削除
	void RemoveChild(ObjectBase* child);

	//移動させる
	void Move();

	//描画 上:ルート用　下:子用
	void Render(const Matrix& view, const Matrix& proj);
	void RenderChild(const Matrix& view, const Matrix& proj);

	//初期化 派生クラスの最後に呼ぶ
	virtual void Initialize() {
		//初期化中の変更によってアクセス違反が起こるため
		//コンテナのサイズで回す
		for (int i = 0; i < (int)(m_children.size()); i++){
			m_children.at(i)->Initialize();
		}
	}

	//更新
	virtual void Update();

	//終了  派生クラスの最後に呼ぶ
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }

	//ビジター受け入れ
	void Accept(ShunLib::Visitor* visitor);

	//ローカル座標系
	Vec3 LocalPos() { return this->Pos(); }
	void LocalPos(const Vec3& pos) { this->Pos(pos); }

	//ワールド座標系
	Vec3 WorldPos() {
		Vec3 pos = this->Pos();
		if (m_parent != nullptr) {
			pos += m_parent->WorldPos();
		}
		return pos;
	}

	//ワールド拡大率
	Vec3 WorldScale() {
		Vec3 scale = this->Scale();
		if (m_parent != nullptr) {
			scale.m_x *= m_parent->WorldScale().m_x;
			scale.m_y *= m_parent->WorldScale().m_y;
			scale.m_z *= m_parent->WorldScale().m_z;
		}
		return scale;
	}

	//ワールド回転率
	Vec3 WorldRotation() {
		Vec3 rot = this->Rotation();
		if (m_parent != nullptr) {
			rot += m_parent->WorldRotation();
		}
		return rot;
	}

	//親子関係
	ObjectBase* Parent() { return m_parent; }
	const std::vector<ObjectBase*>& Children() { return m_children; }


protected:
	//自身の行列を計算する
	void CalcMat();
};