//************************************************/
//* @file  :Node.h
//* @brief :�e�q�֌W�����m�[�h
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Visitor.h>

namespace ShunLib
{
	class Node : public VisitorNode
	{
	public:
		//�_�[�e�B�[�t���O�ꗗ
		enum DIRTY_FLAG {
			INITIALIZE_FLAG = 0 ,
			UPDATE_FLAG,
			RENDER_FLAG,
			FINALIZE_FLAG,

			DIRTY_FLAG_END,
		};

	protected:
		//�e
		Node* m_parent;

		//�q�̈ꗗ
		std::vector<Node*> m_children;

		//�g�p���Ă��邩�ǂ���
		bool m_isEnable;

		//�_�[�e�B�[�t���O
		//�������true
		bool m_isDirty[DIRTY_FLAG::DIRTY_FLAG_END];

	public:
		Node(int childrenSize = 100);
		virtual ~Node();

		//�������@�X�V�@�`��@�I��
		//�_�[�e�B�[�t���O�̏�������������
		//�h���N���X�̏������Ăяo��
		void BaseInitialize();
		void BaseUpdate();
		void BaseRender();
		void BaseFinalize();

		//�e�ݒ�
		virtual bool SetParent(Node* parent);

		//�q�̒ǉ�
		virtual bool AddChild(Node* child);

		//�q�̐؂藣��
		virtual bool RemoveChild(Node* child);

		//�r�W�^�[���󂯓����
		virtual void Accept(Visitor* visitor);

		//�_�[�e�B�[�t���O��������Ԃɖ߂�
		//�������@�X�V�@�`��@�I�����\�ȏ�Ԃɂ���
		void ClearDirty();

		//�X�V�@�`����\�ȏ�Ԃɂ���
		void BaseActiveUpdate();
		void BaseActiveRender();

		/*--Getter--*/
		Node* Parent() { return m_parent; }
		std::vector<Node*>& Children() { return m_children; }
		bool IsEnable() { return m_isEnable; }

	protected:
		//�������@�X�V�@�`��@�I��
		//�h���N���X�ŏ�������������
		virtual void Initialize() { m_isEnable = true; };
		virtual void Update    () = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;

		//�X�V�@�`����\�ȏ�Ԃɂ���
		void EnableUpdate() { m_isDirty[DIRTY_FLAG::UPDATE_FLAG] = false; }
		void EnableRender() { m_isDirty[DIRTY_FLAG::RENDER_FLAG] = false; }
	};
}