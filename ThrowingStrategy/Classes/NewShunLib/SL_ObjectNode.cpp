//************************************************/
//* @file  :ObjectNode.cpp
//* @brief :�e�q�֌W��������3D�I�u�W�F�N�g�̃m�[�h
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_ObjectNode.h"

using namespace ShunLib;

/// <summary>
/// �e�̐ݒ�
/// </summary>
bool ObjectNode::SetParent(Node* parent)
{
	//�e��ݒ�ł��Ȃ���Ή������Ȃ�
	if (!Node::SetParent(parent)) {
		return false;
	}

	//�e��3D�I�u�W�F�N�g�Ȃ�Έʒu��Ǐ]����
	ObjectNode* obj = dynamic_cast<ObjectNode*>(parent);
	if (obj != nullptr){
		LocalPos(LocalPos() - obj->WorldPos());
	}
	return true;
}

/// <summary>
/// �q�̒ǉ�
/// </summary>
bool ObjectNode::AddChild(Node* child)
{
	//�q�̒ǉ����o���Ȃ���Ή������Ȃ�
	if (!Node::AddChild(child)) {
		return false;
	}

	//�q��3D�I�u�W�F�N�g�Ȃ�Έʒu��Ǐ]������
	ObjectNode* obj = dynamic_cast<ObjectNode*>(child);
	if (obj != nullptr) {
		obj->LocalPos(obj->LocalPos() - WorldPos());
	}

	return true;
}

/// <summary>
/// �q�̐؂藣��
/// </summary>
bool ObjectNode::RemoveChild(Node* child)
{
	//�q�̐؂藣�����o���Ȃ���Ή������Ȃ�
	if (!Node::RemoveChild(child)) {
		return false;
	}

	//�q��3D�I�u�W�F�N�g�Ȃ�Έʒu��Ǐ]������
	ObjectNode* obj = dynamic_cast<ObjectNode*>(child);
	if (obj != nullptr) {
		obj->LocalPos(obj->LocalPos() + WorldPos());
	}

	return true;
}
