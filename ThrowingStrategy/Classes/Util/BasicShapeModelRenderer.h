//************************************************/
//* @file  :BasicShapeRenderer.h
//* @brief :Šî–{“I‚È—§‘Ì‚ð•`‰æ‚·‚é
//* @date  :2017/11/10
//* @author:S.Katou
//************************************************/
#pragma once

#include <GeometricPrimitive.h>
#include <SL_Singleton.h>
#include <SL_Math.h>
#include <SL_Colors.h>

class BasicShapeRenderer : public ShunLib::Singleton<BasicShapeRenderer>
{
	friend ShunLib::Singleton<BasicShapeRenderer>;
private:
	using Matrix = ShunLib::Matrix;
	using Color = ShunLib::Vec4;
	using Vec3 = ShunLib::Vec3;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
	std::unique_ptr<DirectX::GeometricPrimitive> m_teapot;

public:
	void DrawCube(const Matrix& world, const Matrix& view, const Matrix& proj,const Color& color = ShunLib::Colors::WHITE);
	void DrawSphere(const Matrix& world, const Matrix& view, const Matrix& proj, const Color& color = ShunLib::Colors::WHITE);
	void DrawTeapot(const Matrix& world, const Matrix& view, const Matrix& proj, const Color& color = ShunLib::Colors::WHITE);
private:
	BasicShapeRenderer() {}
	~BasicShapeRenderer() {}
};
