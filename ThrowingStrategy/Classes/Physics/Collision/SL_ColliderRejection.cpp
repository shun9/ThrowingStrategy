//************************************************/
//* @file  :SL_ColliderRejection.h
//* @brief :”rËˆ—@Õ“Ë‰“š
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// ”rËˆ—@‹…“¯m
/// </summary>
void CollisionManager::Rejection(SphereCollider* A, SphereCollider* B)
{
	//“®‚©‚È‚¢Ò“¯m‚È‚ç‰½‚à‚µ‚È‚¢
	if (A->IsStatic() && B->IsStatic()) {
		return;
	}

	Sphere* a = A->Shape();
	Sphere* b = B->Shape();
	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();

	//A‚©‚çB‚ÖŒü‚©‚¤ƒxƒNƒgƒ‹
	Vec3 distV = b->CenterPoint() - a->CenterPoint();

	//“–‚½‚Á‚Ä‚¢‚é‹——£
	float hitDist = (a->Scale().m_x + b->Scale().m_x) - distV.Length();

	//“–‚½‚Á‚Ä‚¢‚é‹——£‚ğ”¼•ª‚¸‚Â•ª‚¯‡‚¤
	objA->Transform().Pos(objA->Transform().Pos() - (distV.Normalize()*(hitDist / 2.0f)));
	objB->Transform().Pos(objB->Transform().Pos() + (distV.Normalize()*(hitDist / 2.0f)));
}

/// <summary>
/// ”rËˆ—@” “¯m
/// </summary>
void CollisionManager::Rejection(BoxCollider * A, BoxCollider * B, const Vec3& offset)
{
	//“®‚©‚È‚¢Ò“¯m‚È‚ç‰½‚à‚µ‚È‚¢
	if (A->IsStatic() && B->IsStatic()) {
		return;
	}

	Vec3 aPos = A->Parent()->Transform().Pos();
	Vec3 bPos = B->Parent()->Transform().Pos();
	ObjectBase* objA = B->Parent();
	ObjectBase* objB = B->Parent();

	//Å¬‚Ì’l‚Å”rË‚·‚é
	//X‚ªÅ¬‚Ìê‡
	if (offset.m_x < offset.m_y && offset.m_x < offset.m_z){
		//A‚ª“®‚©‚È‚¢
		if (A->IsStatic()) {
			bPos.m_x += offset.m_x;
			objB->Transform().Pos(bPos);
		}
		//B‚ª“®‚©‚È‚¢
		else if (B->IsStatic()) {
			aPos.m_x -= offset.m_x;
			objA->Transform().Pos(aPos);
		}
		//—¼•û“®‚­
		else {
			aPos.m_x -= offset.m_x / 2;
			objA->Transform().Pos(aPos);
			bPos.m_x += offset.m_x / 2;
			objB->Transform().Pos(bPos);
		}

	}
	//Y‚ªÅ¬‚Ìê‡
	else if (offset.m_y < offset.m_z){
		//A‚ª“®‚©‚È‚¢
		if (A->IsStatic()) {
			bPos.m_y += offset.m_y;
			objB->Transform().Pos(bPos);
		}
		//B‚ª“®‚©‚È‚¢
		else if (B->IsStatic()) {
			aPos.m_y -= offset.m_y;
			objA->Transform().Pos(aPos);
		}
		//—¼•û“®‚­
		else {
			aPos.m_y -= offset.m_y / 2;
			objA->Transform().Pos(aPos);
			bPos.m_y += offset.m_y / 2;
			objB->Transform().Pos(bPos);
		}
	}
	//Z‚ªÅ¬‚Ìê‡
	else{
		//A‚ª“®‚©‚È‚¢
		if (A->IsStatic()) {
			bPos.m_z += offset.m_z;
			objB->Transform().Pos(bPos);
		}
		//B‚ª“®‚©‚È‚¢
		else if (B->IsStatic()) {
			aPos.m_z -= offset.m_z;
			objA->Transform().Pos(aPos);
		}
		//—¼•û“®‚­
		else {
			aPos.m_z -= offset.m_z / 2;
			objA->Transform().Pos(aPos);
			bPos.m_z += offset.m_z / 2;
			objB->Transform().Pos(bPos);
		}
	}

}

/// <summary>
/// ”rËˆ—@” ‚Æ‹…
/// </summary>
void CollisionManager::Rejection(SphereCollider * A, BoxCollider * B, const Vec3& closestPoint)
{
	//“®‚©‚È‚¢Ò“¯m‚È‚ç‰½‚à‚µ‚È‚¢
	if (A->IsStatic() && B->IsStatic()) {
		return;
	}

	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();
	Vec3 aPos = objA->Transform().Pos();
	Vec3 bPos = objB->Transform().Pos();
	Vec3 vec = closestPoint - A->Shape()->CenterPoint();
	float dist = A->Shape()->Radius() - vec.Length();
	vec.Normalize();
	vec *= dist;

	//A‚ª“®‚©‚È‚¢
	if (A->IsStatic()){
		bPos += vec;
		objB->Transform().Pos(bPos);
	}
	//B‚ª“®‚©‚È‚¢
	else if (B->IsStatic()){
		aPos -= vec;
		objA->Transform().Pos(aPos);
	}
	//—¼•û“®‚­
	else{
		aPos -= vec / 2;
		objA->Transform().Pos(aPos);
		bPos += vec / 2;
		objB->Transform().Pos(bPos);
	}
}