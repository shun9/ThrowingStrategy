//************************************************/
//* @file  :Visitor.cpp
//* @brief :ビジターまとめ
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "Visitor.h"

#include <algorithm>
#include "../../Object/Unit/Unit.h"

/// <summary>
/// ユニットを探すビジター
/// </summary>
void SearchUnitVisitor::Visit(ShunLib::VisitorNode * node)
{
	Unit* unit = dynamic_cast<Unit*>(node);

	//ユニットならカウント
	if (unit != nullptr){
		m_unitCnt++;
		m_unitList.push_back(unit);
	}
}

/// <summary>
/// 状態を持つオブジェクトを探すビジター
/// </summary>
void SearchStateObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr){

		//状態を持ったオブジェクト一覧
		const std::vector<OBJECT_LIST> STATE_OBJECT{
			PLAYER,
			COMMANDER,
			UNIT,
			SUMMONER,
		};

		//オブジェクトの種類を探す
		auto result = std::find(STATE_OBJECT.begin(), STATE_OBJECT.end(), obj->Type());
	
		//状態を持っているオブジェクトならカウント
		if (result != STATE_OBJECT.end()){
			m_objectCnt++;
			m_objectList.push_back(obj);
		}
	}
}


/// <summary>
/// 違うチームのオブジェクトを探すビジター
/// </summary>
void SearchAnotherTeamVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {
		TEAM objTeam = obj->Team();

		//チームに所属していて
		//指定チームではないならカウントする
		if (objTeam != NONE && objTeam != m_myTeam){
			m_objectCnt++;
			m_objectList.push_back(obj);
		}
	}
}

/// <summary>
/// 特定のオブジェクトを探すビジター
/// </summary>
void SearchSpecificObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	//同じならカウント
	if (node == m_target) {
		ObjectBase* obj = dynamic_cast<ObjectBase*>(node);
		m_object = obj;
	}
}
