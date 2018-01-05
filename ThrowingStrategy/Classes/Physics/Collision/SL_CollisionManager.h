//************************************************/
//* @file  :CollisionManager.h
//* @brief :当たり判定を管理するクラス
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
		//当たり判定　排斥処理
		static bool Collision(ICollider* A, ICollider* B, bool rejection = true);
		static bool SphereCollision(ICollider* A, ICollider* B, bool rejection);
		static bool BoxCollision(ICollider* A, ICollider* B, bool rejection);
		static bool SphereAndBoxCollision(ICollider* A, ICollider* B, bool rejection);
		static void Rejection(SphereCollider* A, SphereCollider* B);
		static void Rejection(BoxCollider* A, BoxCollider* B, const Vec3& offset);
		static void Rejection(SphereCollider* A, BoxCollider* B, const Vec3& closestPoint);

	private:
		//当たり判定の一覧
		std::vector<ICollider*> m_colliderList;

	public:
		//更新 描画
		void Update();
		void Render();

		//当たり判定の追加
		void AddCollider(ICollider* col) { m_colliderList.push_back(col); }

		//当たり判定の削除
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