//************************************************/
//* @file  :SL_Shape.h
//* @brief :�����蔻��p�̌`��N���X�܂Ƃ�
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"

//�����蔻��
bool ShunLib::Collision(IShape* A, IShape* B)
{
	//�������̓��m
	if (A->Type() == B->Type())
	{
		//���Ƌ�
		if (A->Type() == SHAPE_TYPE::SPHERE)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}

		//���Ɣ�
		if (A->Type() == SHAPE_TYPE::BOX)
		{
			Box* a = dynamic_cast<Box*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//�Е�����
	if (A->Type() == SHAPE_TYPE::SPHERE)
	{
		//���Ɣ�
		if (B->Type() == SHAPE_TYPE::BOX)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//�Е�����
	if (A->Type() == SHAPE_TYPE::BOX)
	{
		//���Ƌ�
		if (B->Type() == SHAPE_TYPE::SPHERE)
		{
			Box* a = dynamic_cast<Box*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}
	}

	return false;
}

/*--�����蔻��p--*/
//���Ƌ�
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// ���S���W�Ԃ̋������v�Z
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// ���a�̘a
	float rad = A.Scale() + B.Scale();
	rad *= rad;

	// ���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (dist > rad)
	{
		return false;
	}

	return true;
}

//���Ɣ�
bool ShunLib::operator*(Sphere & A, Box & B)
{
	return false;
}

//���Ƌ�
bool ShunLib::operator*(Box & A, Sphere & B)
{
	return false;
}

//���Ɣ�
bool ShunLib::operator*(Box & A, Box & B)
{
	return false;
}


//���̕`��
void ShunLib::Sphere::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::CreateScale(Scale()*2.0f);
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawSphere(world,camera->ViewMat(),camera->ProjMat());
}

//���̕`��
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
