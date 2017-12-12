//************************************************/
//* @file  :SL_ColliderRejection.h
//* @brief :�r�ˏ����@�Փˉ���
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

void ShunLib::CollisionManager::Rejection(SphereCollider* A, SphereCollider* B)
{
	Sphere* a = A->Shape();
	Sphere* b = B->Shape();
	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();

	//A����B�֌������x�N�g��
	Vec3 distV = b->CenterPoint() - a->CenterPoint();

	//�������Ă��鋗��
	float hitDist = (a->Scale().m_x + b->Scale().m_x) - distV.Length();

	//�������Ă��鋗���𔼕�����������
	objA->Pos(objA->Pos() - (distV.Normalize()*(hitDist / 2.0f)));
	objB->Pos(objB->Pos() + (distV.Normalize()*(hitDist / 2.0f)));
}

void ShunLib::CollisionManager::Rejection(BoxCollider * A, BoxCollider * B)
{

}

void ShunLib::CollisionManager::Rejection(SphereCollider * A, BoxCollider * B)
{

}