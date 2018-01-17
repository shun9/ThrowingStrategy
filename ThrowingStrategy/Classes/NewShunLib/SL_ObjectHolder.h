//************************************************/
//* @file  :ObjectHolder.h
//* @brief :�I�u�W�F�N�g����ۊǂ��Ă����N���X
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include <SL_ObjectNode.h>

namespace ShunLib {
	class ObjectHolder : public Singleton<ObjectHolder>
	{
		friend Singleton<ObjectHolder>;
	public:
		using ObjectList = std::vector<ObjectNode*>;

	private:
		std::vector<ObjectList> m_objectList;

	public:
		// �I�u�W�F�N�g���X�g�̃T�C�Y��ݒ肷��
		void ResizeList(int layerNum, int layerSize);

		//�I�u�W�F�N�g��ǉ�
		void AddObject(int layerNum,ObjectNode* obj);

		//�I�u�W�F�N�g�����O
		void RemoveObject(int layerNum, ObjectNode* obj);

		//�g�p����Ă��Ȃ��I�u�W�F�N�g��T��
		ObjectNode* SearchNotEnableObject(int layerNum);

		// �r�W�^�[���}�������
		void Accept(int layerNum,Visitor* visitor);

		/*--Getter--*/
		ObjectList& List(int layerNum) { return m_objectList[layerNum]; }

	private:
		ObjectHolder() {}
		~ObjectHolder();
	};
}