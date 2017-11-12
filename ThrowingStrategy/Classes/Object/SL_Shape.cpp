//************************************************/
//* @file  :SL_Shape.h
//* @brief :当たり判定用の形状クラスまとめ
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"

//当たり判定
bool ShunLib::Collision(IShape* A, IShape* B)
{
	//同じもの同士
	if (A->Type() == B->Type())
	{
		//球と球
		if (A->Type() == SHAPE_TYPE::SPHERE)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}

		//箱と箱
		if (A->Type() == SHAPE_TYPE::BOX)
		{
			Box* a = dynamic_cast<Box*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//片方が球
	if (A->Type() == SHAPE_TYPE::SPHERE)
	{
		//球と箱
		if (B->Type() == SHAPE_TYPE::BOX)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//片方が箱
	if (A->Type() == SHAPE_TYPE::BOX)
	{
		//箱と球
		if (B->Type() == SHAPE_TYPE::SPHERE)
		{
			Box* a = dynamic_cast<Box*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}
	}

	return false;
}

/*--当たり判定用--*/
//球と球
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// 中心座標間の距離を計算
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// 半径の和
	float rad = A.Scale() + B.Scale();
	rad *= rad;

	// 距離が半径の和より大きければ、当たっていない
	if (dist > rad)
	{
		return false;
	}

	return true;
}

//球と箱
bool ShunLib::operator*(Sphere & A, Box & B)
{
	return false;
}

//箱と球
bool ShunLib::operator*(Box & A, Sphere & B)
{
	return false;
}

//箱と箱
bool ShunLib::operator*(Box & A, Box & B)
{
	return false;
}


//球の描画
void ShunLib::Sphere::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::CreateScale(Scale()*2.0f);
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawSphere(world,camera->ViewMat(),camera->ProjMat());
}

//箱の描画
void ShunLib::Box::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world;
	world = Matrix::CreateScale(this->Size());
	world *= Matrix::CreateScale(Scale());
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawCube(world, camera->ViewMat(), camera->ProjMat());
}
