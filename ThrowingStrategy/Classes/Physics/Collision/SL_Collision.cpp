#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//“–‚½‚è”»’è
bool CollisionManager::Collision(ICollider* A, ICollider* B)
{
	SHAPE_TYPE aType = A->ShapeType();
	SHAPE_TYPE bType = B->ShapeType();

	bool hit = false;

	//“¯‚¶‚à‚Ì“¯Žm
	if (aType == bType)
	{
		//‹…‚Æ‹…
		if (aType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereCollision(A, B);
		}

		//” ‚Æ” 
		if (aType == SHAPE_TYPE::BOX)
		{
			hit = BoxCollision(A, B);
		}
	}

	//•Ð•û‚ª‹…
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//‹…‚Æ” 
		if (bType == SHAPE_TYPE::BOX)
		{
			hit = SphereAndBoxCollision(A, B);
		}
	}

	//•Ð•û‚ª” 
	if (aType == SHAPE_TYPE::BOX)
	{
		//” ‚Æ‹…
		if (bType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereAndBoxCollision(B, A);
		}
	}

	//“–‚½‚Á‚Ä‚¢‚½‚çƒqƒbƒgƒŠƒXƒg‚É’Ç‰Á
	if (hit){
		if (B->HitParent() != nullptr)A->AddHitList(B->HitParent());
		if (A->HitParent() != nullptr)B->AddHitList(A->HitParent());
	}

	return hit;
}

/*--“–‚½‚è”»’è—p--*/
//‹…‚Æ‹…
bool CollisionManager::SphereCollision(ICollider* A, ICollider* B)
{
	SphereCollider* a = dynamic_cast<SphereCollider*>(A);
	SphereCollider* b = dynamic_cast<SphereCollider*>(B);

	// ’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	Vec3 distV = b->Shape()->CenterPoint() - a->Shape()->CenterPoint();
	float dist = distV.Length();

	// ”¼Œa‚Ì˜a
	float rad = a->Shape()->Radius() + b->Shape()->Radius();

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > rad)
	{
		return false;
	}

	//”rËˆ—
	if (a->ColliderType() != COLLIDER_LAYER::TRIGGER && b->ColliderType() != COLLIDER_LAYER::TRIGGER){
		CollisionManager::Rejection(a,b);
	}

	return true;
}

//‹…‚Æ” 
bool CollisionManager::SphereAndBoxCollision(ICollider* sphere, ICollider* box)
{
	SphereCollider* s = dynamic_cast<SphereCollider*>(sphere);
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);

	//‹…‚Ì’†S“_
	Point point;
	point.CenterPoint(s->Shape()->CenterPoint());

	//ÅÚ‹ß“_
	Point closestPoint;

	//‹…‚Ì’†S“_‚Æ” ‚ÌÅ’Z‹——£‚ðo‚·
	float dist = ShortestDistance(*b->Shape(), point,&closestPoint);

	//Å’Z‹——£‚ª‹…‚Ì”¼Œa‚æ‚è‚à‘å‚«‚©‚Á‚½‚ç“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > s->Shape()->Radius()) {
		return false;
	}

	//”rËˆ—
	if (s->ColliderType() != COLLIDER_LAYER::TRIGGER && b->ColliderType() != COLLIDER_LAYER::TRIGGER) {
		CollisionManager::Rejection(s,b, closestPoint.CenterPoint());
	}

	return true;
}

//” ‚Æ” 
bool CollisionManager::BoxCollision(ICollider* A, ICollider* B)
{
	Box* a = dynamic_cast<BoxCollider*>(A)->Shape();
	Box* b = dynamic_cast<BoxCollider*>(B)->Shape();

	bool isHit = true;
	Vec3 offset = Vec3::Zero;

	/*--XŽ²‚Ì”»’è--*/
	if (!(a->MaxX() > b->MinX() && a->MinX() < b->MaxX())) {
		offset.m_x = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	/*--YŽ²‚Ì”»’è--*/
	if (!(a->MaxY() > b->MinY() && a->MinY() < b->MaxY())) {
		offset.m_y = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	/*--ZŽ²‚Ì”»’è--*/
	if (!(a->MaxZ() > b->MinZ() && a->MinZ() < b->MaxZ())) {
		offset.m_z = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	//”rËˆ—
	if (A->ColliderType() != COLLIDER_LAYER::TRIGGER && B->ColliderType() != COLLIDER_LAYER::TRIGGER) {
		//CollisionManager::Rejection(dynamic_cast<BoxCollider*>(A), dynamic_cast<BoxCollider*>(B), offset);
	}

	return isHit;
}