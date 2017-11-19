//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :オブジェクト
//* @date  :2017/11/15
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"

//全てのオブジェクトの親
//全てのオブジェクトをここに紐づける
ObjectBase* ObjectBase::ROOT_OBJECT;

void ObjectBase::InitializeRootObject()
{
	ROOT_OBJECT = new ObjectBase(true);
	ObjectBase::ROOT_OBJECT->Type(ROOT);
	ObjectBase::ROOT_OBJECT->LocalPos(ShunLib::Vec3(0.0f, 0.0f, 0.0f));
}

void ObjectBase::FinalizeRootObject()
{
	SAFE_DELETE(ROOT_OBJECT);
}


/// <summary>
/// 親を設定する
/// </summary>
void ObjectBase::SetParent(ObjectBase * parent)
{
	if (m_parent != nullptr)m_parent->RemoveChild(this);
	m_parent = parent;
	//親が存在し、ルートではないとき親データを影響させる
	if (parent != nullptr && parent->Type() != ROOT) {
		//座標を相対的に決定
		this->LocalPos(this->LocalPos() - m_parent->WorldPos());
		this->Rotation(ShunLib::Vec3::Zero);
	}
}

/// <summary>
/// 指定した子を削除する
/// </summary>
void ObjectBase::RemoveChild(ObjectBase * child)
{
	if (m_children.empty())return;

	auto tmpChild = std::find(m_children.begin(), m_children.end(), child);

	if (tmpChild != m_children.end()) {
		m_children.erase(tmpChild);
		m_children.shrink_to_fit();
		//親の情報を子に渡す
		child->LocalPos(child->LocalPos() + this->WorldPos());
	}
}

/// <summary>
/// 移動させる
/// </summary>
void ObjectBase::Move()
{
	using namespace ShunLib;
	auto timer = MyStepTimer::GetInstance();

	//移動速度を制限
	if (this->Velocity().Length() > this->Spd()) {
		this->Velocity(this->Velocity().Normalize()*this->Spd());
	}

	//移動
	m_pos += this->Velocity() * timer->GetElapsedSeconds();

	//向いている方向を計算する
	if (this->Velocity().Length() > 1.0f)
	{
		float rotY = ShunLib::ToAngle(std::atan2(this->Velocity().m_z, this->Velocity().m_x)) - 90.0f;
		m_rotation.m_y = rotY;
	}


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

	world *= CalcMat();

	//モデルが存在するならば描画
	if (data.model) {
		//モデル描画
		data.model->Draw(world, view, proj);
	}

	//子の描画
	for (auto& v : m_children) {
		v->Render(world, view, proj);
	}
}

/// <summary>
/// 自身の行列を計算する
/// </summary>
ShunLib::Matrix ObjectBase::CalcMat()
{
	Matrix m;

	//拡大　縮小
	m *= Matrix::CreateScale(m_scale);

	//ロール ピッチ ヨー
	m *= Matrix::CreateRotationZ(m_rotation.m_z);
	m *= Matrix::CreateRotationX(m_rotation.m_x);
	m *= Matrix::CreateRotationY(m_rotation.m_y);

	//移動
	m *= Matrix::CreateTranslation(this->LocalPos());

	return m;
}
