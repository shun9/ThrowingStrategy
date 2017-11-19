//************************************************/
//* @file  :ObjectBase.h
//* @brief :オブジェクトの基底クラス
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <SL_Math.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"

class ObjectBase : public ObjectData
{
private:
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
	//子用
	ObjectBase() :m_parent(nullptr) {
		ROOT_OBJECT->AddChild(this);
	}

	//ルート用
	//引数は何でもよい
	ObjectBase(bool dummy):m_parent(nullptr) {
	}

	virtual ~ObjectBase() {}

	//親を設定
	void SetParent(ObjectBase* parent);

	//子を追加
	void AddChild(ObjectBase* child) { 
		m_children.push_back(child); 
		child->SetParent(this);
	}

	//指定されたオブジェクトが子にいるかどうか
	bool HasChild(const ObjectBase* obj) {

		//直接の子に存在する
		if (std::find(m_children.begin(), m_children.end(), obj) != m_children.end()) {
			return true;
		}

		//子の子に存在する
		for (auto& v : m_children){
			if (v->HasChild(obj)){
				return true;
			}
		}

		return false;
	}
	
	//指定された種類のオブジェクトが子にいるかどうか
	//第二引数でそのオブジェクトを返す
	bool HasChild(OBJECT_LIST type,ObjectBase** buff = nullptr) {
		auto c = std::find_if(m_children.begin(), m_children.end(),[=](ObjectBase* child) { return (child->Type() == type); });
		if (c != m_children.end())
		{
			if (buff != nullptr)*buff = (*c);
			return true;
		}
		return false;
	}

	//子を削除
	void RemoveChild(ObjectBase* child);

	//移動させる
	void Move();

	//描画 上:ルート用　下:子用
	void Render(const Matrix& view, const Matrix& proj);
	void Render(const Matrix& parentWorld, const Matrix& view, const Matrix& proj);

	//初期化 更新  派生クラスの最後に呼ぶ
	virtual void Initialize() {	for (auto& v : m_children) { v->Initialize(); }}
	virtual void Update() { 
		//更新中の変更によってアクセス違反が起こるため
		//コンテナのサイズで回す
		for (int i = 0;i < (int)m_children.size();i++){
			m_children.at(i)->Update(); 
		} 
	}
	
	//終了  派生クラスの最後に呼ぶ
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }

	//ローカル座標系
	ShunLib::Vec3 LocalPos() { return this->Pos(); }
	void LocalPos(const ShunLib::Vec3& pos) { this->Pos(pos); }
	
	//ワールド座標系
	ShunLib::Vec3 WorldPos() {
		ShunLib::Vec3 pos = this->Pos();
		if (m_parent != nullptr) {
			pos += m_parent->WorldPos();
		}
		return pos;
	}

	ObjectBase* Parent() { return m_parent; }
	const std::vector<ObjectBase*>& Children() { return m_children; }

protected:
	//自身の行列を計算する
	Matrix CalcMat();
};