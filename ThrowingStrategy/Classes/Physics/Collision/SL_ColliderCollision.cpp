#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//�����蔻��
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	bool hit = false;

	//�������̓��m
	if (aType == bType)
	{
		//���Ƌ�
		if (aType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereCollision(A, B, rejection);
		}

		//���Ɣ�
		if (aType == SHAPE_TYPE::BOX)
		{
			hit = BoxCollision(A, B, rejection);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//���Ɣ�
		if (bType == SHAPE_TYPE::BOX)
		{
			hit = SphereAndBoxCollision(A, B, rejection);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::BOX)
	{
		//���Ƌ�
		if (bType == SHAPE_TYPE::SPHERE)
		{
			hit = SphereAndBoxCollision(B, A, rejection);
		}
	}

	//�������Ă�����q�b�g���X�g�ɒǉ� �q�̓����蔻����s��
	if (hit){
		if (B->Parent() != nullptr)A->AddHitList(B->Parent());
		if (A->Parent() != nullptr)B->AddHitList(A->Parent());

		//�q�̓����蔻��
		//������q���m�̓����蔻���2�����Ă���
		//���C���K�v����
		for (auto& var : A->ChildrenCollider()) {
			Collision(var, B);
		}

		for (auto& var : B->ChildrenCollider()) {
			Collision(A, var);
		}
	}

	return hit;
}

/*--�����蔻��p--*/
//���Ƌ�
bool CollisionManager::SphereCollision(ICollider* A, ICollider* B, bool rejection)
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
	if (rejection){
		//CollisionManager::Rejection(A, B);
	}

	return true;
}

//���Ɣ�
bool CollisionManager::SphereAndBoxCollision(ICollider* sphere, ICollider* box, bool rejection)
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

	return true;
}

//���Ɣ�
bool CollisionManager::BoxCollision(ICollider* A, ICollider* B, bool rejection)
{
	Box* a = dynamic_cast<BoxCollider*>(A)->Shape();
	Box* b = dynamic_cast<BoxCollider*>(B)->Shape();

	/*--X���̔���--*/
	if (!(a->MaxX() > b->MinX() && a->MinX() < b->MaxX())) {
		return false;
	}

	/*--Y���̔���--*/
	if (!(a->MaxY() > b->MinY() && a->MinY() < b->MaxY())) {
		return false;
	}

	/*--Z���̔���--*/
	if (!(a->MaxZ() > b->MinZ() && a->MinZ() < b->MaxZ())) {
		return false;
	}

	return true;
}