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
	public:
		using ChildList = std::vector<ICollider*>;
		using HitObjectList = std::vector<ObjectBase*>;
	protected:
		//�����蔻������I�u�W�F�N�g
		ObjectBase* m_parent;

		//�q�̓����蔻��
		//�e�̓����蔻���Ɏq�̓����蔻����s��
		ChildList m_childrenCollider;

		//�����蔻��`��
		IShape* m_shape;

		//�I�u�W�F�N�g����̑��΍��W
		Vec3 m_offset;

		//�������Ă���I�u�W�F�N�g�̃��X�g
		HitObjectList m_hitList;

		//�e�̏���n�����ǂ���
		bool m_shouldPassParentInfo;

		//�����蔻����s�����ǂ���
		bool m_isEnable;

		//�r�ˏ������s�����ǂ���
		bool m_shouldRejection;

		//�������ǂ���
		bool m_isStatic;

		//�f�o�b�O�`�悷�邩�ǂ���
		bool m_isDebugDraw;
	public:
		ICollider();
		virtual ~ICollider();

		virtual void Update();

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
			for (auto& v:m_childrenCollider){
				v->ResetList();
			}
		}

		//�r�W�^�[�󂯓���
		void Accept(ShunLib::Visitor* visitor);

		//�q�̓����蔻���ǉ�
		void AddChildCollider(ICollider* child);

		/*--Getter--*/
		ObjectBase* Parent          () { return m_parent; }
		ObjectBase* HitParent       ();
		ChildList& ChildrenCollider () { return m_childrenCollider; }
		Vec3 Offset                 () { return m_offset; }
		const HitObjectList& HitList() { return m_hitList; }
		bool IsEnable               () { return m_isEnable; }
		bool IsStatic               () { return m_isStatic; }
		bool ShouldRejection        () { return m_shouldRejection; }
		SHAPE_TYPE Type             () { return m_shape->Type(); }

		/*--Setter--*/
		void Offset         (const Vec3& offset) { m_offset = offset; }
		void Parent         (ObjectBase* parent) { m_parent = parent; }
		void IsEnable       (bool enable       ) { m_isEnable = enable; }
		void IsStatic       (bool isStatic     ) { m_isStatic = isStatic; }
		void IsDebugDraw    (bool draw         ) { m_isDebugDraw = draw; }
		void ShouldPassInfo (bool shouldPass   ) { m_shouldPassParentInfo = shouldPass; }
		void ShouldRejection(bool rejection    ) { m_shouldRejection = rejection; }

	//�������z�֐�
	public:
		//�N���X���ƂɕԂ��`���ύX
		virtual IShape* Shape() = 0;
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