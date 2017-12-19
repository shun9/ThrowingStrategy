//************************************************/
//* @file  :Node.cpp
//* @brief :親子関係を持つノード
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_Node.h"

#include <algorithm>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="childrenSize">最初に確保する子の一覧サイズ</param>
ShunLib::Node::Node(int childrenSize):
	m_parent(nullptr)
{
	//この領域をあらかじめ確保
	m_children.reserve(childrenSize);
}

/// <summary>
/// 親の設定
/// </summary>
/// <param name="parent">親</param>
/// <returns>設定出来たらtrue</returns>
bool ShunLib::Node::SetParent(Node* parent)
{
	//親が変化しないなら何もしない
	if (m_parent == parent){
		return false;
	}

	//別の親が存在しているとき
	if (m_parent != nullptr) {
		m_parent->RemoveChild(this);
	}

	//親を設定
	m_parent = parent;

	return true;
}

/// <summary>
/// 子の追加
/// </summary>
/// <param name="child">子</param>
/// <returns>追加出来たらtrue</returns>
bool ShunLib::Node::AddChild(Node* child)
{
	//既に自分の子ならば何もしない
	if (child->Parent() == this){
		return false;
	}

	//子を追加　親を自身に設定
	m_children.push_back(child);
	child->SetParent(this);
	return true;
}

/// <summary>
/// 子の切り離し
/// </summary>
/// <param name="child">子</param>
/// <returns>切り離しに成功したらtrue</returns>
bool ShunLib::Node::RemoveChild(Node* child)
{
	//自身の子ではないなら何もしない
	if (child->Parent() != this){
		return false;
	}

	//一覧の中から子を探す
	std::vector<Node*>::iterator itr = std::find(m_children.begin(), m_children.end(), child);

	//子が存在したなら切り離す
	if (itr != m_children.end()){
		m_children.erase(itr);
	}

	return true;
}
