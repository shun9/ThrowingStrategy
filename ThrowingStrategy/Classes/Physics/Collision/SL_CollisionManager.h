//************************************************/
//* @file  :CollisionManager.h
//* @brief :�����蔻����Ǘ�����N���X
//* @date  :2018/01/23
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include "SL_Collider.h"

namespace ShunLib
{
	//�����蔻��̎��
	enum COLLIDER_LAYER {
		RIGID = 0,//�����̉e�����󂯂�
		STATIC,   //�����̉e�����󂯂邪�ړ����Ȃ�
		TRIGGER,  //�����̉e�����󂯂Ȃ�

		COLLIDER_LAYER_END,
	};

	class CollisionManager :public Singleton<CollisionManager>
	{
		friend ShunLib::Singleton<CollisionManager>;
	public:
		using ColliderList = std::vector<std::vector<ICollider*>>;

	public:
		//�����蔻��@�r�ˏ���
		static bool Collision(ICollider* A, ICollider* B);
		static bool SphereCollision(ICollider* A, ICollider* B);
		static bool BoxCollision(ICollider* A, ICollider* B);
		static bool SphereAndBoxCollision(ICollider* A, ICollider* B);
		static void Rejection(SphereCollider* A, SphereCollider* B);
		static void Rejection(BoxCollider* A, BoxCollider* B, const Vec3& offset);
		static void Rejection(SphereCollider* A, BoxCollider* B, const Vec3& closestPoint);

	private:
		//�����蔻��̈ꗗ
		ColliderList m_colliderList;

	public:
		//���X�g�̃T�C�Y�𒲐�
		void ResizeLayer(int layerNum, int layerSize);

		//�X�V �`��
		void Update();
		void Render();

		//�����蔻��̒ǉ�
		void AddCollider(int layerNum, ICollider* col) {
			m_colliderList[layerNum].push_back(col);
		}

		//�����蔻��̍폜
		void RemoveCollider(ICollider* col);

	private:
		CollisionManager();
		~CollisionManager() {}

		//���C���[���Ƃɓ����蔻��
		void CollisionLayer(int layer1,int layer2);
	};
}