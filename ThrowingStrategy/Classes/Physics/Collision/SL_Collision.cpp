#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//�����蔻��
bool CollisionManager::Collision(ICollider* A, ICollider* B)
{
	SHAPE_TYPE aType = A->ShapeType();
	SHAPE_TYPE bType = B->ShapeType();

	bool hit = false;

	//�������̓��m
	if (aType == bType)
	{
		//���Ƌ�
		if (aType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereCollision(A, B);
		}

		//���Ɣ�
		if (aType == SHAPE_TYPE::BOX)
		{
			hit = BoxCollision(A, B);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//���Ɣ�
		if (bType == SHAPE_TYPE::BOX)
		{
			hit = SphereAndBoxCollision(A, B);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::BOX)
	{
		//���Ƌ�
		if (bType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereAndBoxCollision(B, A);
		}
	}

	//�������Ă�����q�b�g���X�g�ɒǉ�
	if (hit){
		if (B->HitParent() != nullptr)A->AddHitList(B->HitParent());
		if (A->HitParent() != nullptr)B->AddHitList(A->HitParent());
	}

	return hit;
}

/*--�����蔻��p--*/
//���Ƌ�
bool CollisionManager::SphereCollision(ICollider* A, ICollider* B)
{
	SphereCollider* a = dynamic_cast<SphereCollider*>(A);
	SphereCollider* b = dynamic_cast<SphereCollider*>(B);

	// ���S���W�Ԃ̋������v�Z
	Vec3 distV = b->Shape()->CenterPoint() - a->Shape()->CenterPoint();
	float dist = distV.Length();

	// ���a�̘a
	float rad = a->Shape()->Radius() + b->Shape()->Radius();

	// ���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (dist > rad)
	{
		return false;
	}

	//�r�ˏ���
	if (a->ColliderType() != COLLIDER_LAYER::TRIGGER && b->ColliderType() != COLLIDER_LAYER::TRIGGER){
		CollisionManager::Rejection(a,b);
	}

	return true;
}

//���Ɣ�
bool CollisionManager::SphereAndBoxCollision(ICollider* sphere, ICollider* box)
{
	SphereCollider* s = dynamic_cast<SphereCollider*>(sphere);
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);

	//���̒��S�_
	Point point;
	point.CenterPoint(s->Shape()->CenterPoint());

	//�Őڋߓ_
	Point closestPoint;

	//���̒��S�_�Ɣ��̍ŒZ�������o��
	float dist = ShortestDistance(*b->Shape(), point,&closestPoint);

	//�ŒZ���������̔��a�����傫�������瓖�����Ă��Ȃ�
	if (dist > s->Shape()->Radius()) {
		return false;
	}

	//�r�ˏ���
	if (s->ColliderType() != COLLIDER_LAYER::TRIGGER && b->ColliderType() != COLLIDER_LAYER::TRIGGER) {
		CollisionManager::Rejection(s,b, closestPoint.CenterPoint());
	}

	return true;
}

//���Ɣ�
bool CollisionManager::BoxCollision(ICollider* A, ICollider* B)
{
	Box* a = dynamic_cast<BoxCollider*>(A)->Shape();
	Box* b = dynamic_cast<BoxCollider*>(B)->Shape();

	bool isHit = true;
	Vec3 offset = Vec3::Zero;

	/*--X���̔���--*/
	if (!(a->MaxX() > b->MinX() && a->MinX() < b->MaxX())) {
		offset.m_x = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	/*--Y���̔���--*/
	if (!(a->MaxY() > b->MinY() && a->MinY() < b->MaxY())) {
		offset.m_y = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	/*--Z���̔���--*/
	if (!(a->MaxZ() > b->MinZ() && a->MinZ() < b->MaxZ())) {
		offset.m_z = (a->LengthX() + b->LengthX()) / 2;
		isHit = false;
	}

	//�r�ˏ���
	if (A->ColliderType() != COLLIDER_LAYER::TRIGGER && B->ColliderType() != COLLIDER_LAYER::TRIGGER) {
		//CollisionManager::Rejection(dynamic_cast<BoxCollider*>(A), dynamic_cast<BoxCollider*>(B), offset);
	}

	return isHit;
}