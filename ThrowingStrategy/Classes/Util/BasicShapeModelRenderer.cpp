//************************************************/
//* @file  :BasicShapeRenderer.h
//* @brief :��{�I�ȗ��̂�`�悷��
//* @date  :2017/11/10
//* @author:S.Katou
//************************************************/
#include "BasicShapeModelRenderer.h"

#include <SL_ConversionTK.h>
#include "../Main/SL_Graphics.h"

/// <summary>
/// ���̕`��
/// </summary>
void BasicShapeRenderer::DrawCube(const Matrix & world, const Matrix & view, const Matrix & proj)
{
	if (!m_cube){
		auto context = ShunLib::Graphics::GetInstance()->DeviceContext();

		m_cube = DirectX::GeometricPrimitive::CreateBox(context, ShunLib::ConvertTK(Vec3(1.0f, 1.0f, 1.0f)));
	}

	m_cube->Draw(ShunLib::ConvertTK(world), ShunLib::ConvertTK(view), ShunLib::ConvertTK(proj));
}

/// <summary>
/// ���̕`��
/// </summary>
void BasicShapeRenderer::DrawSphere(const Matrix & world, const Matrix & view, const Matrix & proj)
{
	if (!m_sphere) {
		auto context = ShunLib::Graphics::GetInstance()->DeviceContext();

		m_sphere = DirectX::GeometricPrimitive::CreateSphere(context);
	}

	m_sphere->Draw(ShunLib::ConvertTK(world), ShunLib::ConvertTK(view), ShunLib::ConvertTK(proj));
}

/// <summary>
/// �e�B�[�|�b�g�̕`��
/// </summary>
void BasicShapeRenderer::DrawTeapot(const Matrix & world, const Matrix & view, const Matrix & proj)
{
	if (!m_teapot) {
		auto context = ShunLib::Graphics::GetInstance()->DeviceContext();

		m_teapot = DirectX::GeometricPrimitive::CreateTeapot(context);
	}

	m_teapot->Draw(ShunLib::ConvertTK(world), ShunLib::ConvertTK(view), ShunLib::ConvertTK(proj));
}
