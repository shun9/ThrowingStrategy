//************************************************/
//* @file  :SL_Shape.cpp
//* @brief :当たり判定用の形状クラスまとめ
//* @date  :2017/12/11
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include <SL_Math.h>
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"


/// <summary>
/// 最短距離を求める　箱と点
/// </summary>
/// <param name="A">箱</param>
/// <param name="B">点</param>
/// <param name="buffer">箱の最接近点を格納する</param>
/// <returns>最短距離</returns>
float ShunLib::ShortestDistance(const Box & A, const Point & B, Point* buffer)
{
	Vec3 point = B.CenterPoint();

	// 長さのべき乗の値を格納
	float sqLen = 0;

	//最接近点
	Vec3 closestPoint;
	closestPoint = point;

	//点が最小値～最大値の中にないとき差を考慮する
	//X軸
	if (point.m_x < A.MinX()){
		sqLen += ((point.m_x - A.MinX()) * (point.m_x - A.MinX()));

		//最接近点
		closestPoint.m_x = A.MinX();
	}
	else if (point.m_x > A.MaxX()){
		sqLen += ((point.m_x - A.MaxX()) * (point.m_x - A.MaxX()));
		//最接近点
		closestPoint.m_x = A.MaxX();
	}

	//Y軸
	if (point.m_y < A.MinY()) {
		sqLen += ((point.m_y - A.MinY()) * (point.m_y - A.MinY()));

		//最接近点
		closestPoint.m_y = A.MinY();
	}
	else if (point.m_y > A.MaxY()) {
		sqLen += ((point.m_y - A.MaxY()) * (point.m_y - A.MaxY()));
		//最接近点
		closestPoint.m_y = A.MaxY();
	}

	//Z軸
	if (point.m_z < A.MinZ()){
		sqLen += ((point.m_z - A.MinZ()) * (point.m_z - A.MinZ()));

		//最接近点
		closestPoint.m_z = A.MinZ();
	}
	else if (point.m_z > A.MaxZ()) {
		sqLen += ((point.m_z - A.MaxZ()) * (point.m_z - A.MaxZ()));
		//最接近点
		closestPoint.m_z = A.MaxZ();
	}

	//最接近点が必要なら渡す
	if (buffer != nullptr){
		buffer->CenterPoint(closestPoint);
	}

	return sqrt(sqLen);
}

/// <summary>
/// 球の描画
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
/// 箱の描画
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
