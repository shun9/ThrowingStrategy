//************************************************/
//* @file  :CollisionManager.h
//* @brief :当たり判定を管理するクラス
//* @date  :2018/01/23
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include "SL_Collider.h"

namespace ShunLib
{
	//当たり判定の種類
	enum COLLIDER_LAYER {
		RIGID = 0,//物理の影響を受ける
		STATIC,   //物理の影響を受けるが移動しない
		TRIGGER,  //物理の影響を受けない

		COLLIDER_LAYER_END,
	};

	class CollisionManager :public Singleton<CollisionManager>
	{
		friend ShunLib::Singleton<CollisionManager>;
	public:
		using ColliderList = std::vector<std::vector<ICollider*>>;

	public:
		//当たり判定　排斥処理
		static bool Collision(ICollider* A, ICollider* B);
		static bool SphereCollision(ICollider* A, ICollider* B);
		static bool BoxCollision(ICollider* A, ICollider* B);
		static bool SphereAndBoxCollision(ICollider* A, ICollider* B);
		static void Rejection(SphereCollider* A, SphereCollider* B);
		static void Rejection(BoxCollider* A, BoxCollider* B, const Vec3& offset);
		static void Rejection(SphereCollider* A, BoxCollider* B, const Vec3& closestPoint);

	private:
		//当たり判定の一覧
		ColliderList m_colliderList;

	public:
		//リストのサイズを調整
		void ResizeLayer(int layerNum, int layerSize);

		//更新 描画
		void Update();
		void Render();

		//当たり判定の追加
		void AddCollider(int layerNum, ICollider* col) {
			m_colliderList[layerNum].push_back(col);
		}

		//当たり判定の削除
		void RemoveCollider(ICollider* col);

	private:
		CollisionManager();
		~CollisionManager() {}

		//レイヤーごとに当たり判定
		void CollisionLayer(int layer1,int layer2);
	};
}