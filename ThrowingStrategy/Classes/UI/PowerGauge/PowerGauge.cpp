//************************************************/
//* @file  :PowerGauge.cpp
//* @brief :パワーゲージ
//* @date  :2018/01/29
//* @author:S.Katou
//************************************************/
#include "PowerGauge.h"
#include "../UIResourceHolder.h"
#include "../../Util/SL_Camera.h"

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
PowerGauge::PowerGauge():
	m_parent(nullptr),
	m_power(0.0f),
	m_offset(Vec3::UnitZ)
{
	Scale(Vec3(3.5f, 1.0f, 0.5f));
}

/// <summary>
/// デストラクタ
/// </summary>
PowerGauge::~PowerGauge()
{
}

/// <summary>
/// 更新
/// </summary>
void PowerGauge::Update()
{
	if (m_parent != nullptr)
	{
		//使用しているかどうか
		m_isEnable = m_parent->IsEnable();

		//位置を合わせる
		Pos(m_parent->WorldPos());

		//方向をカメラに合わせる
		//CalcRot();
	}
}

/// <summary>
/// 描画
/// </summary>
void PowerGauge::Render()
{
	//使用していたら描画
	if (m_isEnable)
	{
		auto camera = ShunLib::MainCamera::GetInstance();
		auto texHolder = UIResourceHolder::GetInstance();

		//パワーゲージを描画
		texHolder->GetTexture(UI_TEXTURE_LIST::ORANGE_GAUGE)->Draw(CalcMat(), camera->ViewMat(), camera->ProjMat());
	}
}

/// <summary>
/// 行列の計算をする
/// </summary>
Matrix PowerGauge::CalcMat()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	Matrix w;

	//残りHPの割合
	float ratio = m_power / Parent()->Data().Power();

	//残りHPの割合によって拡大率を変更
	Vec3 scale = Scale();
	scale.m_x *= ratio;
	w *= Matrix::CreateScale(scale);

	//親とのずれ
	w *= Matrix::CreateTranslation(Offset());

	//回転
	w *= Matrix::CreateRotationZ(Rot().m_z);
	w *= Matrix::CreateRotationX(Rot().m_x);
	w *= Matrix::CreateRotationY(Rot().m_y);

	//位置　左詰めする
	Vec3 pos = Pos();
	pos.m_x -= (1.0f - ratio) * (Scale().m_x / 2.0f);
	w *= Matrix::CreateTranslation(pos);

	return w;
}
