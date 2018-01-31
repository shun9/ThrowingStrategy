//************************************************/
//* @file  :PowerGauge.cpp
//* @brief :�p���[�Q�[�W
//* @date  :2018/01/29
//* @author:S.Katou
//************************************************/
#include "PowerGauge.h"
#include "../UIResourceHolder.h"
#include "../../Util/SL_Camera.h"

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PowerGauge::PowerGauge():
	m_parent(nullptr),
	m_power(0.0f),
	m_offset(Vec3::UnitZ)
{
	Scale(Vec3(3.5f, 1.0f, 0.5f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PowerGauge::~PowerGauge()
{
}

/// <summary>
/// �X�V
/// </summary>
void PowerGauge::Update()
{
	if (m_parent != nullptr)
	{
		//�g�p���Ă��邩�ǂ���
		m_isEnable = m_parent->IsEnable();

		//�ʒu�����킹��
		Pos(m_parent->WorldPos());

		//�������J�����ɍ��킹��
		//CalcRot();
	}
}

/// <summary>
/// �`��
/// </summary>
void PowerGauge::Render()
{
	//�g�p���Ă�����`��
	if (m_isEnable)
	{
		auto camera = ShunLib::MainCamera::GetInstance();
		auto texHolder = UIResourceHolder::GetInstance();

		//�p���[�Q�[�W��`��
		texHolder->GetTexture(UI_TEXTURE_LIST::ORANGE_GAUGE)->Draw(CalcMat(), camera->ViewMat(), camera->ProjMat());
	}
}

/// <summary>
/// �s��̌v�Z������
/// </summary>
Matrix PowerGauge::CalcMat()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	Matrix w;

	//�c��HP�̊���
	float ratio = m_power / Parent()->Data().Power();

	//�c��HP�̊����ɂ���Ċg�嗦��ύX
	Vec3 scale = Scale();
	scale.m_x *= ratio;
	w *= Matrix::CreateScale(scale);

	//�e�Ƃ̂���
	w *= Matrix::CreateTranslation(Offset());

	//��]
	w *= Matrix::CreateRotationZ(Rot().m_z);
	w *= Matrix::CreateRotationX(Rot().m_x);
	w *= Matrix::CreateRotationY(Rot().m_y);

	//�ʒu�@���l�߂���
	Vec3 pos = Pos();
	pos.m_x -= (1.0f - ratio) * (Scale().m_x / 2.0f);
	w *= Matrix::CreateTranslation(pos);

	return w;
}
