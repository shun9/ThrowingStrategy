//************************************************/
//* @file  :SL_Shape.h
//* @brief :“–‚½‚è”»’è—p‚ÌŒ`óƒNƒ‰ƒX‚Ü‚Æ‚ß
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"

//“–‚½‚è”»’è
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

//“–‚½‚è”»’è—p
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// ’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// ”¼Œa‚Ì˜a
	float rad = A.Radius() + B.Radius();
	rad *= rad;

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > rad)
	{
		return false;
	}

	return true;
}