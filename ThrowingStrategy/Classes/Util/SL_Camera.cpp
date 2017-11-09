//************************************************/
//* @file  :SL_Camera.cpp
//* @brief :ï`âÊópÉJÉÅÉâ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Camera.h"


ShunLib::MainCamera::MainCamera():
	m_pos   (Vec3(0.0f, 1.0f, 0.0f)),
	m_target(Vec3(0.0f, 0.0f, 3.0f)),
	m_up    (Vec3::UnitY),
	m_fov   (45.0f),
	m_aspect(800.0f / 600.0f),
	m_near  (1.0f),
	m_far   (200.0f)
{
	m_view = Matrix::CreateLookAt(m_pos, m_target, m_up);
	m_proj = Matrix::CreateProj(m_fov, m_aspect, m_near, m_far);
}

ShunLib::MainCamera::~MainCamera()
{

}

void ShunLib::MainCamera::Update()
{
	m_view = Matrix::CreateLookAt(m_pos, m_target, m_up);
	m_proj = Matrix::CreateProj(m_fov, m_aspect, m_near, m_far);
}