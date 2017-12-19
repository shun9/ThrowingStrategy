//************************************************/
//* @file  :Node.h
//* @brief :�e�q�֌W�����m�[�h
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
		//�e
		Node* m_parent;

		//�q�̈ꗗ
		std::vector<Node*> m_children;

	public:
		Node(int childrenSize = 100);
		virtual ~Node() {}

		//�e�ݒ�
		virtual bool SetParent(Node* parent);

		//�q�̒ǉ�
		virtual bool AddChild(Node* child);

		//�q�̐؂藣��
		virtual bool RemoveChild(Node* child);

		/*--Getter--*/
		Node* Parent() { return m_parent; }
		std::vector<Node*>& Children() { return m_children; }
	};
}