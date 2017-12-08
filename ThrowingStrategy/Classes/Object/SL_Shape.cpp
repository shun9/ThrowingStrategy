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

	//���̒��_�̍ŏ��l�ƍő�l
	Vec3 min, max;
	min.m_x = A.CenterPoint().m_x - (A.Size().m_x / 2.0f);
	min.m_y = A.CenterPoint().m_y - (A.Size().m_y / 2.0f);
	min.m_z = A.CenterPoint().m_z - (A.Size().m_z / 2.0f);

	max.m_x = A.CenterPoint().m_x + (A.Size().m_x / 2.0f);
	max.m_y = A.CenterPoint().m_y + (A.Size().m_y / 2.0f);
	max.m_z = A.CenterPoint().m_z + (A.Size().m_z / 2.0f);

	//�_���ŏ��l�`�ő�l�̒��ɂȂ��Ƃ������l������
	//X��
	if (!(point.m_x > min.m_x && point.m_x < max.m_x)){
		sqLen += ((point.m_x - min.m_x) * (point.m_x - min.m_x));
	}

	//Y��
	if (!(point.m_y > min.m_y && point.m_y < max.m_y)) {
		sqLen += ((point.m_y - min.m_y) * (point.m_y - min.m_y));
	}
	
	//Z��
	if (!(point.m_z > min.m_z&&point.m_z < max.m_z)){
		sqLen += ((point.m_z - min.m_z) * (point.m_z - min.m_z));
	}

	//�Őڋߓ_���K�v�Ȃ�
	if (buffer != nullptr){
		Vec3 tmp;
		tmp.m_x = ShunLib::Clamp(max.m_x, min.m_x, buffer->CenterPoint().m_x);
		tmp.m_y = ShunLib::Clamp(max.m_y, min.m_y, buffer->CenterPoint().m_y);
		tmp.m_z = ShunLib::Clamp(max.m_z, min.m_z, buffer->CenterPoint().m_z);
		buffer->CenterPoint(tmp);
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

	Matrix world = Matrix::CreateScale(Scale()*2.0f);
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawSphere(world, camera->ViewMat(), camera->ProjMat());
}

/// <summary>
/// ���̕`��
/// </summary>
void ShunLib::Box::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world;
	world = Matrix::CreateScale(this->Size());
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawCube(world, camera->ViewMat(), camera->ProjMat());
}
