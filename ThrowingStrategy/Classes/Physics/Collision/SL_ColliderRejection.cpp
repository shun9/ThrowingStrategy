//************************************************/
//* @file  :SL_ColliderRejection.h
//* @brief :�r�ˏ����@�Փˉ���
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// �r�ˏ����@�����m
/// </summary>
void CollisionManager::Rejection(SphereCollider* A, SphereCollider* B)
{
	//�����Ȃ��ғ��m�Ȃ牽�����Ȃ�
	if (A->IsStatic() && B->IsStatic()) {
		return;
	}

	Sphere* a = A->Shape();
	Sphere* b = B->Shape();
	ObjectBase* objA = A->Parent();
	ObjectBase* objB = B->Parent();

	//A����B�֌������x�N�g��
	Vec3 distV = b->CenterPoint() - a->CenterPoint();

	//�������Ă��鋗��
	float hitDist = (a->Scale().m_x + b->Scale().m_x) - distV.Length();

	//�������Ă��鋗���𔼕�����������
	objA->Transform().Pos(objA->Transform().Pos() - (distV.Normalize()*(hitDist / 2.0f)));
	objB->Transform().Pos(objB->Transform().Pos() + (distV.Normalize()*(hitDist / 2.0f)));
}

/// <summary>
/// �r�ˏ����@�����m
/// </summary>
void CollisionManager::Rejection(BoxCollider * A, BoxCollider * B, const Vec3& offset)
{
	//�����Ȃ��ғ��m�Ȃ牽�����Ȃ�
	if (A->IsStatic() && B->IsStatic()) {
		return;
	}

	Vec3 aPos = A->Parent()->Transform().Pos();
	Vec3 bPos = B->Parent()->Transform().Pos();
	ObjectBase* objA = B->Parent();
	ObjectBase* objB = B->Parent();

	//�ŏ��̒l�Ŕr�˂���
	//X���ŏ��̏ꍇ
	if (offset.m_x < offset.m_y && offset.m_x < offset.m_z){
		//A�������Ȃ�
		if (A->IsStatic()) {
			bPos.m_x += offset.m_x;
			objB->Transform().Pos(bPos);
		}
		//B�������Ȃ�
		else if (B->IsStatic()) {
			aPos.m_x -= offset.m_x;
			objA->Transform().Pos(aPos);
		}
		//��������
		else {
			aPos.m_x -= offset.m_x / 2;
			objA->Transform().Pos(aPos);
			bPos.m_x += offset.m_x / 2;
			objB->Transform().Pos(bPos);
		}

	}
	//Y���ŏ��̏ꍇ
	else if (offset.m_y < offset.m_z){
		//A�������Ȃ�
		if (A->IsStatic()) {
			bPos.m_y += offset.m_y;
			objB->Transform().Pos(bPos);
		}
		//B�������Ȃ�
		else if (B->IsStatic()) {
			aPos.m_y -= offset.m_y;
			objA->Transform().Pos(aPos);
		}
		//��������
		else {
			aPos.m_y -= offset.m_y / 2;
			objA->Transform().Pos(aPos);
			bPos.m_y += offset.m_y / 2;
			objB->Transform().Pos(bPos);
		}
	}
	//Z���ŏ��̏ꍇ
	else{
		//A�������Ȃ�
		if (A->IsStatic()) {
			bPos.m_z += offset.m_z;
			objB->Transform().Pos(bPos);
		}
		//B�������Ȃ�
		else if (B->IsStatic()) {
			aPos.m_z -= offset.m_z;
			objA->Transform().Pos(aPos);
		}
		//��������
		else {
			aPos.m_z -= offset.m_z / 2;
			objA->Transform().Pos(aPos);
			bPos.m_z += offset.m_z / 2;
			objB->Transform().Pos(bPos);
		}
	}

}

/// <summary>
/// �r�ˏ����@���Ƌ�
/// </summary>
void CollisionManager::Rejection(SphereCollider * A, BoxCollider * B, const Vec3& closestPoint)
{
	//�����Ȃ��ғ��m�Ȃ牽�����Ȃ�
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

	//A�������Ȃ�
	if (A->IsStatic()){
		bPos += vec;
		objB->Transform().Pos(bPos);
	}
	//B�������Ȃ�
	else if (B->IsStatic()){
		aPos -= vec;
		objA->Transform().Pos(aPos);
	}
	//��������
	else{
		aPos -= vec / 2;
		objA->Transform().Pos(aPos);
		bPos += vec / 2;
		objB->Transform().Pos(bPos);
	}
}