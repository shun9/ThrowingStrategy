//************************************************/
//* @file  :SL_Shape.cpp
//* @brief :�����蔻��p�̌`��N���X�܂Ƃ�
//* @date  :2017/12/11
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include <SL_Math.h>
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"


/// <summary>
/// �ŒZ���������߂�@���Ɠ_
/// </summary>
/// <param name="A">��</param>
/// <param name="B">�_</param>
/// <param name="buffer">���̍Őڋߓ_���i�[����</param>
/// <returns>�ŒZ����</returns>
float ShunLib::ShortestDistance(const Box & A, const Point & B, Point* buffer)
{
	Vec3 point = B.CenterPoint();

	// �����ׂ̂���̒l���i�[
	float sqLen = 0;

	//�Őڋߓ_
	Vec3 closestPoint;
	closestPoint = point;

	//�_���ŏ��l�`�ő�l�̒��ɂȂ��Ƃ������l������
	//X��
	if (point.m_x < A.MinX()){
		sqLen += ((point.m_x - A.MinX()) * (point.m_x - A.MinX()));

		//�Őڋߓ_
		closestPoint.m_x = A.MinX();
	}
	else if (point.m_x > A.MaxX()){
		sqLen += ((point.m_x - A.MaxX()) * (point.m_x - A.MaxX()));
		//�Őڋߓ_
		closestPoint.m_x = A.MaxX();
	}

	//Y��
	if (point.m_y < A.MinY()) {
		sqLen += ((point.m_y - A.MinY()) * (point.m_y - A.MinY()));

		//�Őڋߓ_
		closestPoint.m_y = A.MinY();
	}
	else if (point.m_y > A.MaxY()) {
		sqLen += ((point.m_y - A.MaxY()) * (point.m_y - A.MaxY()));
		//�Őڋߓ_
		closestPoint.m_y = A.MaxY();
	}

	//Z��
	if (point.m_z < A.MinZ()){
		sqLen += ((point.m_z - A.MinZ()) * (point.m_z - A.MinZ()));

		//�Őڋߓ_
		closestPoint.m_z = A.MinZ();
	}
	else if (point.m_z > A.MaxZ()) {
		sqLen += ((point.m_z - A.MaxZ()) * (point.m_z - A.MaxZ()));
		//�Őڋߓ_
		closestPoint.m_z = A.MaxZ();
	}

	//�Őڋߓ_���K�v�Ȃ�n��
	if (buffer != nullptr){
		buffer->CenterPoint(closestPoint);
	}

	return sqrt(sqLen);
}

/// <summary>
/// ���̕`��
/// </summary>
void ShunLib::Sphere::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::CreateScale(Radius() * 2.0f);
	world *= Matrix::CreateTranslation(CenterPoint());
	shape->DrawSphere(world, camera->ViewMat(), camera->ProjMat());
}

/// <summary>
/// ���̕`��
/// </summary>
void ShunLib::Box::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(Size());
	world *= Matrix::CreateScale(Scale());
	world *= Matrix::CreateTranslation(CenterPoint());
	shape->DrawCube(world, camera->ViewMat(), camera->ProjMat());
}
