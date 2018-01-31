//************************************************/
//* @file  :ThrowCursor.cpp
//* @brief :���e�n�_�̕\��
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "ThrowCursor.h"
#include "../UIResourceHolder.h"
#include "../UIConstantNumber.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ThrowCursor::ThrowCursor()
{
	m_scale = UIConstantNumber::THROW_CURSOR_CONSTANT::SCALE;
}

/// <summary>
/// �X�V
/// </summary>
void ThrowCursor::Update()
{
	m_mat = Matrix::CreateTranslation(m_pos);

	m_mat *= Matrix::CreateScale(m_scale);
}

/// <summary>
/// �`��
/// </summary>
void ThrowCursor::Render()
{
	//�g�p���Ă���Ȃ�`��
	if (m_isEnable){
		auto model = UIResourceHolder::GetInstance()->GetModel(UI_MODEL_LIST::THROW_CURSOR);
		auto camera = ShunLib::MainCamera::GetInstance();
		model->Draw(m_mat, camera->ViewMat(), camera->ProjMat());
	}
}
