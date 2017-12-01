//************************************************/
//* @file  :Visitor.h
//* @brief :ビジターまとめ
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#pragma once

#include <vector>
#include <SL_Visitor.h>
#include "../../Object/ObjectConstantNumber.h"

class Unit;
class ObjectBase;

/// <summary>
/// ユニットを探すビジター
/// </summary>
class SearchUnitVisitor : public ShunLib::Visitor
{
private:
	int m_unitCnt;
	std::vector<Unit*> m_unitList;

public:
	SearchUnitVisitor():m_unitCnt(0) {}
	~SearchUnitVisitor() {}

	void Visit(ShunLib::VisitorNode* node);

	/*--Getter--*/
	int Count() { return m_unitCnt; }
	std::vector<Unit*>& List() { return m_unitList; }
};

/// <summary>
/// 状態を使用するオブジェクトを探すビジター
/// </summary>
class SearchStateObjectVisitor : public ShunLib::Visitor
{
private:
	int m_objectCnt;
	std::vector<ObjectBase*> m_objectList;

public:
	SearchStateObjectVisitor() :m_objectCnt(0) {}
	~SearchStateObjectVisitor() {}

	void Visit(ShunLib::VisitorNode* node);

	/*--Getter--*/
	int Count() { return m_objectCnt; }
	std::vector<ObjectBase*>& List() { return m_objectList; }
};


/// <summary>
/// 別のチームを探すビジター
/// </summary>
class SearchAnotherTeamVisitor : public ShunLib::Visitor
{
private:
	TEAM m_myTeam;
	int m_objectCnt;
	std::vector<ObjectBase*> m_objectList;

public:
	SearchAnotherTeamVisitor(TEAM team) :
		m_objectCnt(0),
		m_myTeam(team)
	{}
	~SearchAnotherTeamVisitor() {}

	void Visit(ShunLib::VisitorNode* node);

	/*--Getter--*/
	int Count() { return m_objectCnt; }
	std::vector<ObjectBase*>& List() { return m_objectList; }
};


/// <summary>
/// 特定のオブジェクトを探すビジター
/// </summary>
class SearchSpecificObjectVisitor : public ShunLib::Visitor
{
private:
	ObjectBase* m_target;
	int m_objectCnt;
	std::vector<ObjectBase*> m_objectList;

public:
	SearchSpecificObjectVisitor(ObjectBase* obj):
		m_target(obj),
		m_objectCnt(0)
	{}
	~SearchSpecificObjectVisitor() {}


	void Visit(ShunLib::VisitorNode* node);

	/*--Getter--*/
	bool IsFound() { return !(m_objectList.empty()); }
	int Count() { return m_objectCnt; }
	std::vector<ObjectBase*>& List() { return m_objectList; }
};