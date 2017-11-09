//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :オブジェクト
//* @date  :2017/11/07
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"

/// <summary>
/// 移動させる
/// </summary>
void ObjectBase::Move()
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	//移動
	m_pos += m_velocity * timer->GetElapsedSeconds();
	
	//TODO:向いている方向を計算する


	//摩擦をかける
	m_velocity *= FRICTION;
}

/// <summary>
/// 描画 親用
/// </summary>
void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{
	//親がいる場合はここでは描画しない
	if (m_parent != nullptr)return;

	this->Render(Matrix::Identity, view, proj);
}

/// <summary>
/// 描画 子用
/// </summary>
void ObjectBase::Render(const Matrix & parentWorld, const Matrix & view, const Matrix & proj)
{
	auto data = OBJ_PARAM(this->m_type);

	Matrix world = parentWorld;

	//拡大　縮小
	world *= Matrix::CreateScale(m_scale);

	//ロール ピッチ ヨー
	world *= Matrix::CreateRotationZ(m_rotation.m_y);
	world *= Matrix::CreateRotationX(m_rotation.m_x);
	world *= Matrix::CreateRotationY(m_rotation.m_z);

	//移動
	world *= Matrix::CreateTranslation(m_pos);

	//モデルが存在するならば描画
	if (data.model)
	{
		//モデル描画
		data.model->Draw(world, view, proj);
	}

	//子の描画
	for (auto& v : m_children)
	{
		v->Render(world, view, proj);
	}
}
