//************************************************/
//* @file  :Collider.h
//* @brief :�����蔻��I�u�W�F�N�g�̃N���X
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <SL_MacroConstants.h>
#include "../../Object/SL_Shape.h"

class ObjectBase;

namespace ShunLib 
{
	
	//�����蔻��p�N���X�̒��ۃN���X
	class ICollider
	{
	private:
		using Vec3 = ShunLib::Vec3;

	protected:
		//�����蔻������I�u�W�F�N�g
		ObjectBase* m_parent;

		//�����蔻��`��
		IShape* m_shape;

		//�I�u�W�F�N�g����̑��΍��W
		Vec3 m_offset;

		//���������Ƃ��Ɏ��s����֐�
		std::function<void(ObjectBase*)> m_callBack;

	public:
		ICollider();
		virtual ~ICollider();
	
		virtual void Update() = 0;
		void DebugRender();

		void Parent(ObjectBase* parent) { m_parent = parent; }
		ObjectBase* Parent() { return m_parent; }

		Vec3 Offset() { return m_offset; }
		void Offset(const Vec3& offset) { m_offset = offset; }
	
		IShape* Shape() { return m_shape; }

		void SetCallBack(std::function<void(ObjectBase*)> func) { m_callBack = func; }
	
	protected:
		void Shape(IShape* shape) { m_shape = shape; }

	public:
		void operator()(ObjectBase* obj) { 
			if(m_callBack!=NULL)m_callBack(obj); }
	};


	//����̓����蔻��
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() { m_shape  = new Sphere; }
		~SphereCollider() { SAFE_DELETE(m_shape); }

		void Update()override;
	
	private:
		//�L���X�g�����|�C���^��Ԃ�
		Sphere* CastShape() {
			return dynamic_cast<Sphere*>(m_shape);
		}
	};
}