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
#include <SL_Visitor.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"
#include "ObjectData.h"
#include "ObjectTransform.h"

class ObjectBase : public ObjectData , public ShunLib::VisitorNode,public ObjectTransform
{
private:
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;
	using OBJECT_LIST = ObjectConstantNumber::OBJECT_LIST;

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

	//�q���폜
	void RemoveChild(ObjectBase* child);

	//�ړ�������
	void Move();

	//�`�� ��:���[�g�p�@��:�q�p
	void Render(const Matrix& view, const Matrix& proj);
	void RenderChild(const Matrix& view, const Matrix& proj);

	//������ �X�V  �h���N���X�̍Ō�ɌĂ�
	virtual void Initialize() {	
		for (int i = 0; i < (int)(m_children.size()); i++){
			m_children.at(i)->Initialize();
		}
	}

	virtual void Update() { 
		//�X�V���̕ύX�ɂ���ăA�N�Z�X�ᔽ���N���邽��
		//�R���e�i�̃T�C�Y�ŉ�
		for (int i = 0;i < (int)m_children.size();i++){
			m_children.at(i)->Update(); 
		} 
	}
	
	//�I��  �h���N���X�̍Ō�ɌĂ�
	virtual void Finalize() { for (auto& v : m_children) { v->Finalize(); } }

	//�r�W�^�[�󂯓���
	void Accept(ShunLib::Visitor* visitor) {
		visitor->Visit(this);
		for (auto& v : m_children) {
			visitor->Visit(v);
		}
	}

	//���[�J�����W�n
	Vec3 LocalPos() { return this->Pos(); }
	void LocalPos(const Vec3& pos) { this->Pos(pos); }
	
	//���[���h���W�n
	Vec3 WorldPos() {
		Vec3 pos = this->Pos();
		if (m_parent != nullptr) {
			pos += m_parent->WorldPos();
		}
		return pos;
	}

	//���[���h�g�嗦
	Vec3 WorldScale() {
		Vec3 scale = this->Scale();
		if (m_parent != nullptr) {
			scale.m_x *= m_parent->WorldScale().m_x;
			scale.m_y *= m_parent->WorldScale().m_y;
			scale.m_z *= m_parent->WorldScale().m_z;
		}
		return scale;
	}

	//���[���h��]��
	Vec3 WorldRotation() {
		Vec3 rot = this->Rotation();
		if (m_parent != nullptr) {
			rot += m_parent->WorldRotation();
		}
		return rot;
	}

	//�e�q�֌W
	ObjectBase* Parent() { return m_parent; }
	const std::vector<ObjectBase*>& Children() { return m_children; }

	
protected:
	//���g�̍s����v�Z����
	void CalcMat();
};