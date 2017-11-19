//************************************************/
//* @file  :SL_Shape.cpp
//* @brief :�����蔻��p�̌`��N���X�܂Ƃ�
//* @date  :2017/11/17
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include <SL_Math.h>
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"

float ShunLib::ShortestDistance(const Box & A, const Point & B)
{
	float sqLen = 0;   // �����ׂ̂���̒l���i�[
	Vec3 point = B.CenterPoint();

	//���̒��_�̍ŏ��l�ƍő�l
	Vec3 min, max;
	min.m_x = B.CenterPoint().m_x - (B.Size().m_x / 2.0f);
	min.m_y = B.CenterPoint().m_y - (B.Size().m_y / 2.0f);
	min.m_z = B.CenterPoint().m_z - (B.Size().m_z / 2.0f);

	max.m_x = B.CenterPoint().m_x + (B.Size().m_x / 2.0f);
	max.m_y = B.CenterPoint().m_y + (B.Size().m_y / 2.0f);
	max.m_z = B.CenterPoint().m_z + (B.Size().m_z / 2.0f);

	//�_���ŏ��l�`�ő�l�̒��ɂȂ��Ƃ������l������
	//X��
	if (!(point.m_x > min.m_x && point.m_x < max.m_x))
		sqLen += ((point.m_x - min.m_x) * (point.m_x - min.m_x));

	//Y��
	if (!(point.m_y > min.m_y && point.m_y < max.m_y))
		sqLen += ((point.m_y - min.m_y) * (point.m_y - min.m_y));
	
	//Z��
	if (!(point.m_z > min.m_z && point.m_z < max.m_z))
		sqLen += ((point.m_z - min.m_z) * (point.m_z - min.m_z));

	return sqrt(sqLen);
}

//���̕`��
void ShunLib::Sphere::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::CreateScale(Scale()*2.0f);
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawSphere(world, camera->ViewMat(), camera->ProjMat());
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
