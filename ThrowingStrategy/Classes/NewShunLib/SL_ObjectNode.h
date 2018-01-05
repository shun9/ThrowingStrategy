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
		//�I�u�W�F�N�g�̊�{���
		ObjectTransform m_transform;

		int m_layerNumber;

	public:
		ObjectNode(int layerNumber);
		virtual ~ObjectNode();


		//�e�ݒ�
		bool SetParent(Node* parent)override;

		//�q�̒ǉ�
		bool AddChild(Node* child)override;

		//�q�̐؂藣��
		bool RemoveChild(Node* child)override;

		/*--Getter--*/
		const Vec3 WorldPos()const;
		const Vec3 LocalPos()const { return m_transform.Pos(); }

		/*--Setter--*/
		void LocalPos(const Vec3& pos) { m_transform.Pos(pos); }

		/*--Getter & Setter--*/
		ObjectTransform& Transform() { return m_transform; }

	protected:
		//�������@�X�V�@�`��@�I��
		//�h���N���X�ŏ�������������
		virtual void Initialize()override { Node::Initialize(); };
		virtual void Update    ()override = 0;
		virtual void Render    ()override = 0;
		virtual void Finalize  ()override = 0;
	};
}