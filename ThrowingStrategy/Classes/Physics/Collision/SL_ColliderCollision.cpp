#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//当たり判定
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	//同じもの同士
	if (aType == bType)
	{
		//球と球
		if (aType == SHAPE_TYPE::SPHERE)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(a, b, rejection);
		}

		//箱と箱
		if (aType == SHAPE_TYPE::BOX)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//片方が球
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//球と箱
		if (bType == SHAPE_TYPE::BOX)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//片方が箱
	if (aType == SHAPE_TYPE::BOX)
	{
		//箱と球
		if (bType == SHAPE_TYPE::SPHERE)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(b, a, rejection);
		}
	}

	return false;
}

/*--当たり判定用--*/
//球と球
bool CollisionManager::Collision(SphereCollider* A, SphereCollider* B, bool rejection)
{
	// 中心座標間の距離を計算
	Vec3 distV = B->Shape()->CenterPoint() - A->Shape()->CenterPoint();
	float dist = distV.Length();

	// 半径の和
	float rad = A->Shape()->Scale() + B->Shape()->Scale();

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
bool CollisionManager::Collision(SphereCollider* A, BoxCollider* B, bool rejection)
{
	Point point;
	point.CenterPoint(A->Shape()->CenterPoint());
	
	//球の中心点と箱の最短距離を出す
	float dist = ShortestDistance((*B->Shape()), point);

	//最短距離が球の半径よりも大きかったら当たっていない
	if (dist > A->Shape()->Scale()) {
		return false;
	}

	return true;
}

//箱と箱
bool CollisionManager::Collision(BoxCollider* A, BoxCollider* B, bool rejection)
{
	Box* a = A->Shape();
	Box* b = B->Shape();

	/*--X軸の判定--*/
	float aXRight = a->CenterPoint().m_x + (a->Size().m_x / 2.0f);//AのX軸の右側(+方向)
	float aXLeft  = a->CenterPoint().m_x - (a->Size().m_x / 2.0f);//AのX軸の左側(-方向)

	float bXRight = b->CenterPoint().m_x + (b->Size().m_x / 2.0f);//BのX軸の右側(+方向)
	float bXLeft  = b->CenterPoint().m_x - (b->Size().m_x / 2.0f);//BのX軸の左側(-方向)

	if (!(aXRight > bXLeft && aXLeft < bXRight)) {
		return false;
	}

	/*--Y軸の判定--*/
	float aYTop    = a->CenterPoint().m_y + (a->Size().m_y / 2.0f);//AのY軸の上側(+方向)
	float aYBottom = a->CenterPoint().m_y - (a->Size().m_y / 2.0f);//AのY軸の下側(-方向)

	float bYTop    = b->CenterPoint().m_y + (b->Size().m_y / 2.0f);//BのY軸の上側(+方向)
	float bYBottom = b->CenterPoint().m_y - (b->Size().m_y / 2.0f);//BのY軸の下側(-方向)

	if (!(aYTop > bYBottom && aYBottom < bYTop)) {
		return false;
	}

	/*--Z軸の判定--*/
	float aZFront = a->CenterPoint().m_z + (a->Size().m_z / 2.0f);//AのZ軸の奥側　(+方向)
	float aZBack  = a->CenterPoint().m_z - (a->Size().m_z / 2.0f);//AのZ軸の手前側(-方向)

	float bZFront = b->CenterPoint().m_z + (b->Size().m_z / 2.0f);//BのZ軸の奥側　(+方向)
	float bZBack  = b->CenterPoint().m_z - (b->Size().m_z / 2.0f);//BのZ軸の手前側(-方向)

	if (!(aZFront > bZBack && aZBack < bZFront)) {
		return false;
	}

	return true;
}