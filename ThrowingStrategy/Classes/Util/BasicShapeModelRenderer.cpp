//************************************************/
//* @file  :BasicShapeRenderer.h
//* @brief :基本的な立体を描画する
//* @date  :2017/11/10
//* @author:S.Katou
//************************************************/
#include "BasicShapeModelRenderer.h"

#include <SL_ConversionTK.h>
#include "../Main/SL_Graphics.h"

using namespace ShunLib;

/// <summary>
/// 箱の描画
/// </summary>
void BasicShapeRenderer::DrawCube(const Matrix & world, const Matrix & view, const Matrix & proj, const Color& color)
{
	if (!m_cube){
		auto context = Graphics::GetInstance()->DeviceContext();

		m_cube = DirectX::GeometricPrimitive::CreateBox(context, ConvertTK(Vec3(1.0f, 1.0f, 1.0f)));
	}

	m_cube->Draw(ConvertTK(world), ConvertTK(view), ConvertTK(proj), ConvertTK(color));
}

/// <summary>
/// 球の描画
/// </summary>
void BasicShapeRenderer::DrawSphere(const Matrix & world, const Matrix & view, const Matrix & proj, const Color& color)
{
	if (!m_sphere) {
		auto context = Graphics::GetInstance()->DeviceContext();

		m_sphere = DirectX::GeometricPrimitive::CreateSphere(context);
	}

	m_sphere->Draw(ConvertTK(world), ConvertTK(view), ConvertTK(proj), ConvertTK(color));
}

/// <summary>
/// ティーポットの描画
/// </summary>
void BasicShapeRenderer::DrawTeapot(const Matrix & world, const Matrix & view, const Matrix & proj, const Color& color)
{
	if (!m_teapot) {
		auto context = Graphics::GetInstance()->DeviceContext();

		m_teapot = DirectX::GeometricPrimitive::CreateTeapot(context);
	}

	m_teapot->Draw(ConvertTK(world), ConvertTK(view), ConvertTK(proj), ConvertTK(color));
}
