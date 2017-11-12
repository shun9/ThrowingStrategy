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

class BasicShapeRenderer : public ShunLib::Singleton<BasicShapeRenderer>
{
	friend ShunLib::Singleton<BasicShapeRenderer>;
private:
	using Matrix = ShunLib::Matrix;
	using Vec3 = ShunLib::Vec3;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
	std::unique_ptr<DirectX::GeometricPrimitive> m_teapot;

public:
	void DrawCube(const Matrix& world, const Matrix& view, const Matrix& proj);
	void DrawSphere(const Matrix& world, const Matrix& view, const Matrix& proj);
	void DrawTeapot(const Matrix& world, const Matrix& view, const Matrix& proj);
private:
	BasicShapeRenderer() {}
	~BasicShapeRenderer() {}
};
