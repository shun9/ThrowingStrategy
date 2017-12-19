//************************************************/
//* @file  :ObjectNode.h
//* @brief :�e�q�֌W��������3D�I�u�W�F�N�g�̃m�[�h
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Node.h>
#include <SL_ObjectTransform.h>

namespace ShunLib {
	class ObjectNode : public Node
	{
	protected:
		ObjectTransform m_transform;

	public:
		ObjectNode() {}
		~ObjectNode() {}

		//�e�ݒ�
		bool SetParent(Node* parent)override;

		//�q�̒ǉ�
		bool AddChild(Node* child)override;

		//�q�̐؂藣��
		bool RemoveChild(Node* child)override;

		/*--Getter--*/
		const Vec3& WorldPos()const { return m_transform.Pos(); }
		const Vec3& LocalPos()const { return m_transform.Pos(); }
		const ObjectTransform& Transform()const { return m_transform; }

		/*--Setter--*/
		void LocalPos(const Vec3& pos) { m_transform.Pos(pos); }

	};
}