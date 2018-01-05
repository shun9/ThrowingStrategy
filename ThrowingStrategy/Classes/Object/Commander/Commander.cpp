//************************************************/
//* @file  :Commander.cpp
//* @brief :�w����
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "Commander.h"
#include "CommanderMoveState.h"

#include <SL_MacroConstants.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Commander::Commander() :
	StateObject(this, OBJECT_LIST::COMMANDER),
	m_capacity(1)
{
	//�����蔻��̐ݒ� ��{�I�Ƀv���C���[�Ɠ���
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_OFFSET);

	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_SIZE);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Commander::~Commander()
{
	SAFE_DELETE(m_collider);
}

/// <summary>
/// ������
/// </summary>
void Commander::Initialize()
{
	StateObject::Initialize();

	//������Ԃ�ݒ�
	this->ChangeState(new CommanderMoveState);
}

/// <summary>
/// �I��
/// </summary>
void Commander::Finalize()
{
	StateObject::Finalize();
}
