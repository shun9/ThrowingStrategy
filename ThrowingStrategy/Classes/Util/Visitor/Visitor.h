//************************************************/
//* @file  :Visitor.h
//* @brief :�r�W�^�[�܂Ƃ�
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
/// ���j�b�g��T���r�W�^�[
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
/// ��Ԃ��g�p����I�u�W�F�N�g��T���r�W�^�[
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
/// �ʂ̃`�[����T���r�W�^�[
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
/// ����̃I�u�W�F�N�g��T���r�W�^�[
/// </summary>
class SearchSpecificObjectVisitor : public ShunLib::Visitor
{
private:
	ObjectBase* m_target; //�T���Ώ�
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
/// �ł��߂��ʒu�ɂ���I�u�W�F�N�g��T���r�W�^�[
/// </summary>
class SearchNearestObjectVisitor :public ShunLib::Visitor
{
private:
	ShunLib::Vec3 m_pos;  //��̈ʒu
	bool m_isOnlyState;	  //��Ԃ��������I�u�W�F�N�g�Ɍ��肷�邩�ǂ���
	
	ObjectBase* m_object; //�ł��߂��I�u�W�F�N�g
	float m_minDist;      //�ŒZ����

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