//************************************************/
//* @file  :Node.h
//* @brief :親子関係を持つノード
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>

namespace ShunLib
{
	class Node
	{
	protected:
		//親
		Node* m_parent;

		//子の一覧
		std::vector<Node*> m_children;

	public:
		Node(int childrenSize = 100);
		virtual ~Node() {}

		//親設定
		virtual bool SetParent(Node* parent);

		//子の追加
		virtual bool AddChild(Node* child);

		//子の切り離し
		virtual bool RemoveChild(Node* child);

		/*--Getter--*/
		Node* Parent() { return m_parent; }
		std::vector<Node*>& Children() { return m_children; }
	};
}