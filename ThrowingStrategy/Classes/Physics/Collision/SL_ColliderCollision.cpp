#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//“–‚½‚è”»’è
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	bool hit = false;

	//“¯‚¶‚à‚Ì“¯m
	if (aType == bType)
	{
		//‹…‚Æ‹…
		if (aType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereCollision(A, B, rejection);
		}

		//” ‚Æ” 
		if (aType == SHAPE_TYPE::BOX)
		{
			hit = BoxCollision(A, B, rejection);
		}
	}

	//•Ğ•û‚ª‹…
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//‹…‚Æ” 
		if (bType == SHAPE_TYPE::BOX)
		{
			hit = SphereAndBoxCollision(A, B, rejection);
		}
	}

	//•Ğ•û‚ª” 
	if (aType == SHAPE_TYPE::BOX)
	{
		//” ‚Æ‹…
		if (bType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereAndBoxCollision(B, A, rejection);
		}
	}

	//“–‚½‚Á‚Ä‚¢‚½‚çƒqƒbƒgƒŠƒXƒg‚É’Ç‰Á
	if (hit){
		if (B->Parent() != nullptr)A->AddHitList(B->Parent());
		if (A->Parent() != nullptr)B->AddHitList(A->Parent());
	}

	//q‚Ì“–‚½‚è”»’è
	for(auto& var : A->ChildrenCollider()){
		Collision(var, B);
	}

	for (auto& var : B->ChildrenCollider()) {
		Collision(A, var);
	}

	return hit;
}

/*--“–‚½‚è”»’è—p--*/
//‹…‚Æ‹…
bool CollisionManager::SphereCollision(ICollider* A, ICollider* B, bool rejection)
{
	SphereCollider* a = dynamic_cast<SphereCollider*>(A);
	SphereCollider* b = dynamic_cast<SphereCollider*>(B);

	// ’†SÀ•WŠÔ‚Ì‹——£‚ğŒvZ
	Vec3 distV = b->Shape()->CenterPoint() - a->Shape()->CenterPoint();
	float dist = distV.Length();

	// ”¼Œa‚Ì˜a
	float rad = a->Shape()->Scale() + b->Shape()->Scale();

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > rad)
	{
		return false;
	}

	//”rËˆ—
	if (rejection){
		//CollisionManager::Rejection(A, B);
	}

	return true;
}

//‹…‚Æ” 
bool CollisionManager::SphereAndBoxCollision(ICollider* sphere, ICollider* box, bool rejection)
{
	SphereCollider* s = dynamic_cast<SphereCollider*>(sphere);
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);
	
	Point point;
	point.CenterPoint(s->Shape()->CenterPoint());
	
	//‹…‚Ì’†S“_‚Æ” ‚ÌÅ’Z‹——£‚ğo‚·
	float dist = ShortestDistance((*b->Shape()), point);

	//Å’Z‹——£‚ª‹…‚Ì”¼Œa‚æ‚è‚à‘å‚«‚©‚Á‚½‚ç“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > s->Shape()->Scale()) {
		return false;
	}

	return true;
}

//” ‚Æ” 
bool CollisionManager::BoxCollision(ICollider* A, ICollider* B, bool rejection)
{
	Box* a = dynamic_cast<BoxCollider*>(A)->Shape();
	Box* b = dynamic_cast<BoxCollider*>(B)->Shape();

	/*--X²‚Ì”»’è--*/
	float aXRight = a->CenterPoint().m_x + (a->Size().m_x / 2.0f);//A‚ÌX²‚Ì‰E‘¤(+•ûŒü)
	float aXLeft  = a->CenterPoint().m_x - (a->Size().m_x / 2.0f);//A‚ÌX²‚Ì¶‘¤(-•ûŒü)

	float bXRight = b->CenterPoint().m_x + (b->Size().m_x / 2.0f);//B‚ÌX²‚Ì‰E‘¤(+•ûŒü)
	float bXLeft  = b->CenterPoint().m_x - (b->Size().m_x / 2.0f);//B‚ÌX²‚Ì¶‘¤(-•ûŒü)

	if (!(aXRight > bXLeft && aXLeft < bXRight)) {
		return false;
	}

	/*--Y²‚Ì”»’è--*/
	float aYTop    = a->CenterPoint().m_y + (a->Size().m_y / 2.0f);//A‚ÌY²‚Ìã‘¤(+•ûŒü)
	float aYBottom = a->CenterPoint().m_y - (a->Size().m_y / 2.0f);//A‚ÌY²‚Ì‰º‘¤(-•ûŒü)

	float bYTop    = b->CenterPoint().m_y + (b->Size().m_y / 2.0f);//B‚ÌY²‚Ìã‘¤(+•ûŒü)
	float bYBottom = b->CenterPoint().m_y - (b->Size().m_y / 2.0f);//B‚ÌY²‚Ì‰º‘¤(-•ûŒü)

	if (!(aYTop > bYBottom && aYBottom < bYTop)) {
		return false;
	}

	/*--Z²‚Ì”»’è--*/
	float aZFront = a->CenterPoint().m_z + (a->Size().m_z / 2.0f);//A‚ÌZ²‚Ì‰œ‘¤@(+•ûŒü)
	float aZBack  = a->CenterPoint().m_z - (a->Size().m_z / 2.0f);//A‚ÌZ²‚Ìè‘O‘¤(-•ûŒü)

	float bZFront = b->CenterPoint().m_z + (b->Size().m_z / 2.0f);//B‚ÌZ²‚Ì‰œ‘¤@(+•ûŒü)
	float bZBack  = b->CenterPoint().m_z - (b->Size().m_z / 2.0f);//B‚ÌZ²‚Ìè‘O‘¤(-•ûŒü)

	if (!(aZFront > bZBack && aZBack < bZFront)) {
		return false;
	}

	return true;
}