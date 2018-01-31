//************************************************/
//* @file  :HPGauge.cpp
//* @brief :HPゲージ
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "HPGauge.h"

#include <SL_MacroConstants.h>
#include <SL_Conversion.h>
#include "../UIConstantNumber.h"
#include "../UIResourceHolder.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
HPGauge::HPGauge() :
	m_parent(nullptr),
	m_offset(Vec3::UnitZ)
{
	Scale(UIConstantNumber::HP_GAUGE_CONSTANT::SCALE);
}

/// <summary>
/// デストラクタ
/// </summary>
HPGauge::~HPGauge()
{
}

/// <summary>
/// 更新
/// </summary>
void HPGauge::Update()
{
	if (m_parent != nullptr)
	{
		//使用しているかどうか
		m_isEnable = m_parent->IsEnable();

		//位置を合わせる
		Pos(m_parent->WorldPos());

		//方向をカメラに合わせる
		CalcRot();
	}
}

/// <summary>
/// 描画
/// </summary>
void HPGauge::Render()
{
	//使用していたら描画
	if (m_isEnable)
	{
		auto camera = ShunLib::MainCamera::GetInstance();
		auto texHolder = UIResourceHolder::GetInstance();

		//赤のゲージを描画
		texHolder->GetTexture(UI_TEXTURE_LIST::RED_GAUGE)->Draw(CalcRedMat(), camera->ViewMat(), camera->ProjMat());

		//緑のゲージを描画
		texHolder->GetTexture(UI_TEXTURE_LIST::GREEN_GAUGE)->Draw(CalcGreenMat(), camera->ViewMat(), camera->ProjMat());
	}
}

/// <summary>
/// 赤ゲージ用の行列を計算
/// </summary>
ShunLib::Matrix HPGauge::CalcRedMat()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	Matrix w;
	//拡大
	w *= Matrix::CreateScale(Scale());

	//親とのずれ
	w *= Matrix::CreateTranslation(Offset());

	//回転
	w *= Matrix::CreateRotationZ(Rot().m_z);
	w *= Matrix::CreateRotationX(Rot().m_x);
	w *= Matrix::CreateRotationY(Rot().m_y);

	//位置
	w *= Matrix::CreateTranslation(Pos());
	return w;
}

/// <summary>
/// 緑ゲージ用の行列を計算
/// </summary>
ShunLib::Matrix HPGauge::CalcGreenMat()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	Matrix w;

	//残りHPの割合
	float ratio = (float)Parent()->Data().HP() / Parent()->Data().MaxHP();

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

/// <summary>
/// 回転を計算
/// </summary>
void HPGauge::CalcRot()
{
	//auto camera = ShunLib::MainCamera::GetInstance();
	//Vec3 rot;

	////親からのずれ
	////このベクトルを正面にする
	//Vec3 o = Offset();
	//o.Normalize();

	////親からカメラへ向かうベクトル
	//Vec3 v = camera->View().pos - Parent()->WorldPos();
	//v.Normalize();

	//Rot(Vec3::DegreeEachAxis(o,v));
}
