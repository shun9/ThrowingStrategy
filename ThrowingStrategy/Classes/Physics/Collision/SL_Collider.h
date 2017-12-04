//************************************************/
//* @file  :SL_Collider.h
//* @brief :�����蔻��I�u�W�F�N�g�̃N���X
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <vector>
#include <SL_MacroConstants.h>
#include <SL_Visitor.h>
#include "../../Object/SL_Shape.h"

class ObjectBase;

namespace ShunLib
{
	//�����蔻��p�N���X�̒��ۃN���X
	class ICollider :public VisitorNode
	{
	protected:
		//�����蔻������I�u�W�F�N�g
		ObjectBase* m_parent;

		//�q�̓����蔻��
		//�e�̓����蔻���Ɏq�̓����蔻����s��
		std::vector<ICollider*> m_childrenCollider;

		//�����蔻��`��
		IShape* m_shape;

		//�I�u�W�F�N�g����̑��΍��W
		Vec3 m_offset;

		//���݂��邩�ǂ���
		//�Փˉ��������邩�ǂ����Ɏg�p
		bool m_isEntity;

		//���������Ƃ��Ɏ��s����֐�
		std::function<void(ObjectBase*)> m_callBack;

		//�������Ă���I�u�W�F�N�g�̃��X�g
		std::vector<ObjectBase*>m_hitList;

		bool m_isDebugDraw;
	public:
		ICollider();
		virtual ~ICollider();
	
		virtual void Update() = 0;
		void DebugRender();

		//���X�g�ɒǉ�
		//�����傪�����ꍇ�͒ǉ����Ȃ�
		void AddHitList(ObjectBase* obj) {
			if (m_parent != obj && obj != nullptr) {
				m_hitList.push_back(obj);
			}
		}

		//���X�g�̏�����
		void ResetList() { 
			m_hitList.clear();
			m_hitList.shrink_to_fit();
		}

		//�r�W�^�[�󂯓���
		void Accept(ShunLib::Visitor* visitor);

		//�q�̓����蔻���ǉ�
		void AddChildCollider(ICollider* child);

		/*--Getter--*/
		ObjectBase* Parent() { return m_parent; }
		std::vector<ICollider*>& ChildrenCollider() { return m_childrenCollider; }
		Vec3 Offset() { return m_offset; }
		const std::vector<ObjectBase*>& HitList() { return m_hitList; }
		bool IsEntity() { return m_isEntity; }
		SHAPE_TYPE Type() { return m_shape->Type(); }

		/*--Setter--*/
		void Offset(const Vec3& offset) { m_offset = offset; }
		void Parent(ObjectBase* parent) { m_parent = parent; }
		void SetCallBack(std::function<void(ObjectBase*)> func) { m_callBack = func; }
		void IsEntity(bool entity) { m_isEntity = entity; }
		void IsDebugDraw(bool draw) { m_isDebugDraw = draw; }
	
		//�������z�֐�
	public:
		//�N���X���ƂɕԂ��`���ύX
		virtual IShape* Shape() = 0;

	public:
		//�R�[���o�b�N���Ă�
		void operator()(ObjectBase* obj) { 
			if(m_callBack!=NULL)m_callBack(obj); }
	};

	//����̓����蔻��p�N���X
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() { m_shape  = new Sphere; }
		~SphereCollider() { SAFE_DELETE(m_shape); }
	
		void Update()override;

		//�L���X�g�����|�C���^��Ԃ�
		Sphere* Shape() {
			return dynamic_cast<Sphere*>(m_shape);
		}
	};

	//����̓����蔻��p�N���X
	class BoxCollider : public ICollider
	{
	public:
		BoxCollider() { m_shape = new Box; }
		~BoxCollider() { SAFE_DELETE(m_shape); }

		void Update()override;
		
		Box* Shape() {
			return dynamic_cast<Box*>(m_shape);
		}
	};

}