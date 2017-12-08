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
/// オブジェクトが状態を持っているかどうか
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
bool IsStateObject(ObjectBase* obj)
{
	for (auto& v : ObjectConstantNumber::STATE_OBJECT) {
		if (obj->Type() == v) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// ユニットを探すビジター
/// </summary>
void SearchUnitVisitor::Visit(ShunLib::VisitorNode * node)
{
	Unit* unit = dynamic_cast<Unit*>(node);

	//ユニットならカウント
	if (unit != nullptr) {
		m_unitList.push_back(unit);
	}
}

/// <summary>
/// 状態を持つオブジェクトを探すビジター
/// </summary>
void SearchStateObjectVisitor::Visit(ShunLib::VisitorNode* node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {

		//状態を持っているオブジェクトならカウント
		if (IsStateObject(obj)) {
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
		//チームに所属していて
		//指定チームではないならカウントする
		if (obj->Team() != ObjectConstantNumber::NONE && obj->Team() != m_myTeam) {
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


/// <summary>
/// 最も近い位置にあるオブジェクトを探す
/// </summary>
void SearchNearestObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {
		//条件指定なし or 状態を持つオブジェクトの場合
		//距離を確認する
		if (!(m_isOnlyState && !IsStateObject(obj))) {
			ShunLib::Vec3 dist = m_pos - obj->WorldPos();

			if (m_minDist > dist.Length()) {
				//最短距離の更新
				m_minDist = dist.Length();
				m_object = obj;
			}
		}
	}
}

/// <summary>
/// ターゲットの位置を返す
/// </summary>
ShunLib::Vec3 SearchNearestObjectVisitor::TargetPos()
{
	ShunLib::Vec3 pos = ShunLib::Vec3::Zero;
	if (IsFound()) {
		pos = m_object->WorldPos();
	}

	return pos;
}
