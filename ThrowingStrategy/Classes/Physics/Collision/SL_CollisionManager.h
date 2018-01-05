//************************************************/
//* @file  :CollisionManager.h
//* @brief :�����蔻����Ǘ�����N���X
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include "SL_Collider.h"

namespace ShunLib
{
	class CollisionManager :public Singleton<CollisionManager>
	{
		friend ShunLib::Singleton<CollisionManager>;
	public:
		//�����蔻��@�r�ˏ���
		static bool Collision(ICollider* A, ICollider* B, bool rejection = true);
		static bool SphereCollision(ICollider* A, ICollider* B, bool rejection);
		static bool BoxCollision(ICollider* A, ICollider* B, bool rejection);
		static bool SphereAndBoxCollision(ICollider* A, ICollider* B, bool rejection);
		static void Rejection(SphereCollider* A, SphereCollider* B);
		static void Rejection(BoxCollider* A, BoxCollider* B, const Vec3& offset);
		static void Rejection(SphereCollider* A, BoxCollider* B, const Vec3& closestPoint);

	private:
		//�����蔻��̈ꗗ
		std::vector<ICollider*> m_colliderList;

	public:
		//�X�V �`��
		void Update();
		void Render();

		//�����蔻��̒ǉ�
		void AddCollider(ICollider* col) { m_colliderList.push_back(col); }

		//�����蔻��̍폜
		void RemoveCollider(ICollider* col) {
			auto tmpCol = std::find(m_colliderList.begin(), m_colliderList.end(), col);
			if (tmpCol != m_colliderList.end()) {
				m_colliderList.erase(tmpCol);
			}
		}

	private:
		CollisionManager() {}
		~CollisionManager() {}
	};
}