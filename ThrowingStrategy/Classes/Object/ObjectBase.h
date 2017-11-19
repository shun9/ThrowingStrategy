//************************************************/
//* @file  :ObjectBase.h
//* @brief :�I�u�W�F�N�g�̊��N���X
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <SL_Math.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"

class ObjectBase : public ObjectData
{
private:
	using Matrix = ShunLib::Matrix;

public:
	//�S�ẴI�u�W�F�N�g�̐e
	//�S�ẴI�u�W�F�N�g�������ɕR�Â���
	static ObjectBase* ROOT_OBJECT;
public:
	static void InitializeRootObject();
	static void FinalizeRootObject();

private:
	//�q�I�u�W�F�N�g
	std::vector<ObjectBase*>m_children;

	//�e�I�u�W�F�N�g
	ObjectBase* m_parent;

public:
	//�q�p
	ObjectBase() :m_parent(nullptr) {
		ROOT_OBJECT->AddChild(this);
	}

	//���[�g�p
	//�����͉��ł��悢
	ObjectBase(bool dummy):m_parent(nullptr) {
	}

	virtual ~ObjectBase() {}

	//�e��ݒ�
	void SetParent(ObjectBase* parent);

	//�q��ǉ�
	void AddChild(ObjectBase* child) { 
		m_children.push_back(child); 
		child->SetParent(this);
	}

	//�w�肳�ꂽ�I�u�W�F�N�g���q�ɂ��邩�ǂ���
	bool HasChild(const ObjectBase* obj) {

		//���ڂ̎q�ɑ��݂���
		if (std::find(m_children.begin(), m_children.end(), obj) != m_children.end()) {
			return true;
		}

		//�q�̎q�ɑ��݂���
		for (auto& v : m_children){
			if (v->HasChild(obj)){
				return true;
			}
		}

		return false;
	}
	
	//�w�肳�ꂽ��ނ̃I�u�W�F�N�g���q�ɂ��邩�ǂ���
	//�������ł��̃I�u�W�F�N�g��Ԃ�
	bool HasChild(OBJECT_LIST type,ObjectBase** buff = nullptr) {
		auto c = std::find_if(m_children.begin(), m_children.end(),[=](ObjectBase* child) { return (child->Type() == type); });
		if (c != m_children.end())
		{
			if (buff != nullptr)*buff = (*c);
			return true;
		}
		return false;
	}

	//�q���폜
	void RemoveChild(ObjectBase* child);

	//�ړ�������
	void Move();

	//�`�� ��:���[�g�p�@��:�q�p
	void Render(const Matrix& view, const Matrix& proj);
	void Render(const Matrix& parentWorld, const Matrix& view, const Matrix& proj);

	//������ �X�V  �h���N���X�̍Ō�ɌĂ�
	virtual void Initialize() {	for (auto& v : m_children) { v->Initialize(); }}
	virtual void Update() { 
		//�X�V���̕ύX�ɂ���ăA�N�Z�X�ᔽ���N���邽��
		//�R���e�i�̃T�C�Y�ŉ�
		for (int i = 0;i < (int)m_children.size();i++){
			m_children.at(i)->Update(); 
		} 
	}
	
	//�I��  �h���N���X�̍Ō�ɌĂ�
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }

	//���[�J�����W�n
	ShunLib::Vec3 LocalPos() { return this->Pos(); }
	void LocalPos(const ShunLib::Vec3& pos) { this->Pos(pos); }
	
	//���[���h���W�n
	ShunLib::Vec3 WorldPos() {
		ShunLib::Vec3 pos = this->Pos();
		if (m_parent != nullptr) {
			pos += m_parent->WorldPos();
		}
		return pos;
	}

	ObjectBase* Parent() { return m_parent; }
	const std::vector<ObjectBase*>& Children() { return m_children; }

protected:
	//���g�̍s����v�Z����
	Matrix CalcMat();
};