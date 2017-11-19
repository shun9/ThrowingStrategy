//************************************************/
//* @file  :Unit.h
//* @brief :��������郆�j�b�g
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

struct FlyingData;
class Unit :public StateObject<Unit>
{
private:
	int m_type;
	ShunLib::SphereCollider* m_collider;

public:
	Unit():StateObject(this) {}
	~Unit() {}

	//�������@�I��
	void Initialize()override;
	void Finalize()override;

	//�����j�b�g�Ɏ����グ����
	void ToBeLifted();

	//�����j�b�g�ɓ�������
	void ToBeThrow(const FlyingData& data);
};