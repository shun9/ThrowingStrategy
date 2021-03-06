#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//当たり判定
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	bool hit = false;

	//同じもの同士
	if (aType == bType)
	{
		//球と球
		if (aType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereCollision(A, B, rejection);
		}

		//箱と箱
		if (aType == SHAPE_TYPE::BOX)
		{
			hit = BoxCollision(A, B, rejection);
		}
	}

	//片方が球
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//球と箱
		if (bType == SHAPE_TYPE::BOX)
		{
			hit = SphereAndBoxCollision(A, B, rejection);
		}
	}

	//片方が箱
	if (aType == SHAPE_TYPE::BOX)
	{
		//箱と球
		if (bType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereAndBoxCollision(B, A, rejection);
		}
	}

	//当たっていたらヒットリストに追加 子の当たり判定を行う
	if (hit){
		if (B->Parent() != nullptr)A->AddHitList(B->Parent());
		if (A->Parent() != nullptr)B->AddHitList(A->Parent());

		//子の当たり判定
		//※現状子同士の当たり判定を2回取っている
		//※修正必要あり
		for (auto& var : A->ChildrenCollider()) {
			Collision(var, B);
		}

		for (auto& var : B->ChildrenCollider()) {
			Collision(A, var);
		}
	}

	return hit;
}

/*--当たり判定用--*/
//球と球
bool CollisionManager::SphereCollision(ICollider* A, ICollider* B, bool rejection)
{
	SphereCollider* a = dynamic_cast<SphereCollider*>(A);
	SphereCollider* b = dynamic_cast<SphereCollider*>(B);

	// 中心座標間の距離を計算
	Vec3 distV = b->Shape()->CenterPoint() - a->Shape()->CenterPoint();
	float dist = distV.Length();

	// 半径の和
	float rad = a->Shape()->Radius() + b->Shape()->Radius();

	// 距離が半径の和より大きければ、当たっていない
	if (dist > rad)
	{
		return false;
	}

	//排斥処理
	if (rejection){
		//CollisionManager::Rejection(A, B);
	}

	return true;
}

//球と箱
bool CollisionManager::SphereAndBoxCollision(ICollider* sphere, ICollider* box, bool rejection)
{
	SphereCollider* s = dynamic_cast<SphereCollider*>(sphere);
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);
	
	//球の中心点
	Point point;
	point.CenterPoint(s->Shape()->CenterPoint());
	
	//最接近点
	Point closestPoint;

	//球の中心点と箱の最短距離を出す
	float dist = ShortestDistance(*b->Shape(), point,&closestPoint);

	//最短距離が球の半径よりも大きかったら当たっていない
	if (dist > s->Shape()->Radius()) {
		return false;
	}

	return true;
}

//箱と箱
bool CollisionManager::BoxCollision(ICollider* A, ICollider* B, bool rejection)
{
	Box* a = dynamic_cast<BoxCollider*>(A)->Shape();
	Box* b = dynamic_cast<BoxCollider*>(B)->Shape();

	/*--X軸の判定--*/
	if (!(a->MaxX() > b->MinX() && a->MinX() < b->MaxX())) {
		return false;
	}

	/*--Y軸の判定--*/
	if (!(a->MaxY() > b->MinY() && a->MinY() < b->MaxY())) {
		return false;
	}

	/*--Z軸の判定--*/
	if (!(a->MaxZ() > b->MinZ() && a->MinZ() < b->MaxZ())) {
		return false;
	}

	return true;
}