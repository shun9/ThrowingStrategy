//************************************************/
//* @file  :ObjectNode.cpp
//* @brief :親子関係を持った3Dオブジェクトのノード
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#include "SL_ObjectNode.h"
#include <SL_ObjectHolder.h>

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
ObjectNode::ObjectNode(int layerNumber):
	m_layerNumber(layerNumber)
{
	//オブジェクト管理クラスに追加
	ObjectHolder::GetInstance()->AddObject(m_layerNumber, this);
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectNode::~ObjectNode()
{
	//オブジェクト管理クラスから除外
	ObjectHolder::GetInstance()->RemoveObject(m_layerNumber, this);
}

/// <summary>
/// 親の設定
/// </summary>
bool ObjectNode::SetParent(Node* parent)
{
	//親を設定できなければ何もしない
	if (!Node::SetParent(parent)) {
		return false;
	}

	//親が3Dオブジェクトならば位置を追従する
	ObjectNode* obj = dynamic_cast<ObjectNode*>(parent);
	if (obj != nullptr){
		LocalPos(LocalPos() - obj->WorldPos());
	}
	return true;
}

/// <summary>
/// 子の追加
/// </summary>
bool ObjectNode::AddChild(Node* child)
{
	//子の追加が出来なければ何もしない
	if (!Node::AddChild(child)) {
		return false;
	}

	//子が3Dオブジェクトならば位置を追従させる
	ObjectNode* obj = dynamic_cast<ObjectNode*>(child);
	if (obj != nullptr) {
		obj->LocalPos(obj->LocalPos() - WorldPos());
	}

	return true;
}

/// <summary>
/// 子の切り離し
/// </summary>
bool ObjectNode::RemoveChild(Node* child)
{
	//子の切り離しが出来なければ何もしない
	if (!Node::RemoveChild(child)) {
		return false;
	}

	//子が3Dオブジェクトならば位置を追従させる
	ObjectNode* obj = dynamic_cast<ObjectNode*>(child);
	if (obj != nullptr) {
		obj->LocalPos(obj->LocalPos() + WorldPos());
	}

	return true;
}

/// <summary>
/// ワールド座標の取得
/// </summary>
const Vec3 ShunLib::ObjectNode::WorldPos() const
{
	//現在位置
	Vec3 pos = m_transform.Pos();

	//親が存在するかどうか
	ObjectNode* parent = dynamic_cast<ObjectNode*>(m_parent);

	//親が存在するなら位置を影響させる
	if (parent != nullptr && parent->IsEnable()){
		pos += parent->WorldPos();
	}

	return pos;
}
