//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :オブジェクト
//* @date  :2018/01/05
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "ObjectModelHolder.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"
#include "../Util/SL_Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="type"></param>
ObjectBase::ObjectBase(OBJECT_LIST type):
	ObjectNode(type),
	m_data(type)
{
	m_data.Init();
}

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
	auto pos = m_transform.Pos() + m_transform.Velocity() * timer->GetElapsedSeconds();
	if(m_data.UseGravity())pos.m_y -= GRAVITY;
	m_transform.Pos(pos);

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
/// 初期化
/// </summary>
void ObjectBase::Initialize()
{
	ObjectNode::Initialize();
	m_data.Init();
}

/// <summary>
/// 更新
/// </summary>
void ObjectBase::Update()
{
	if (m_data.IsDead()) {
		m_isEnable = false;
	}
}

/// <summary>
/// 描画
/// </summary>
void ObjectBase::Render()
{
	auto model = ObjectModelHolder::GetInstance()->GetModel(this);
	auto camera = ShunLib::MainCamera::GetInstance();

	//行列の計算
	m_transform.CalcMat();

	//モデルの描画
	if (model != nullptr)
	{
		//親が存在するなら座標を影響させる
		auto parent = dynamic_cast<ObjectBase*>(m_parent);
		if (parent != nullptr){
			model->Draw(parent->Transform().TransMat() * m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat());
		}
		else {
			model->Draw(m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat());
		}
	}
}
