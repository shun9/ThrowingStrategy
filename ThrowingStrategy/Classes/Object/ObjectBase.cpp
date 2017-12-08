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
#include "ObjectModelHolder.h"

//全てのオブジェクトの親
//全てのオブジェクトをここに紐づける
ObjectBase* ObjectBase::ROOT_OBJECT;

void ObjectBase::InitializeRootObject()
{
	ROOT_OBJECT = new ObjectBase(true);
	ObjectBase::ROOT_OBJECT->Type(ObjectConstantNumber::ROOT);
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
	if (parent != nullptr && parent->Type() != ObjectConstantNumber::ROOT) {
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
	//子がいなければ何もしない
	if (m_children.empty())return;

	auto tmpChild = std::find(m_children.begin(), m_children.end(), child);

	if (tmpChild != m_children.end()) {
		//親の情報を子に渡す
		child->LocalPos(child->WorldPos());
		child->Rotation(child->WorldRotation());
		
		//子を切り離す
		m_children.erase(tmpChild);
		m_children.shrink_to_fit();
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


/// /// <summary>
/// 描画 親用
/// </summary>
void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{
	//親がいる場合はここでは描画しない
	if (m_parent != nullptr)return;

	this->RenderChild(view, proj);
}


/// <summary>
/// 描画 子用
/// </summary>
void ObjectBase::RenderChild(const Matrix & view, const Matrix & proj)
{
	auto model = ObjectModelHolder::GetInstance()->GetModel(this);

	//行列更新
	CalcMat();

	//モデルが存在するならば描画
	if (model != nullptr) {
		//モデル描画
		model->Draw(m_world, view, proj);
	}

	//子の描画
	for (auto& v : m_children) {
		v->RenderChild(view, proj);
	}
}


/// <summary>
/// 自身の行列を計算する
/// </summary>
void ObjectBase::CalcMat()
{
	m_world = Matrix::Identity;

	//拡大　縮小
	m_world *= Matrix::CreateScale(this->Scale());

	//子の回転
	m_world *= Matrix::CreateRotationZ(this->Rotation().m_z);
	m_world *= Matrix::CreateRotationX(this->Rotation().m_x);
	m_world *= Matrix::CreateRotationY(this->Rotation().m_y);

	//子の移動
	m_world *= Matrix::CreateTranslation(this->LocalPos());

	//親の行列を影響させる
	ObjectBase* parent = this->Parent();
	if (parent != nullptr){
		m_world *= m_parent->World();
	}
}
