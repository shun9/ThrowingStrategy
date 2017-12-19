//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :オブジェクト
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "ObjectFactory.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"
#include "ObjectModelHolder.h"

//全てのオブジェクトの親
//全てのオブジェクトをここに紐づける
ObjectBase* ObjectBase::ROOT_OBJECT;

/// <summary>
/// ルートオブジェクトの初期化
/// </summary>
void ObjectBase::InitializeRootObject()
{
	ROOT_OBJECT = new ObjectBase();
	ObjectBase::ROOT_OBJECT->Type(ObjectConstantNumber::ROOT);
	ObjectBase::ROOT_OBJECT->LocalPos(ShunLib::Vec3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// ルートオブジェクトの終了処理
/// </summary>
void ObjectBase::FinalizeRootObject()
{
	SAFE_DELETE(ROOT_OBJECT);
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBase::~ObjectBase()
{
	//this->Finalize();

	//子も同時に削除
	for (int i = 0; i < (int)(m_children.size()); i++) {
		m_children.at(i)->Finalize();
		ObjectFactory::GetInstance()->Delete(m_children.at(i));
	}

	//親がいるなら切り離す
	if (Parent() != nullptr) {
		Parent()->RemoveChild(this);
	}
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
/// 子を追加
/// </summary>
void ObjectBase::AddChild(ObjectBase * child)
{
	m_children.push_back(child);
	child->SetParent(this);
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
/// 更新
/// </summary>
void ObjectBase::Update()
{
	//更新中の変更によってアクセス違反が起こるため
	//コンテナのサイズで回す
	for (int i = 0; i < (int)m_children.size();i++) {
		m_children.at(i)->Update();
	}

	//死んでいるオブジェクトを削除
	for (auto& itr = m_children.begin(); itr != m_children.end();)
	{
		//死んでいたら削除
		if ((*itr)->IsDead()) {
			(*itr)->Finalize();
			ObjectFactory::GetInstance()->Delete((*itr));
			//itr = m_children.erase(itr);
			m_children.erase(itr);
		}
		else {
			++itr;
		}
	}

	////死んでいるオブジェクトを削除
	//for (int i = 0; i < (int)m_children.size();)
	//{
	//	//死んでいたら削除
	//	if (m_children.at(i)->IsDead()) {
	//		m_children.at(i)->Finalize();
	//		ObjectFactory::GetInstance()->Delete(m_children.at(i));
	//		m_children.erase(m_children.begin() + i);
	//	}
	//	else {
	//		i++;
	//	}
	//}
}

/// <summary>
/// ビジターを受け入れる
/// </summary>
/// <param name="visitor"></param>
void ObjectBase::Accept(ShunLib::Visitor * visitor)
{
	visitor->Visit(this);
	for (auto& v : m_children) {
		visitor->Visit(v);
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
