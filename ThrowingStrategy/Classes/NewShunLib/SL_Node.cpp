//************************************************/
//* @file  :Node.cpp
//* @brief :�e�q�֌W�����m�[�h
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_Node.h"

#include <algorithm>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="childrenSize">�ŏ��Ɋm�ۂ���q�̈ꗗ�T�C�Y</param>
ShunLib::Node::Node(int childrenSize):
	m_parent(nullptr)
{
	//���̗̈�����炩���ߊm��
	m_children.reserve(childrenSize);
}

/// <summary>
/// �e�̐ݒ�
/// </summary>
/// <param name="parent">�e</param>
/// <returns>�ݒ�o������true</returns>
bool ShunLib::Node::SetParent(Node* parent)
{
	//�e���ω����Ȃ��Ȃ牽�����Ȃ�
	if (m_parent == parent){
		return false;
	}

	//�ʂ̐e�����݂��Ă���Ƃ�
	if (m_parent != nullptr) {
		m_parent->RemoveChild(this);
	}

	//�e��ݒ�
	m_parent = parent;

	return true;
}

/// <summary>
/// �q�̒ǉ�
/// </summary>
/// <param name="child">�q</param>
/// <returns>�ǉ��o������true</returns>
bool ShunLib::Node::AddChild(Node* child)
{
	//���Ɏ����̎q�Ȃ�Ή������Ȃ�
	if (child->Parent() == this){
		return false;
	}

	//�q��ǉ��@�e�����g�ɐݒ�
	m_children.push_back(child);
	child->SetParent(this);
	return true;
}

/// <summary>
/// �q�̐؂藣��
/// </summary>
/// <param name="child">�q</param>
/// <returns>�؂藣���ɐ���������true</returns>
bool ShunLib::Node::RemoveChild(Node* child)
{
	//���g�̎q�ł͂Ȃ��Ȃ牽�����Ȃ�
	if (child->Parent() != this){
		return false;
	}

	//�ꗗ�̒�����q��T��
	std::vector<Node*>::iterator itr = std::find(m_children.begin(), m_children.end(), child);

	//�q�����݂����Ȃ�؂藣��
	if (itr != m_children.end()){
		m_children.erase(itr);
	}

	return true;
}
