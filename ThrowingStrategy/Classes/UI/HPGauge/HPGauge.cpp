//************************************************/
//* @file  :HPGauge.cpp
//* @brief :HP�Q�[�W
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "HPGauge.h"

#include <SL_MacroConstants.h>
#include <SL_Conversion.h>
#include "../UITextureHolder.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
HPGauge::HPGauge() :
	m_parent(nullptr),
	m_offset(Vec3::UnitZ)
{
	Scale(Vec3(3.5f,1.0f,0.5f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HPGauge::~HPGauge()
{
}

/// <summary>
/// �X�V
/// </summary>
void HPGauge::Update()
{
	if (m_parent != nullptr)
	{
		//�ʒu�����킹��
		Pos(m_parent->WorldPos());

		//�������J�����ɍ��킹��
		CalcRot();
	}
}

/// <summary>
/// �`��
/// </summary>
void HPGauge::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto texHolder = UITextureHolder::GetInstance();

	//�Ԃ̃Q�[�W��`��
	texHolder->RedGauge()->Draw(CalcRedMat(), camera->ViewMat(), camera->ProjMat());

	//�΂̃Q�[�W��`��
	texHolder->GreenGauge()->Draw(CalcGreenMat(), camera->ViewMat(), camera->ProjMat());
}

/// <summary>
/// �ԃQ�[�W�p�̍s����v�Z
/// </summary>
ShunLib::Matrix HPGauge::CalcRedMat()
{
	Matrix w;
	//�g��
	w *= Matrix::CreateScale(Scale());

	//�e�Ƃ̂���
	w *= Matrix::CreateTranslation(Offset());

	//��]
	w *= Matrix::CreateRotationZ(Rot().m_z);
	w *= Matrix::CreateRotationX(Rot().m_x);
	w *= Matrix::CreateRotationY(Rot().m_y);

	//�ʒu
	w *= Matrix::CreateTranslation(Pos());
	return w;
}

/// <summary>
/// �΃Q�[�W�p�̍s����v�Z
/// </summary>
ShunLib::Matrix HPGauge::CalcGreenMat()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	Matrix w;

	//�c��HP�̊���
	float ratio = (float)Parent()->Data().HP() / Parent()->Data().MaxHP();

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

/// <summary>
/// ��]���v�Z
/// </summary>
void HPGauge::CalcRot()
{
	//auto camera = ShunLib::MainCamera::GetInstance();
	//Vec3 rot;
	//
	////�e����̂���
	////���̃x�N�g���𐳖ʂɂ���
	//Vec3 o = Offset();
	//o.Normalize();

	////�e����J�����֌������x�N�g��
	//Vec3 v = camera->View().pos - Parent()->WorldPos();
	//v.Normalize();

	//Rot(Vec3::DegreeEachAxis(o,v));
}
