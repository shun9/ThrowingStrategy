//************************************************/
//* @file  :Node.cpp
//* @brief :�e�q�֌W�����m�[�h
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#include "SL_Node.h"
#include <algorithm>
#include <SL_MacroConstants.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="childrenSize">�ŏ��Ɋm�ۂ���q�̈ꗗ�T�C�Y</param>
ShunLib::Node::Node(int childrenSize):
	m_parent(nullptr)
{
	//�q�̗̈�����炩���ߊm��
	m_children.reserve(childrenSize);

	//�_�[�e�B�[�t���O�����낷
	for (int i = 0; i < DIRTY_FLAG::DIRTY_FLAG_END; i++){
		m_isDirty[i] = false;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ShunLib::Node::~Node()
{
	for (int i = 0; i < (int)m_children.size(); i++){
		SAFE_DELETE(m_children[i]);
	}
}

/// <summary>
/// ���̏�����
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void ShunLib::Node::BaseInitialize()
{
	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG])
	{
		//����������
		Initialize();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::INITIALIZE_FLAG] = true;

		//�q�̏��������s��
		for (auto& child:m_children){
			child->BaseInitialize();
		}
	}
}

/// <summary>
/// ���̍X�V
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void ShunLib::Node::BaseUpdate()
{
	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::UPDATE_FLAG])
	{
		//�X�V����
		Update();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::UPDATE_FLAG] = true;

		//�q�̍X�V���s��
		for (auto& child : m_children) {
			child->BaseUpdate();
		}
	}
}

/// <summary>
/// ���̕`��
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void ShunLib::Node::BaseRender()
{
	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::RENDER_FLAG])
	{
		//�`�揈��
		Render();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::RENDER_FLAG] = true;

		//�q�̕`����s��
		for (auto& child : m_children) {
			child->BaseRender();
		}
	}
}

/// <summary>
/// ���̏I��
/// �_�[�e�B�[�t���O�̏�������������
/// �h���N���X�̏������Ăяo��
/// </summary>
void ShunLib::Node::BaseFinalize()
{
	//�����O�Ȃ�Δh���N���X�̏������s��
	if (!m_isDirty[DIRTY_FLAG::FINALIZE_FLAG])
	{
		//�I������
		Finalize();

		//�t���O�𗧂Ă�
		m_isDirty[DIRTY_FLAG::FINALIZE_FLAG] = true;

		//�q�̏I�����s��
		for (auto& child : m_children) {
			child->BaseFinalize();
		}
	}
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

/// <summary>
/// �r�W�^�[���󂯓����
/// </summary>
void ShunLib::Node::Accept(Visitor* visitor){
	//�󂯓����
	visitor->Visit(this);

	//�q�ɂ��K�₳����
	for (Node* child:m_children){
		child->Accept(visitor);
	}
}
