//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :�I�u�W�F�N�g
//* @date  :2017/11/07
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"

/// <summary>
/// �ړ�������
/// </summary>
void ObjectBase::Move()
{
	auto timer = ShunLib::MyStepTimer::GetInstance();

	//�ړ�
	m_pos += m_velocity * timer->GetElapsedSeconds();
	
	//TODO:�����Ă���������v�Z����


	//���C��������
	m_velocity *= FRICTION;
}

/// <summary>
/// �`�� �e�p
/// </summary>
void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{
	//�e������ꍇ�͂����ł͕`�悵�Ȃ�
	if (m_parent != nullptr)return;

	this->Render(Matrix::Identity, view, proj);
}

/// <summary>
/// �`�� �q�p
/// </summary>
void ObjectBase::Render(const Matrix & parentWorld, const Matrix & view, const Matrix & proj)
{
	auto data = OBJ_PARAM(this->m_type);

	Matrix world = parentWorld;

	//�g��@�k��
	world *= Matrix::CreateScale(m_scale);

	//���[�� �s�b�` ���[
	world *= Matrix::CreateRotationZ(m_rotation.m_y);
	world *= Matrix::CreateRotationX(m_rotation.m_x);
	world *= Matrix::CreateRotationY(m_rotation.m_z);

	//�ړ�
	world *= Matrix::CreateTranslation(m_pos);

	//���f�������݂���Ȃ�Ε`��
	if (data.model)
	{
		//���f���`��
		data.model->Draw(world, view, proj);
	}

	//�q�̕`��
	for (auto& v : m_children)
	{
		v->Render(world, view, proj);
	}
}
