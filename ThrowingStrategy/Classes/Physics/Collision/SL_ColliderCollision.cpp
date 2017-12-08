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
	float rad = a->Shape()->Scale() + b->Shape()->Scale();

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
	float dist = ShortestDistance((*b->Shape()), point,&closestPoint);

	//�ŒZ���������̔��a�����傫�������瓖�����Ă��Ȃ�
	if (dist > s->Shape()->Scale()) {
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
	float aXRight = a->CenterPoint().m_x + (a->Size().m_x / 2.0f);//A��X���̉E��(+����)
	float aXLeft  = a->CenterPoint().m_x - (a->Size().m_x / 2.0f);//A��X���̍���(-����)

	float bXRight = b->CenterPoint().m_x + (b->Size().m_x / 2.0f);//B��X���̉E��(+����)
	float bXLeft  = b->CenterPoint().m_x - (b->Size().m_x / 2.0f);//B��X���̍���(-����)

	if (!(aXRight > bXLeft && aXLeft < bXRight)) {
		return false;
	}

	/*--Y���̔���--*/
	float aYTop    = a->CenterPoint().m_y + (a->Size().m_y / 2.0f);//A��Y���̏㑤(+����)
	float aYBottom = a->CenterPoint().m_y - (a->Size().m_y / 2.0f);//A��Y���̉���(-����)

	float bYTop    = b->CenterPoint().m_y + (b->Size().m_y / 2.0f);//B��Y���̏㑤(+����)
	float bYBottom = b->CenterPoint().m_y - (b->Size().m_y / 2.0f);//B��Y���̉���(-����)

	if (!(aYTop > bYBottom && aYBottom < bYTop)) {
		return false;
	}

	/*--Z���̔���--*/
	float aZFront = a->CenterPoint().m_z + (a->Size().m_z / 2.0f);//A��Z���̉����@(+����)
	float aZBack  = a->CenterPoint().m_z - (a->Size().m_z / 2.0f);//A��Z���̎�O��(-����)

	float bZFront = b->CenterPoint().m_z + (b->Size().m_z / 2.0f);//B��Z���̉����@(+����)
	float bZBack  = b->CenterPoint().m_z - (b->Size().m_z / 2.0f);//B��Z���̎�O��(-����)

	if (!(aZFront > bZBack && aZBack < bZFront)) {
		return false;
	}

	return true;
}