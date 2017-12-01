#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/SL_Shape.h"

using namespace ShunLib;

//�����蔻��
bool CollisionManager::Collision(ICollider* A, ICollider* B, bool rejection)
{
	SHAPE_TYPE aType = A->Type();
	SHAPE_TYPE bType = B->Type();

	//�������̓��m
	if (aType == bType)
	{
		//���Ƌ�
		if (aType == SHAPE_TYPE::SPHERE)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(a, b, rejection);
		}

		//���Ɣ�
		if (aType == SHAPE_TYPE::BOX)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::SPHERE)
	{
		//���Ɣ�
		if (bType == SHAPE_TYPE::BOX)
		{
			SphereCollider* a = dynamic_cast<SphereCollider*>(A);
			BoxCollider* b = dynamic_cast<BoxCollider*>(B);
			return Collision(a, b, rejection);
		}
	}

	//�Е�����
	if (aType == SHAPE_TYPE::BOX)
	{
		//���Ƌ�
		if (bType == SHAPE_TYPE::SPHERE)
		{
			BoxCollider* a = dynamic_cast<BoxCollider*>(A);
			SphereCollider* b = dynamic_cast<SphereCollider*>(B);
			return Collision(b, a, rejection);
		}
	}

	return false;
}

/*--�����蔻��p--*/
//���Ƌ�
bool CollisionManager::Collision(SphereCollider* A, SphereCollider* B, bool rejection)
{
	// ���S���W�Ԃ̋������v�Z
	Vec3 distV = B->Shape()->CenterPoint() - A->Shape()->CenterPoint();
	float dist = distV.Length();

	// ���a�̘a
	float rad = A->Shape()->Scale() + B->Shape()->Scale();

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
bool CollisionManager::Collision(SphereCollider* A, BoxCollider* B, bool rejection)
{
	Point point;
	point.CenterPoint(A->Shape()->CenterPoint());
	
	//���̒��S�_�Ɣ��̍ŒZ�������o��
	float dist = ShortestDistance((*B->Shape()), point);

	//�ŒZ���������̔��a�����傫�������瓖�����Ă��Ȃ�
	if (dist > A->Shape()->Scale()) {
		return false;
	}

	return true;
}

//���Ɣ�
bool CollisionManager::Collision(BoxCollider* A, BoxCollider* B, bool rejection)
{
	Box* a = A->Shape();
	Box* b = B->Shape();

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