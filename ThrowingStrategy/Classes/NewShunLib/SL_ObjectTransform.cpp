//************************************************/
//* @file  :ObjectTransform.cpp
//* @brief :3D�I�u�W�F�N�g�̊�{���
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_ObjectTransform.h"

using namespace ShunLib;

/// <summary>
/// �s��̌v�Z
/// </summary>
/// <returns>�v�Z����</returns>
const Matrix & ObjectTransform::CalcMat()
{
	m_world = Matrix::Identity;

	m_world *= Matrix::CreateScale(m_scale);

	m_world *= Matrix::CreateRotationZ(m_rotation.m_z);
	m_world *= Matrix::CreateRotationX(m_rotation.m_x);
	m_world *= Matrix::CreateRotationY(m_rotation.m_y);

	m_world *= Matrix::CreateTranslation(m_pos);

	return m_world;
}
