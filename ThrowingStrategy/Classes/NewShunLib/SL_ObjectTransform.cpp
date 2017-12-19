//************************************************/
//* @file  :ObjectTransform.cpp
//* @brief :3Dオブジェクトの基本情報
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#include "SL_ObjectTransform.h"

using namespace ShunLib;

/// <summary>
/// 行列の計算
/// </summary>
/// <returns>計算結果</returns>
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
