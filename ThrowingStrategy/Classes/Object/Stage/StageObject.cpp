//************************************************/
//* @file  :StageObject.cpp
//* @brief :�X�e�[�W�ɔz�u����I�u�W�F�N�g�̂܂Ƃ�
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "StageObject.h"
#include "../../Physics/Collision/SL_CollisionManager.h"
#include "../../Util/SL_Camera.h"
#include "../../Util/BasicShapeModelRenderer.h"

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Block::Block():
	ObjectBase(ObjectConstantNumber::BLOCK)
{
	m_data.Team(ObjectConstantNumber::TEAM::NONE);

	//�����蔻��̐ݒ�
	m_collider = new BoxCollider(ShunLib::COLLIDER_LAYER::STATIC);
	m_collider->Parent(this);
	m_collider->IsStatic(true);

	m_color = ShunLib::Colors::WHITE;
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}

/// <summary>
/// ���̏�����
/// </summary>
void Block::Initialize()
{
	//�����蔻����g�p����
	m_collider->IsEnable(true);

	//���N���X�̏�����
	ObjectBase::Initialize();
}

/// <summary>
/// ���̕`��
/// </summary>
void Block::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto renderer = BasicShapeRenderer::GetInstance();

	//�s��̌v�Z
	m_transform.CalcMat();

	renderer->DrawCube(m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat(), m_color);
}

/// <summary>
/// �I������
/// </summary>
void Block::Finalize()
{
	//�����蔻����g�p����
	m_collider->IsEnable(false);
}

