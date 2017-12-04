//************************************************/
//* @file  :CollisionManager.h
//* @brief :“–‚½‚è”»’è‚ğŠÇ—‚·‚éƒNƒ‰ƒX
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
		//“–‚½‚è”»’è@”rËˆ—
		static bool Collision(ICollider* A, ICollider* B, bool rejection = true);
		static bool SphereCollision(ICollider* A, ICollider* B, bool rejection);
		static bool BoxCollision(ICollider* A, ICollider* B, bool rejection);
		static bool SphereAndBoxCollision(ICollider* A, ICollider* B, bool rejection);
		static void Rejection(SphereCollider* A, SphereCollider* B);
		static void Rejection(BoxCollider* A, BoxCollider* B);
		static void Rejection(SphereCollider* A, BoxCollider* B);

	private:
		std::vector<ICollider*> m_colliderList;

	public:
		void Update();
		void Render();

		void AddCollider(ICollider* col) { m_colliderList.push_back(col); }
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