#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//“–‚½‚è”»’è
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	//“¯‚¶‚à‚Ì“¯Žm
	if (aType == bType)
	{
		//‹…‚Æ‹…
		if (aType == SHAPE_TYPE::SPHERE)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(a, b, rejection);
		}

		//” ‚Æ” 
		if (aType == SHAPE_TYPE::BOX)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//•Ð•û‚ª‹…
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//‹…‚Æ” 
		if (bType == SHAPE_TYPE::BOX)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//•Ð•û‚ª” 
	if (aType == SHAPE_TYPE::BOX)
	{
		//” ‚Æ‹…
		if (bType == SHAPE_TYPE::SPHERE)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(b, a, rejection);
		}
	}

	return false;
}

/*--“–‚½‚è”»’è—p--*/
//‹…‚Æ‹…
bool CollisionManager::Collision(SphereCollider* A, SphereCollider* B, bool rejection)
{
	// ’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	Vec3 distV = B->Shape()->CenterPoint() - A->Shape()->CenterPoint();
	float dist = distV.Length();

	// ”¼Œa‚Ì˜a
	float rad = A->Shape()->Scale() + B->Shape()->Scale();

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
bool CollisionManager::Collision(SphereCollider* A, BoxCollider* B, bool rejection)
{
	Point point;
	point.CenterPoint(A->Shape()->CenterPoint());
	
	//‹…‚Ì’†S“_‚Æ” ‚ÌÅ’Z‹——£‚ðo‚·
	float dist = ShortestDistance((*B->Shape()), point);

	//Å’Z‹——£‚ª‹…‚Ì”¼Œa‚æ‚è‚à‘å‚«‚©‚Á‚½‚ç“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > A->Shape()->Scale()) {
		return false;
	}

	return true;
}

//” ‚Æ” 
bool CollisionManager::Collision(BoxCollider* A, BoxCollider* B, bool rejection)
{
	Box* a = A->Shape();
	Box* b = B->Shape();

	/*--XŽ²‚Ì”»’è--*/
	float aXRight = a->CenterPoint().m_x + (a->Size().m_x / 2.0f);//A‚ÌXŽ²‚Ì‰E‘¤(+•ûŒü)
	float aXLeft  = a->CenterPoint().m_x - (a->Size().m_x / 2.0f);//A‚ÌXŽ²‚Ì¶‘¤(-•ûŒü)

	float bXRight = b->CenterPoint().m_x + (b->Size().m_x / 2.0f);//B‚ÌXŽ²‚Ì‰E‘¤(+•ûŒü)
	float bXLeft  = b->CenterPoint().m_x - (b->Size().m_x / 2.0f);//B‚ÌXŽ²‚Ì¶‘¤(-•ûŒü)

	if (!(aXRight > bXLeft && aXLeft < bXRight)) {
		return false;
	}

	/*--YŽ²‚Ì”»’è--*/
	float aYTop    = a->CenterPoint().m_y + (a->Size().m_y / 2.0f);//A‚ÌYŽ²‚Ìã‘¤(+•ûŒü)
	float aYBottom = a->CenterPoint().m_y - (a->Size().m_y / 2.0f);//A‚ÌYŽ²‚Ì‰º‘¤(-•ûŒü)

	float bYTop    = b->CenterPoint().m_y + (b->Size().m_y / 2.0f);//B‚ÌYŽ²‚Ìã‘¤(+•ûŒü)
	float bYBottom = b->CenterPoint().m_y - (b->Size().m_y / 2.0f);//B‚ÌYŽ²‚Ì‰º‘¤(-•ûŒü)

	if (!(aYTop > bYBottom && aYBottom < bYTop)) {
		return false;
	}

	/*--ZŽ²‚Ì”»’è--*/
	float aZFront = a->CenterPoint().m_z + (a->Size().m_z / 2.0f);//A‚ÌZŽ²‚Ì‰œ‘¤@(+•ûŒü)
	float aZBack  = a->CenterPoint().m_z - (a->Size().m_z / 2.0f);//A‚ÌZŽ²‚ÌŽè‘O‘¤(-•ûŒü)

	float bZFront = b->CenterPoint().m_z + (b->Size().m_z / 2.0f);//B‚ÌZŽ²‚Ì‰œ‘¤@(+•ûŒü)
	float bZBack  = b->CenterPoint().m_z - (b->Size().m_z / 2.0f);//B‚ÌZŽ²‚ÌŽè‘O‘¤(-•ûŒü)

	if (!(aZFront > bZBack && aZBack < bZFront)) {
		return false;
	}

	return true;
}