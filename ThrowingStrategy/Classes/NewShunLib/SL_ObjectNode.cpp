//************************************************/
//* @file  :ObjectNode.cpp
//* @brief :親子関係を持った3Dオブジェクトのノード
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_ObjectNode.h"

using namespace ShunLib;

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
