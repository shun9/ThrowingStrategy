//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :オブジェクト
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="type"></param>
ObjectBase::ObjectBase(OBJECT_LIST type):
	m_data(type)
{}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBase::~ObjectBase(){

}

/// <summary>
/// 移動させる
/// </summary>
void ObjectBase::Move()
{
	using namespace ShunLib;
	auto timer = MyStepTimer::GetInstance();

	//移動速度を制限
	if (m_transform.Velocity().Length() > m_data.Spd()) {
		m_transform.Velocity(m_transform.Velocity().Normalize()*m_data.Spd());
	}

	//移動
	m_transform.Pos(m_transform.Pos() + m_transform.Velocity() * timer->GetElapsedSeconds());

	//向いている方向を計算する
	//移動中のみ計算
	//Ｙのみ計算　見上げたり見下げたりすることはない
	if (m_transform.Velocity().Length() > 1.0f)
	{
		Vec3 rot = m_transform.Rotation();

		rot.m_y = ToAngle(std::atan2(m_transform.Velocity().m_z, m_transform.Velocity().m_x)) - 90.0f;
		m_transform.Rotation(rot);
	}

	//摩擦をかける
	m_transform.Velocity(m_transform.Velocity() * FRICTION);
}

/// <summary>
/// 描画
/// </summary>
void ObjectBase::Render()
{
}
