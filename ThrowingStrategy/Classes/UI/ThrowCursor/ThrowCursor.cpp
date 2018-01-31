//************************************************/
//* @file  :ThrowCursor.cpp
//* @brief :着弾地点の表示
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "ThrowCursor.h"
#include "../UIResourceHolder.h"
#include "../UIConstantNumber.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
ThrowCursor::ThrowCursor()
{
	m_scale = UIConstantNumber::THROW_CURSOR_CONSTANT::SCALE;
}

/// <summary>
/// 更新
/// </summary>
void ThrowCursor::Update()
{
	m_mat = Matrix::CreateTranslation(m_pos);

	m_mat *= Matrix::CreateScale(m_scale);
}

/// <summary>
/// 描画
/// </summary>
void ThrowCursor::Render()
{
	//使用しているなら描画
	if (m_isEnable){
		auto model = UIResourceHolder::GetInstance()->GetModel(UI_MODEL_LIST::THROW_CURSOR);
		auto camera = ShunLib::MainCamera::GetInstance();
		model->Draw(m_mat, camera->ViewMat(), camera->ProjMat());
	}
}
