//************************************************/
//* @file  :SL_Shape.h
//* @brief :�����蔻��p�̌`��N���X�܂Ƃ�
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"

//�����蔻��
bool ShunLib::Collision(IShape* A, IShape* B)
{
	if (A->Type() == SHAPE_TYPE::SPHERE)
	{
		Sphere* a = dynamic_cast<Sphere*>(A);

		if (B->Type() == SHAPE_TYPE::SPHERE)
		{
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}
	}
	return false;
}

//�����蔻��p
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// ���S���W�Ԃ̋������v�Z
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// ���a�̘a
	float rad = A.Radius() + B.Radius();
	rad *= rad;

	// ���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (dist > rad)
	{
		return false;
	}

	return true;
}