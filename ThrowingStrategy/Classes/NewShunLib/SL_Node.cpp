//************************************************/
//* @file  :Node.cpp
//* @brief :�e�q�֌W�����m�[�h
//* @date  :2017/12/26
//* @author:S.Katou
//************************************************/
#include "SL_Node.h"
#include <algorithm>
#include <SL_MacroConstants.h>

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="childrenSize">�ŏ��Ɋm�ۂ���q�̈ꗗ�T�C�Y</param>
Node::Node(int childrenSize):
	m_parent(nullptr)
{
	//�q�̗̈�����炩���ߊm��
	m_children.reserve(childrenSize);

	//�_�[�e�B�[�t���O�����낷
	ClearDirty();

	//�g�p���Ă����Ԃɂ��Ă���
	m_isEnable = true;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Node::~Node()
{
	//�q�������ɏ���
	for (int i = 0; i < (int)m_children.size(); i++){
		SAFE_DELETE(m_children[i]);
	}
}

/// <summary>
/// ���̏�����
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void Node::BaseInitialize()
{
	//�g�p���Ă��Ȃ���ԂȂ�t���O��߂�
	if (!m_isEnable) {
		ClearDirty();
	}

	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG]){
		//����������
		Initialize();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG] = true;

		//�g�p���Ă���
		m_isEnable = true;

		//�q�̏��������s��
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseInitialize();
		}
	}
}

/// <summary>
/// ���̍X�V
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void Node::BaseUpdate()
{
	//�g�p���Ă��Ȃ���ԂȂ牽�����Ȃ�
	if (!IsEnable()) {
		return;
	}

	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::UPDATE_FLAG]){
		//�X�V����
		Update();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::UPDATE_FLAG] = true;

		//�`��\�ɂ���
		EnableRender();

		//�q�̍X�V���s��
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseUpdate();
		}
	}
}

/// <summary>
/// ���̕`��
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void Node::BaseRender()
{
	//�g�p���Ă��Ȃ���ԂȂ牽�����Ȃ�
	if (!IsEnable()){
		return;
	}

	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::RENDER_FLAG]){
		//�`�揈��
		Render();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::RENDER_FLAG] = true;

		//�X�V�\�ɂ���
		EnableUpdate();

		//�q�̕`����s��
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseRender();
		}
	}
}

/// <summary>
/// ���̏I��
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void Node::BaseFinalize()
{
	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::FINALIZE_FLAG]){
		//�I������
		Finalize();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::FINALIZE_FLAG] = true;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_isEnable = false;

		//�q�̏I�����s��
		for (int i = 0; i < (int)m_children.size(); i++){
			m_children[i]->BaseFinalize();
		}
	}
}

/// <summary>
/// �e�̐ݒ�
/// </summary>
/// <param name="parent">�e</param>
/// <returns>�ݒ�o������true</returns>
bool Node::SetParent(Node* parent)
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
	parent->m_children.push_back(this);

	return true;
}

/// <summary>
/// �q�̒ǉ�
/// </summary>
/// <param name="child">�q</param>
/// <returns>�ǉ��o������true</returns>
bool Node::AddChild(Node* child)
{
	//���Ɏ����̎q�Ȃ�Ή������Ȃ�
	if (child->Parent() == this){
		return false;
	}

	//�ʂ̐e�����݂����Ȃ�e�q�֌W��؂藣��
	if (child->Parent() != nullptr){
		child->Parent()->RemoveChild(child);
	}

	//�q��ǉ��@�e�����g�ɐݒ�
	m_children.push_back(child);
	child->m_parent = this;
	return true;
}

/// <summary>
/// �q�̐؂藣��
/// </summary>
/// <param name="child">�q</param>
/// <returns>�؂藣���ɐ���������true</returns>
bool Node::RemoveChild(Node* child)
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

/// <summary>
/// �r�W�^�[���󂯓����
/// </summary>
void Node::Accept(Visitor* visitor){
	//�󂯓����
	visitor->Visit(this);

	//�q�ɂ��K�₳����
	for (Node* child:m_children){
		child->Accept(visitor);
	}
}

/// <summary>
/// �_�[�e�B�[�t���O��������Ԃɖ߂�
/// �������@�X�V�@�`��@�I�����\�ȏ�Ԃɂ���
/// </summary>
void Node::ClearDirty()
{
	//�_�[�e�B�[�t���O�����낷
	for (int i = 0; i < DIRTY_FLAG::DIRTY_FLAG_END; i++) {
		m_isDirty[i] = false;
	}
}