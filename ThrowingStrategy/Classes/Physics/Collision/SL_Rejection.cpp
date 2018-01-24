//************************************************/
//* @file  :SL_ColliderRejection.h
//* @brief :排斥処理　衝突応答
//* @date  :2018/01/09
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// 排斥処理　球同士
/// </summary>
void CollisionManager::Rejection(SphereCollider* A, SphereCollider* B)
{
	//動かないオブジェクトかどうか
	bool aIsStatic = A->ColliderType() == COLLIDER_LAYER::STATIC;
	bool bIsStatic = B->ColliderType() == COLLIDER_LAYER::STATIC;

	//両方とも動かなければ何もしない
	if (aIsStatic && bIsStatic) {
		return;
	}

	Sphere* a = A->Shape();
	Sphere* b = B->Shape();
	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();

	//AからBへ向かうベクトル
	Vec3 distV = b->CenterPoint() - a->CenterPoint();

	//当たっている距離
	float hitDist = (a->Scale().m_x + b->Scale().m_x) - distV.Length();

	//当たっている距離を半分ずつ分け合う
	objA->Transform().Pos(objA->Transform().Pos() - (distV.Normalize()*(hitDist / 2.0f)));
	objB->Transform().Pos(objB->Transform().Pos() + (distV.Normalize()*(hitDist / 2.0f)));
}

/// <summary>
/// 排斥処理　箱同士
/// </summary>
void CollisionManager::Rejection(BoxCollider * A, BoxCollider * B, const Vec3& offset)
{
	//動かないオブジェクトかどうか
	bool aIsStatic = A->ColliderType() == COLLIDER_LAYER::STATIC;
	bool bIsStatic = B->ColliderType() == COLLIDER_LAYER::STATIC;

	//両方とも動かなければ何もしない
	if (aIsStatic && bIsStatic) {
		return;
	}

	Vec3 aPos = A->Parent()->Transform().Pos();
	Vec3 bPos = B->Parent()->Transform().Pos();
	ObjectBase* objA = B->Parent();
	ObjectBase* objB = B->Parent();

	//最小の値で排斥する
	//Xが最小の場合
	if (offset.m_x < offset.m_y && offset.m_x < offset.m_z){
		//Aが動かない
		if (aIsStatic) {
			bPos.m_x += offset.m_x;
			objB->Transform().Pos(bPos);
		}
		//Bが動かない
		else if (bIsStatic) {
			aPos.m_x -= offset.m_x;
			objA->Transform().Pos(aPos);
		}
		//両方動く
		else {
			aPos.m_x -= offset.m_x / 2;
			objA->Transform().Pos(aPos);
			bPos.m_x += offset.m_x / 2;
			objB->Transform().Pos(bPos);
		}

	}
	//Yが最小の場合
	else if (offset.m_y < offset.m_z){
		//Aが動かない
		if (aIsStatic) {
			bPos.m_y += offset.m_y;
			objB->Transform().Pos(bPos);
		}
		//Bが動かない
		else if (bIsStatic) {
			aPos.m_y -= offset.m_y;
			objA->Transform().Pos(aPos);
		}
		//両方動く
		else {
			aPos.m_y -= offset.m_y / 2;
			objA->Transform().Pos(aPos);
			bPos.m_y += offset.m_y / 2;
			objB->Transform().Pos(bPos);
		}
	}
	//Zが最小の場合
	else{
		//Aが動かない
		if (aIsStatic) {
			bPos.m_z += offset.m_z;
			objB->Transform().Pos(bPos);
		}
		//Bが動かない
		else if (bIsStatic) {
			aPos.m_z -= offset.m_z;
			objA->Transform().Pos(aPos);
		}
		//両方動く
		else {
			aPos.m_z -= offset.m_z / 2;
			objA->Transform().Pos(aPos);
			bPos.m_z += offset.m_z / 2;
			objB->Transform().Pos(bPos);
		}
	}

}

/// <summary>
/// 排斥処理　箱と球
/// </summary>
void CollisionManager::Rejection(SphereCollider * A, BoxCollider * B, const Vec3& closestPoint)
{
	//動かないオブジェクトかどうか
	bool aIsStatic = A->ColliderType() == COLLIDER_LAYER::STATIC;
	bool bIsStatic = B->ColliderType() == COLLIDER_LAYER::STATIC;

	//両方とも動かなければ何もしない
	if (aIsStatic && bIsStatic) {
		return;
	}

	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();
	Vec3 aPos = objA->Transform().Pos();
	Vec3 bPos = objB->Transform().Pos();
	Vec3 vec = closestPoint - A->Shape()->CenterPoint();
	float dist = A->Shape()->Radius() - vec.Length();

	//最接近点と球の中心が一致した場合
	//箱の中心と球の中心で排斥する
	if (closestPoint.m_x == A->Shape()->CenterPoint().m_x
	&&  closestPoint.m_y == A->Shape()->CenterPoint().m_y
	&&  closestPoint.m_z == A->Shape()->CenterPoint().m_z){
		Vec3 tmp = B->Shape()->CenterPoint();
		tmp.m_y = A->Shape()->CenterPoint().m_y;
		vec = tmp - A->Shape()->CenterPoint();

		dist = A->Shape()->Radius();
	}

	vec.Normalize();
	vec *= dist;

	//Aが動かない
	if (aIsStatic){
		bPos += vec;
		objB->Transform().Pos(bPos);
	}
	//Bが動かない
	else if (bIsStatic){
		aPos -= vec;
		objA->Transform().Pos(aPos);
	}
	//両方動く
	else{
		aPos -= vec / 2;
		objA->Transform().Pos(aPos);
		bPos += vec / 2;
		objB->Transform().Pos(bPos);
	}
}