//************************************************/
//* @file  :Visitor.h
//* @brief :ビジターまとめ
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once

#include <vector>
#include <SL_Visitor.h>
#include <SL_Math.h>
#include "../../Object/ObjectConstantNumber.h"

#include "../../Object/Unit/Unit.h"

/// <summary>
/// ユニットを探すビジター
/// </summary>
class SearchUnitVisitor : public ShunLib::Visitor
{
private:
	std::vector<Unit*> m_unitList;

public:
	SearchUnitVisitor(){}
	~SearchUnitVisitor() {}

	void Visit(ShunLib::VisitorNode* node)override;

	void Accept(Visitor* visitor) override{
		for (auto& v : m_unitList){
			v->Accept(visitor);
		}
	};

	void Reset()override { 
		m_unitList.clear();
		m_unitList.shrink_to_fit();
	}

	/*--Getter--*/
	int Count() { return m_unitList.size(); }
	std::vector<Unit*>& List() { return m_unitList; }
};


/// <summary>
/// 状態を使用するオブジェクトを探すビジター
/// </summary>
class SearchStateObjectVisitor : public ShunLib::Visitor
{
private:
	std::vector<ObjectBase*> m_objectList;

public:
	SearchStateObjectVisitor() {}
	~SearchStateObjectVisitor() {}

	void Visit(ShunLib::VisitorNode* node)override;

	void Accept(Visitor* visitor) override {
		for (auto& v : m_objectList) {
			v->Accept(visitor);
		}
	};

	void Reset() override {
		m_objectList.clear();
		m_objectList.shrink_to_fit();
	}

	/*--Getter--*/
	int Count() { return m_objectList.size(); }
	std::vector<ObjectBase*>& List() { return m_objectList; }
};


/// <summary>
/// 別のチームを探すビジター
/// </summary>
class SearchAnotherTeamVisitor : public ShunLib::Visitor
{
public:
	using TEAM = ObjectConstantNumber::TEAM;

private:
	TEAM m_myTeam;
	std::vector<ObjectBase*> m_objectList;

public:
	SearchAnotherTeamVisitor(TEAM team) :
		m_myTeam(team)
	{}
	~SearchAnotherTeamVisitor() {}

	void Visit(ShunLib::VisitorNode* node)override;

	void Accept(Visitor* visitor)override {
		for (auto& v : m_objectList) {
			v->Accept(visitor);
		}
	};

	void Reset() override {
		m_objectList.clear();
		m_objectList.shrink_to_fit();
	}

	/*--Getter--*/
	int Count() { return m_objectList.size(); }
	std::vector<ObjectBase*>& List() { return m_objectList; }
};


/// <summary>
/// 特定のオブジェクトを探すビジター
/// </summary>
class SearchSpecificObjectVisitor : public ShunLib::Visitor
{
private:
	ObjectBase* m_target; //探す対象
	ObjectBase* m_object; //

public:
	SearchSpecificObjectVisitor(ObjectBase* obj):
		m_target(obj),
		m_object(nullptr)
	{}
	~SearchSpecificObjectVisitor() {}


	void Visit(ShunLib::VisitorNode* node)override;

	void Accept(Visitor* visitor)override {
		if (IsFound()){
			m_object->Accept(visitor);
		}
	};

	void Reset() override {
		m_object = nullptr;
	}

	/*--Getter--*/
	bool IsFound() { return m_object != nullptr; }
	ObjectBase* Object() { return m_object; }
};


/// <summary>
/// 最も近い位置にいるオブジェクトを探すビジター
/// </summary>
class SearchNearestObjectVisitor :public ShunLib::Visitor
{
private:
	ShunLib::Vec3 m_pos;  //基準の位置
	bool m_isOnlyState;	  //状態を持ったオブジェクトに限定するかどうか
	
	ObjectBase* m_object; //最も近いオブジェクト
	float m_minDist;      //最短距離

public:
	SearchNearestObjectVisitor(const ShunLib::Vec3& pos, bool onlyState = true) :
		m_pos(pos),	m_isOnlyState(onlyState),m_object(nullptr),m_minDist(9999.9999f){}
	~SearchNearestObjectVisitor() {}


	void Visit(ShunLib::VisitorNode* node)override;

	void Accept(Visitor* visitor) override {
		if (IsFound()) {
			m_object->Accept(visitor);
		}
	};

	void Reset() override {
		m_object = nullptr;
		m_minDist = 9999.9999f;
	}

	/*--Getter--*/
	bool IsFound() { return m_object != nullptr; }
	ObjectBase* Object() { return m_object; }
	ShunLib::Vec3 TargetPos();
};