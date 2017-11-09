//************************************************/
//* @file  :ObjectBase.h
//* @brief :�I�u�W�F�N�g�̊��N���X
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <SL_Math.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"

class ObjectBase : public ObjectData
{
private:
	using Matrix = ShunLib::Matrix;

private:
	//�q�I�u�W�F�N�g
	std::vector<ObjectBase*>m_children;

	//�e�I�u�W�F�N�g
	ObjectBase* m_parent;

public:
	ObjectBase():
		m_parent(nullptr)
	{}
	virtual ~ObjectBase() {}

	//�e��ݒ�
	void SetParent(ObjectBase* parent) {
		m_parent = parent;
	}

	//�q��ǉ�
	void AddChild(ObjectBase* child) { 
		m_children.push_back(child); 
		child->SetParent(this);
	}

	//�q���폜
	void RemoveChild(ObjectBase* child){
		auto tmpChild = std::find(m_children.begin(), m_children.end(), child);
		if (tmpChild != m_children.end()) {
			m_children.erase(tmpChild);
			child->SetParent(this);
		}
	}

	//�ړ�������
	void Move();

	//�`�� ��:���[�g�p�@��:�q�p
	void Render(const Matrix& view, const Matrix& proj);
	void Render(const Matrix& parentWorld, const Matrix& view, const Matrix& proj);

	//������ �X�V  �h���N���X�̍Ō�ɌĂ�
	virtual void Initialize() {	for (auto& v : m_children) { v->Initialize(); }}
	virtual void Update() { for (auto& v : m_children) { v->Update(); } }
	
	//�I��  �h���N���X�̍Ō�ɌĂ�
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }
};