//************************************************/
//* @file  :ObjectNode.cpp
//* @brief :�e�q�֌W��������3D�I�u�W�F�N�g�̃m�[�h
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#include "SL_ObjectNode.h"
#include <SL_ObjectHolder.h>

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectNode::ObjectNode(int layerNumber):
	m_layerNumber(layerNumber)
{
	//�I�u�W�F�N�g�Ǘ��N���X�ɒǉ�
	ObjectHolder::GetInstance()->AddObject(m_layerNumber, this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectNode::~ObjectNode()
{
	//�I�u�W�F�N�g�Ǘ��N���X���珜�O
	ObjectHolder::GetInstance()->RemoveObject(m_layerNumber, this);
}

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

/// <summary>
/// ���[���h���W�̎擾
/// </summary>
const Vec3 ShunLib::ObjectNode::WorldPos() const
{
	//���݈ʒu
	Vec3 pos = m_transform.Pos();

	//�e�����݂��邩�ǂ���
	ObjectNode* parent = dynamic_cast<ObjectNode*>(m_parent);

	//�e�����݂���Ȃ�ʒu���e��������
	if (parent != nullptr && parent->IsEnable()){
		pos += parent->WorldPos();
	}

	return pos;
}
