//************************************************/
//* @file  :DefenseTarget.cpp
//* @brief :�h�q�Ώ�
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#include "DefenseTarget.h"
#include "../../Util/Debugger/DebuggerUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
DefenseTarget::DefenseTarget():
	StateObject(this,ObjectConstantNumber::DEFENSE_TARGET)
{
	this->Scale(DEFENSE_TARGET_CONSTANT::MODEL_SCALE);

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::BoxCollider;
	m_collider->Parent(this);
	m_collider->PosObj(this);
	m_collider->Offset(DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Size(DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE / DEFENSE_TARGET_CONSTANT::MODEL_SCALE);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DefenseTarget::~DefenseTarget()
{
	SAFE_DELETE(m_collider)
}

/// <summary>
/// ������
/// </summary>
void DefenseTarget::Initialize()
{
	StateObject::Initialize();
}

/// <summary>
/// �I��
/// </summary>
void DefenseTarget::Finalize()
{
	StateObject::Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
void DefenseTarget::Update()
{
	if (Team() == ObjectConstantNumber::BLUE){
		DebuggerUI::GetInstance()->DrawDebugText("DefenseTarget BLUE : %d", HP());
	}
	else {
		DebuggerUI::GetInstance()->DrawDebugText("DefenseTarget RED  : %d", HP());
	}

	StateObject::Update();
}
