//************************************************/
//* @file  :SL_Shape.h
//* @brief :当たり判定用の形状クラスまとめ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"

//当たり判定
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

//当たり判定用
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// 中心座標間の距離を計算
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// 半径の和
	float rad = A.Radius() + B.Radius();
	rad *= rad;

	// 距離が半径の和より大きければ、当たっていない
	if (dist > rad)
	{
		return false;
	}

	return true;
}